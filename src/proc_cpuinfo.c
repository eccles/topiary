/*
This file is part of liblnxproc.

 liblnxproc is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 liblnxproc is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with liblnxproc.  If not, see <http://www.gnu.org/licenses/>.

 Copyright 2013 Paul Hewlett, phewlett76@gmail.com

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strlcpy.h"
#include "error_private.h"
#include "limits_private.h"
#include "array_private.h"
#include "results_private.h"
#include "interface_private.h"
#include "base_private.h"
#include "modules.h"

static int
proc_cpuinfo_normalize(_LNXPROC_BASE_T *base)
{
    _LNXPROC_BASE_DATA_T *data = base->current;
    _LNXPROC_RESULTS_T *results = data->results;
    _LNXPROC_ARRAY_T *array = data->array;
    _LNXPROC_VECTOR_T *vector = array->vector;

    size_t nrows = vector->length;

    _LNXPROC_DEBUG("Current data is %d at %p\n", data->id, data);
    _LNXPROC_DEBUG("Current results is at %p\n", results);
    _LNXPROC_DEBUG("Nrows %zd\n", nrows);
    char ***values = (char ***) vector->values;

    int i;
    char prockey[32];
    int np1 = 0;
    int np2 = 0;

    STRLCAT(prockey, "/", np1, sizeof(prockey));

    char key[64];
    int n1 = 0;

    STRLCAT(key, "/", n1, sizeof(key));

    _lnxproc_results_init(results, nrows);
    int first = 2;

    for (i = 0; i < nrows; i++) {
        char **value1 = (char **) values[i];
        char *rowkey = value1[0];

        if (!rowkey)
            continue;
        _LNXPROC_DEBUG("%d:rowkey '%s'\n", i, rowkey);

        char *val = value1[1];

        if (!val)
            continue;
        while (*val == ' ')
            val++;

        if (!strcmp(rowkey, "processor")) {
            np2 = np1;
            STRLCAT(prockey, val, np2, sizeof(prockey));
            STRLCAT(prockey, "/", np2, sizeof(prockey));
            first--;
            _LNXPROC_DEBUG("%d:first %d prockey '%s'\n", i, first, prockey);
        }

        else {
            if (!strcmp(rowkey, "apicid") ||
                !strcmp(rowkey, "initial apicid") ||
                !strcmp(rowkey, "physical id") || !strcmp(rowkey, "core id")) {
                int np3 = np2;

                STRLCAT(prockey, rowkey, np3, sizeof(prockey));
                _LNXPROC_DEBUG("%d:key '%s'\n", i, prockey);
                int v = atoi(val);

                _LNXPROC_DEBUG("%d:val %d\n", i, v);

                _lnxproc_results_add_int(results, prockey, v);
            }
            else if (!strcmp(rowkey, "bogomips") || !strcmp(rowkey, "cpu MHz")) {
                if (first > 0) {
                    int n2 = n1;

                    STRLCAT(key, rowkey, n2, sizeof(key));
                    _LNXPROC_DEBUG("%d:key '%s'\n", i, key);
                    float f = atof(val);

                    _LNXPROC_DEBUG("%d:val %f\n", i, f);
                    _lnxproc_results_add_fixed(results, key, f, 0, 1);
                }
            }
            else if (!strcmp(rowkey, "cpu cores") ||
                     !strcmp(rowkey, "cache_alignment") ||
                     !strcmp(rowkey, "cache size") ||
                     !strcmp(rowkey, "clflush size") ||
                     !strcmp(rowkey, "cpuid level") ||
                     !strcmp(rowkey, "model") ||
                     !strcmp(rowkey, "siblings") ||
                     !strcmp(rowkey, "stepping") ||
                     !strcmp(rowkey, "cpu family")) {
                if (first > 0) {
                    int n2 = n1;

                    STRLCAT(key, rowkey, n2, sizeof(key));
                    _LNXPROC_DEBUG("%d:key '%s'\n", i, key);
                    int v = atoi(val);

                    _LNXPROC_DEBUG("%d:val %d\n", i, v);
                    _lnxproc_results_add_int(results, key, v);
                }
            }
            else if (!strcmp(rowkey, "address sizes") ||
                     !strcmp(rowkey, "flags") ||
                     !strcmp(rowkey, "fpu") ||
                     !strcmp(rowkey, "fpu_exception") ||
                     !strcmp(rowkey, "model name") ||
                     !strcmp(rowkey, "microcode") ||
                     !strcmp(rowkey, "power management") ||
                     !strcmp(rowkey, "vendor_id") || !strcmp(rowkey, "wp")) {
                _LNXPROC_DEBUG("%d:first %d\n", i, first);
                if (first > 0) {
                    int n2 = n1;

                    STRLCAT(key, rowkey, n2, sizeof(key));
                    _LNXPROC_DEBUG("%d:key '%s'\n", i, key);
                    _LNXPROC_DEBUG("%d:val '%s'\n", i, val);
                    _lnxproc_results_add_stringref(results, key, val);
                }
            }
            else {
                int np3 = np2;

                STRLCAT(prockey, rowkey, np3, sizeof(prockey));
                _LNXPROC_DEBUG("%d:key '%s'\n", i, prockey);
                _LNXPROC_DEBUG("%d:val '%s'\n", i, val);

                _lnxproc_results_add_stringref(results, prockey, val);
            }
        }

    }
    return LNXPROC_OK;
}

int
_lnxproc_proc_cpuinfo_new(_LNXPROC_BASE_T **base, LNXPROC_OPT_T *optional)
{

    _LNXPROC_LIMITS_T *limits = NULL;
    int ret = _lnxproc_limits_new(&limits, 2);

    if (ret) {
        return ret;
    }
    ret = _lnxproc_limits_set(limits, 0, 9, "\f\n", 2); /* row delimiters */
    if (ret) {
        _LNXPROC_LIMITS_FREE(limits);
        return ret;
    }
    ret = _lnxproc_limits_set(limits, 1, 2, ":\t", 2);  /* column delimiter */
    if (ret) {
        _LNXPROC_LIMITS_FREE(limits);
        return ret;
    }

    char *filenames[] = { "/proc/cpuinfo", };
    ret =
        _lnxproc_base_new(base, "proc_cpuinfo", _LNXPROC_BASE_TYPE_MEMOIZE,
                          NULL, proc_cpuinfo_normalize, NULL, 256, limits);
    if (!ret) {
        ret = _lnxproc_base_set_filenames(*base, filenames, 1);
    }
    _LNXPROC_LIMITS_FREE(limits);
    return ret;
}

/*
 * vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab
 */

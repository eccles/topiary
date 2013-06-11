/*
 * This file is part of liblnxproc.
 *
 *  liblnxproc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  liblnxproc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with liblnxproc.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright 2013 Paul Hewlett, phewlett76@gmail.com
 *
 */

/* This file is a re-implementation of the 'list' type from Python
 */

#ifndef LIBLNXPROC_ARRAY_PRIVATE_H
#define LIBLNXPROC_ARRAY_PRIVATE_H 1

#include "vector_private.h"
#include "limits_private.h"

struct _lnxproc_array_t {
    _LNXPROC_LIMITS_T *limits;
    _LNXPROC_VECTOR_T *vector;
    char *data;
};
typedef struct _lnxproc_array_t _LNXPROC_ARRAY_T;

int _lnxproc_array_new(_LNXPROC_ARRAY_T **array, _LNXPROC_LIMITS_T *limits);

int _lnxproc_array_free(_LNXPROC_ARRAY_T **arrayptr);

#define _LNXPROC_ARRAY_FREE(a) _lnxproc_array_free(&a)

int _lnxproc_array_size(_LNXPROC_ARRAY_T *array, size_t * size);
int _lnxproc_array_set(_LNXPROC_ARRAY_T *array, size_t idx[],
                       size_t dim, char *val);
int _lnxproc_array_set_last(_LNXPROC_ARRAY_T *array,
                            size_t idx[], size_t dim, char *val);
int _lnxproc_array_get(_LNXPROC_ARRAY_T *array, size_t idx[],
                       size_t dim, char **value);

int _lnxproc_array_diff(_LNXPROC_ARRAY_T *previous,
                        _LNXPROC_ARRAY_T *current,
                        size_t idx[], size_t dim, int *diff);

typedef int (*_LNXPROC_ARRAY_ITERATE_FUNC) (char *val,
                                            void *data,
                                            size_t idx[], size_t dim);

int _lnxproc_array_iterate(_LNXPROC_ARRAY_T *array,
                           void *data,
                           int allocated, _LNXPROC_ARRAY_ITERATE_FUNC func);

int _lnxproc_array_print(_LNXPROC_ARRAY_T *array, int allocated);

#endif                          // LIBLNXPROC_ARRAY_PRIVATE_H
/*
 * vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab
 */

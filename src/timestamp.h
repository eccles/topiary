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

#ifndef LIBLNXPROC_TIMESTAMP_H
#define LIBLNXPROC_TIMESTAMP_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>
#include "error.h"

    struct lnxproc_timestamp_t;
    typedef struct lnxproc_timestamp_t LNXPROC_TIMESTAMP_T;

    struct timeval *lnxproc_timestamp_timeval(LNXPROC_TIMESTAMP_T * timestamp);
    struct timeval *lnxproc_timestamp_tv(LNXPROC_TIMESTAMP_T * timestamp);
    char *lnxproc_timestamp_str(LNXPROC_TIMESTAMP_T * timestamp, char *buf,
                                size_t buflen);
    int lnxproc_timestamp_print(LNXPROC_TIMESTAMP_T * timestamp);
    LNXPROC_TIMESTAMP_T *lnxproc_timestamp_init(LNXPROC_ERROR_CALLBACK
                                                callback);
    LNXPROC_TIMESTAMP_T *lnxproc_timestamp_free(LNXPROC_TIMESTAMP_T *
                                                timestamp);

#ifdef __cplusplus
}                               // extern "C"
#endif
#endif                          // LIBLNXPROC_TIMESTAMP_H
/*
 * vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab
 */

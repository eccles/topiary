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

#ifndef LIBLNXPROC_ERROR_H
#define LIBLNXPROC_ERROR_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <stddef.h>
#include <stdio.h>

    enum lnxproc_error_t {
        LNXPROC_OK = 0,
        LNXPROC_ERROR_MISMATCHED_STRINGS,
        LNXPROC_ERROR_SYSTEM,
        LNXPROC_ERROR_ARRAY_MALLOC_HEADER,
        LNXPROC_ERROR_ARRAY_MALLOC_DATA,
        LNXPROC_ERROR_ARRAY_NULL,
/*5*/ LNXPROC_ERROR_ARRAY_REALLOC_DATA,
        LNXPROC_ERROR_ARRAY_INDEX_OUT_OF_RANGE,
        LNXPROC_ERROR_ARRAY_VECTOR_NULL,
        LNXPROC_ERROR_ARRAY_VECTOR_MALLOC,
        LNXPROC_ERROR_ARRAY_SAVED_MALLOC,
        LNXPROC_ERROR_ARRAY_SAVED_NULL,
        LNXPROC_ERROR_ARRAY_ADDRESS_NULL,
        LNXPROC_ERROR_ARRAY_ADDRESS_CONTENTS_NOT_NULL,
        LNXPROC_ERROR_ARRAY_LIMITS_NULL,
        LNXPROC_ERROR_ARRAY_ILLEGAL_DIMENSION,
        LNXPROC_ERROR_BASE_NULL,
        LNXPROC_ERROR_BASE_BAD_FILENAME,
/*17*/ LNXPROC_ERROR_BASE_MALLOC_BASE,
        LNXPROC_ERROR_BASE_MALLOC_BUFFER,
        LNXPROC_ERROR_BASE_MALLOC_FILENAME,
        LNXPROC_ERROR_BASE_MALLOC_FILEPREFIX,
        LNXPROC_ERROR_BASE_MALLOC_FILESUFFIX,
        LNXPROC_ERROR_BASE_MALLOC_ARRAY,
        LNXPROC_ERROR_BASE_MALLOC_RESULTS,
        LNXPROC_ERROR_BASE_READ_OVERFLOW,
        LNXPROC_ERROR_LIMITS_MALLOC,
        LNXPROC_ERROR_LIMITS_NULL,
        LNXPROC_ERROR_LIMIT_NULL,
/*28*/ LNXPROC_ERROR_LIMITS_MALLOC_ENTRY,
        LNXPROC_ERROR_LIMITS_ADDRESS_NULL,
        LNXPROC_ERROR_LIMITS_ADDRESS_CONTENTS_NOT_NULL,
        LNXPROC_ERROR_LIMITS_ILLEGAL_DIMENSION,
        LNXPROC_ERROR_RESULTS_DB_NULL,
        LNXPROC_ERROR_RESULTS_DB_NOT_OPEN,
/*34*/ LNXPROC_ERROR_RESULTS_DB_OPEN,
        LNXPROC_ERROR_RESULTS_DB_CLOSE,
        LNXPROC_ERROR_RESULTS_DB_FETCH,
        LNXPROC_ERROR_RESULTS_DB_STORE,
        LNXPROC_ERROR_RESULTS_DB_ITERATE,
        LNXPROC_ERROR_RESULTS_NULL,
        LNXPROC_ERROR_RESULTS_BUF_NULL,
        LNXPROC_ERROR_RESULTS_BUFLEN_ZERO,
        LNXPROC_ERROR_RESULTS_TV_NULL,
/*43*/ LNXPROC_ERROR_RESULTS_ADDRESS_NULL,
        LNXPROC_ERROR_RESULTS_ADDRESS_CONTENTS_NOT_NULL,
        LNXPROC_ERROR_RESULTS_MALLOC,
        LNXPROC_ERROR_RESULTS_KEY_NULL,
        LNXPROC_ERROR_RESULTS_KEYLEN_ZERO,
        LNXPROC_ERROR_RESULTS_VAL_ADDRESS_NULL,
        LNXPROC_ERROR_VECTOR_MALLOC_HEADER,
        LNXPROC_ERROR_VECTOR_MALLOC_DATA,
/*50*/ LNXPROC_ERROR_VECTOR_NULL,
        LNXPROC_ERROR_VECTOR_REALLOC_DATA,
        LNXPROC_ERROR_VECTOR_INDEX_OUT_OF_RANGE,
        LNXPROC_ERROR_VECTOR_NULL_DATA,
        LNXPROC_ERROR_VECTOR_NULL_CHILDREN,
        LNXPROC_ERROR_VECTOR_NULL_VALUES,
/*57*/ LNXPROC_ERROR_VECTOR_ADDRESS_NULL,
        LNXPROC_ERROR_VECTOR_ADDRESS_CONTENTS_NOT_NULL,
        LNXPROC_ERROR_SIZE
    };

    typedef enum lnxproc_error_t LNXPROC_ERROR_T;

    typedef void (*LNXPROC_ERROR_CALLBACK) (const char *filename,
                                            int lineno,
                                            const char *funcname,
                                            LNXPROC_ERROR_T err);

    const char *lnxproc_strerror(LNXPROC_ERROR_T err, char *buf, size_t buflen);

    void lnxproc_error_print_callback(const char *filename,
                                      int lineno,
                                      const char *funcname,
                                      LNXPROC_ERROR_T err);

    int lnxproc_error_check(void);

#define LNXPROC_ERROR_CHECK() lnxproc_error_check()

#ifdef DEBUG

    void lnxproc_debug(const char *filename,
                       int lineno, const char *funcname, char *fmt, ...
        );

#define LNXPROC_DEBUG(fmt, args...) \
                          lnxproc_debug(__FILE__,__LINE__,__func__, fmt, ##args)

#define LNXPROC_ERROR_DEBUG(s, fmt, args...) {\
    char buf[32];\
    const char *c = lnxproc_strerror(s,buf,sizeof buf);\
    char buf1[64];\
    snprintf(buf1,sizeof buf1,"Error : %d %s",s,c);\
    char buf2[64];\
    snprintf(buf2,sizeof buf2,fmt, ##args);\
    lnxproc_debug(__FILE__,__LINE__,__func__, "%s: %s\n", buf1, buf2);\
}

#else
#define LNXPROC_DEBUG(fmt, args...)
#define LNXPROC_ERROR_DEBUG(s, fmt, args...)
#endif

#ifdef __cplusplus
}                               // extern "C"
#endif
#endif                          // LIBLNXPROC_ERROR_H
/*
 * vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab
 */
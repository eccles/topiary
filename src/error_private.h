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

#ifndef LIBLNXPROC_ERROR_PRIVATE_H
#define LIBLNXPROC_ERROR_PRIVATE_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <lnxproc/error.h>

    int _lnxproc_error_check(void);

#define _LNXPROC_ERROR_CHECK() _lnxproc_error_check()

#ifdef DEBUG

#include <stdio.h>

    void _lnxproc_debug(const char *filename,
                        int lineno, const char *funcname, char *fmt, ...
        );

#define _LNXPROC_DEBUG(fmt, args...) \
                          _lnxproc_debug(__FILE__,__LINE__,__func__, fmt, ##args)

#define _LNXPROC_ERROR_DEBUG(s, fmt, args...) {\
    char buf[32];\
    const char *c = lnxproc_strerror(s,buf,sizeof buf);\
    char buf1[64];\
    snprintf(buf1,sizeof buf1,"Error : %d %s",s,c);\
    char buf2[512];\
    snprintf(buf2,sizeof buf2,fmt, ##args);\
    _lnxproc_debug(__FILE__,__LINE__,__func__, "%s: %s\n", buf1, buf2);\
}

#else
#define _LNXPROC_DEBUG(fmt, args...)
#define _LNXPROC_ERROR_DEBUG(s, fmt, args...)
#endif

#ifdef __cplusplus
}                               // extern "C"
#endif
#endif                          // LIBLNXPROC_ERROR_PRIVATE_H
/*
 * vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab
 */

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

#ifndef LIBLNXPROC_INTERFACE_PRIVATE_H
#define LIBLNXPROC_INTERFACE_PRIVATE_H 1

#include "base_private.h"
#include <lnxproc/interface.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef LNXPROC_ERROR_T (*_LNXPROC_METHOD) (_LNXPROC_BASE_T ** base,
                                                void *optional);

    struct lnxproc_module_t {
        _LNXPROC_METHOD new;
        _LNXPROC_BASE_T *base;
        void *optional;
    };

#ifdef __cplusplus
}                               // extern "C"
#endif
#endif                          // LIBLNXPROC_INTERFACE_PRIVATE_H
/*
 * vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab
 */

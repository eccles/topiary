/*
 * This file is part of topiary.
 *
 *  topiary is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  topiary is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with topiary.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright 2013 Paul Hewlett, phewlett76@gmail.com
 *
 */

#include "config.h"

#include <stdio.h>              //printf
#include <string.h>             //strerror_r

#include "error_private.h"

#ifdef DEBUG
#include <stdarg.h>
#endif

static const char *errstr[] = {
    "No error",
    "Error enum and string have mismatched sizes",
    "Memory allocation error",
    "Illegal argument",
    "Overflow of raw read buffer",
    "Base regex failure",
    "Base glob failure",
    "Key not found",
    "Read buffer > SSIZE_MAX bytes",
};

#define ERRSTR_SIZE sizeof(errstr)/sizeof(errstr[0])

static const char unknown_error[] = "Unknown error";

#ifdef DEBUG
void
_topiary_debug(const char *filename, int lineno, const char *funcname,
               char *fmt, ...)
{
    va_list args;

    printf("Debug: %s[%d] %s -> ", filename, lineno, funcname);

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

}
#endif
const char *
topiary_strerror(int err, char *buf, size_t buflen)
{
    if (err < 0) {
        strerror_r(-((int) err), buf, buflen);
        return buf;
    }
    if (err >= ERRSTR_SIZE) {
        return unknown_error;
    }

    return errstr[err];
}

int
_topiary_error_check(void)
{
    if (TOPIARY_ERROR_SIZE != ERRSTR_SIZE) {
        int err = TOPIARY_ERROR_MISMATCHED_STRINGS;

        printf("Error: %s %d != %zd\n", errstr[err], TOPIARY_ERROR_SIZE,
               ERRSTR_SIZE);
        return err;
    }
    return TOPIARY_OK;
}

/*
 * vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab
 */

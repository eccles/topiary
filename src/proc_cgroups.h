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

#ifndef LIBLNXPROC_PROC_CGROUPS_H
#define LIBLNXPROC_PROC_CGROUPS_H 1
#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "proc_cgroups.h"

    struct procgroups_sub_t {
        int hierarchy;
        int num_cgroups;
        int enabled;
    };

    struct {
        struct procgroups_sub_t cpuset;
        struct procgroups_sub_t cpu;
        struct procgroups_sub_t cpuacct;
        struct procgroups_sub_t memory;
        struct procgroups_sub_t devices;
        struct procgroups_sub_t freezer;
        struct procgroups_sub_t blkio;
        struct procgroups_sub_t perf_event;
    } proccgroups_data;

    LNXPROC_BASE_T *proccgroups_init(void);

#ifdef __cplusplus
}                               // extern "C"
#endif
#endif                          // LIBLNXPROC_PROC_CGROUPS_H
/*
 * vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab
 */

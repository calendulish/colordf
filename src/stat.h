/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2004  Roman Bogorodskiy <bogorodskiy@inbox.ru>
 *                     Pierre Chifflier <chifflier@cpe.fr>
 *               2024  Lara Maia <dev@lara.monster>
 */

#ifndef STAT_H
#define STAT_H

#include <sys/param.h>
#include <sys/mount.h>
#include <sys/vfs.h>

/* A mount table entry. */
struct mount_entry {
    char *me_devname;             /* Device node pathname, including "/dev/". */
    char *me_mountdir;            /* Mount point directory pathname. */
    char *me_type;                /* "nfs", "4.2", etc. */
    struct mount_entry *me_next;
};

/*struct mount_entry *read_filesystem_list (int need_fs_type);*/
struct mount_entry *read_filesystem_list(const char *fs_type);

void display_single_fs(const char *filesystem);

void statfs_display_single_fs(const struct statfs *s, const char *device, const char *mountpoint, const char *fstype);

void display_all_fs(const char *fstype);

#endif /* STAT_H */

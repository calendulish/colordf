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
 *               2016  Lara Maia <dev@lara.click>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mntent.h>

#include "colors.h"
#include "common.h"
#include "stat.h"

struct mount_entry *read_filesystem_list(const char *fs_type) {
    struct mount_entry *mount_list;
    struct mount_entry *me;
    struct mount_entry **mtail = &mount_list;

    struct mntent *mnt;
    char *table = MOUNTED;
    FILE *fp;

    fp = setmntent(table, "r");
    if (!fp) return NULL;

    while ((mnt = getmntent(fp))) {
        if (show_pseudofs == 0 && is_pseudofs(mnt->mnt_type) == 1)
            continue;

        if (strcmp(fs_type, "all") != 0 && strcmp(fs_type, mnt->mnt_type) != 0)
            continue;

        me = malloc(sizeof(struct mount_entry));
        me->me_devname = strdup(mnt->mnt_fsname);
        me->me_mountdir = strdup(mnt->mnt_dir);
        me->me_type = strdup(mnt->mnt_type);

        /* Add to the linked list. */
        *mtail = me;
        mtail = &me->me_next;
    }

    endmntent(fp);

    *mtail = NULL;
    return mount_list;
}

void display_single_fs(const char *filesystem) {
    struct statfs s;

    if (statfs(filesystem, &s) == -1) {
        perror("statfs()");
        return;
    }

    struct mount_entry *mount_list, *mnt;
    struct statfs t;

    mount_list = read_filesystem_list("all");
    if (!mount_list) return;

    for (mnt = mount_list; mnt != NULL; mnt = mnt->me_next) {
        if (statfs(mnt->me_mountdir, &t) == -1) {
            ERROR("damn!");
            return;
        }

        if (memcmp(&s, &t, sizeof(struct statfs)) == 0) { /* found ! */
            statfs_display_single_fs(&s, mnt->me_devname, mnt->me_mountdir, mnt->me_type);
            return; /* only one possible match */
        }
    }
    /* not found ?! */
}

void statfs_display_single_fs(const struct statfs *s, const char *device, const char *mountpoint, const char *fstype) {
    double total, free, used;
    int usage;

    total = (double) s->f_blocks * (double) s->f_bsize / blocksize;
    free = (double) s->f_bfree * (double) s->f_bsize / blocksize;
    used = (double) total - (double) free;

    header();

    /* check for pseudofs */
    if (total != 0)
        usage = (int) rint((double) ((1.0 - (double) free / (double) total) * 100.0));
    else
        return;

    (void) printf("%s%-10s%s %12s %s %s %s %-18s %s %s(%i%%)%s\n",
                  fs_color,
                  device,
                  data_color,
                  fstype,
                  numeric_value((double) free),
                  numeric_value((double) used),
                  numeric_value((double) total),
                  mountpoint,
                  bar((int) rint(usage / 10.0)),
                  perc_color,
                  usage,
                  NORMAL
    );

}

void show_dev(const struct mount_entry *mnt) {
    struct statfs s;

    if (statfs(mnt->me_mountdir, &s) == -1) {
        ERROR("damn!");
        return;
    }

    statfs_display_single_fs(&s, mnt->me_devname, mnt->me_mountdir, mnt->me_type);
}

void display_all_fs(const char *fstype) {
    struct mount_entry *mount_list, *mnt;

    mount_list = read_filesystem_list(fstype);
    if (!mount_list) return;

    for (mnt = mount_list; mnt != NULL; mnt = mnt->me_next) {
        show_dev(mnt);
    }
}

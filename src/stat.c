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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <libmount/libmount.h>

#include "colors.h"
#include "common.h"
#include "stat.h"

static int fs_cmp(struct libmnt_table *tb, struct libmnt_fs *fs1, struct libmnt_fs *fs2);

struct mount_entry *read_filesystem_list(const char *fs_type) {
    struct mount_entry *mount_list;
    struct mount_entry *me;
    struct mount_entry **mtail = &mount_list;

    struct libmnt_fs *fs;
    struct libmnt_iter *iter;
    struct libmnt_table *fstable = NULL;

    struct statfs s;

    fstable = mnt_new_table_from_file("/proc/self/mountinfo");

    // fallback
    if (!fstable)
        fstable = mnt_new_table_from_file(mnt_get_fstab_path());

    if (show_pseudofs == 0)
        mnt_table_uniq_fs(fstable, MNT_UNIQ_FORWARD, fs_cmp);

    iter = mnt_new_iter(MNT_ITER_FORWARD);

    while (mnt_table_next_fs(fstable, iter, &fs) == 0) {
        // netfs not implemented
        if (mnt_fs_is_netfs(fs))
            continue;

        // mount point inaccessible
        if (statfs(mnt_fs_get_target(fs), &s) == -1)
            continue;

        if (!STREQ(fs_type, "all") && !STREQ(fs_type, mnt_fs_get_fstype(fs)))
            continue;

        me = malloc(sizeof(struct mount_entry));
        me->me_devname = strdup(mnt_fs_get_source(fs));
        me->me_mountdir = strdup(mnt_fs_get_target(fs));
        me->me_type = strdup(mnt_fs_get_fstype(fs));

        /* Add to the linked list. */
        *mtail = me;
        mtail = &me->me_next;
    }

    mnt_free_iter(iter);
    mnt_free_table(fstable);
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
    int perc;

    total = (double) s->f_blocks * (double) s->f_bsize / blocksize;
    free = (double) s->f_bfree * (double) s->f_bsize / blocksize;
    used = (double) total - (double) free;
    perc = (int) rint((double) ((1.0 - (double) free / (double) total) * 100.0));

    if (total == 0)
        return;

    header();

    printf("%s%s%-14s%s%s %12s %s %s %s %-18s",
           fs_background,
           fs_color,
           device,
           data_background,
           data_color,
           fstype,
           numeric_value((double) total),
           numeric_value((double) used),
           numeric_value((double) free),
           mountpoint
    );

    if (strlen(mountpoint) <= 17)
        printf("%s%s[%s%s%s%s%s]%s ",
               bracket_background,
               bracket_color,
               gauge_background,
               gauge_color,
               bar((int) rint(perc / 10.0)),
               bracket_background,
               bracket_color,
               RESET_COLOR
               );
    else
        printf("%*s", 13 + (18 - (int) strlen(mountpoint)), " ");

    printf("%s%s(%2i%%)%s\n",
           perc_background,
           perc_color,
           perc,
           RESET_COLOR
    );

}

void display_all_fs(const char *fstype) {
    struct mount_entry *mount_list, *mnt;
    struct statfs s;

    mount_list = read_filesystem_list(fstype);
    if (!mount_list) return;

    for (mnt = mount_list; mnt != NULL; mnt = mnt->me_next) {
        if (statfs(mnt->me_mountdir, &s) == -1)
            continue;

        statfs_display_single_fs(&s, mnt->me_devname, mnt->me_mountdir, mnt->me_type);
    }
}

static int fs_cmp(__attribute__((unused)) struct libmnt_table *tb, struct libmnt_fs *fs1, struct libmnt_fs *fs2) {
    if (mnt_fs_is_pseudofs(fs1) || mnt_fs_is_pseudofs(fs2))
        return 1;

    return !mnt_fs_streq_srcpath(fs1, mnt_fs_get_srcpath(fs2));
}

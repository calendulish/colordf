/*
 * Copyright (C) 2004  Roman Bogorodskiy
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Id: stat.h 11 2004-09-05 17:45:29Z novel $
 */

#ifndef STAT_H
#define STAT_H

#include <sys/param.h>
#include <sys/mount.h>

#ifdef __linux__
#include <sys/vfs.h>
#endif

/* A mount table entry. */
struct mount_entry
{
  char *me_devname;             /* Device node pathname, including "/dev/". */
  char *me_mountdir;            /* Mount point directory pathname. */
  char *me_type;                /* "nfs", "4.2", etc. */
  dev_t me_dev;                 /* Device number of me_mountdir. */
  unsigned int me_dummy : 1;    /* Nonzero for dummy filesystems. */
  unsigned int me_remote : 1;   /* Nonzero for remote fileystems. */
  unsigned int me_type_malloced : 1; /* Nonzero if me_type was malloced. */
  struct mount_entry *me_next;
};

#ifndef ME_DUMMY
# define ME_DUMMY(Fs_name, Fs_type) \
    (!strcmp (Fs_type, "autofs") \
     /* for Irix 6.5 */ \
     || !strcmp (Fs_type, "ignore"))
#endif

#undef STREQ
#define STREQ(a, b) (strcmp ((a), (b)) == 0)

#ifndef ME_REMOTE
/* A file system is `remote' if its Fs_name contains a `:'
   or if (it is of type smbfs and its Fs_name starts with `//').  */
# define ME_REMOTE(Fs_name, Fs_type)    \
    (strchr ((Fs_name), ':') != 0       \
     || ((Fs_name)[0] == '/'            \
         && (Fs_name)[1] == '/'         \
         && STREQ (Fs_type, "smbfs")))
#endif

/*struct mount_entry *read_filesystem_list (int need_fs_type);*/
struct mount_entry *read_filesystem_list(const char *fs_type);
void show_dev(const struct mount_entry * mnt);

void display_single_fs(const char *filesystem);
void statfs_display_single_fs(const struct statfs *s, const char *device, const char *mountpoint, const char *fstype);
void display_all_fs(const char *fstype);

#endif /* STAT_H */

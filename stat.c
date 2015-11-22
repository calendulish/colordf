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
 * $Id: stat.c 25 2005-02-05 11:53:17Z pollux $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <math.h>

#ifdef __linux__
#include <stdint.h>
#include <mntent.h>
#else
#include <sys/ucred.h>
#endif

#include "colors.h"
#include "common.h"
#include "stat.h"

struct mount_entry *read_filesystem_list(const char *fs_type)
{
	struct mount_entry *mount_list;
  	struct mount_entry *me;
  	struct mount_entry **mtail = &mount_list;

#ifdef BSD
{
     	struct statfs *mntbuf;
     	size_t i, mntsize;
     	/*struct mount_entry *mount_list;*/

     	mntsize = getmntinfo(&mntbuf, MNT_WAIT);

     	for (i = 0; i < mntsize; i++) {
		if (strcmp("all", fs_type) == 0 || strcmp(mntbuf[i].f_fstypename, fs_type) == 0) {
			if (show_pseudofs == 0 && (is_pseudofs(mntbuf[i].f_fstypename) == 1)) {
				/* XXX: should we do something with it? */
			} else {
				me = malloc(sizeof(struct mount_entry));
       				me->me_devname = strdup(mntbuf[i].f_mntfromname);
       				me->me_mountdir = strdup(mntbuf[i].f_mntonname);
       				me->me_type = strdup(mntbuf[i].f_fstypename);
       				me->me_type_malloced = 1;
       				me->me_dummy = ME_DUMMY (me->me_devname, me->me_type);
      				me->me_remote = ME_REMOTE (me->me_devname, me->me_type);

       				/* Add to the linked list. */
       				*mtail = me;
       				mtail = &me->me_next;
			}
		}
     	}
 }
#endif
#ifdef __linux__
  {
    struct mntent * mnt;
    char * table = MOUNTED;
    FILE * fp;

    fp = setmntent( table, "r" );
    if (!fp) return NULL;

    while ( (mnt = getmntent(fp)) )
    {
      if (show_pseudofs == 0 && (is_pseudofs(mnt->mnt_type) == 1)) {
        /* XXX: should we do something with it? */
      } else {
        me = malloc(sizeof(struct mount_entry));
        me->me_devname = strdup(mnt->mnt_fsname);
        me->me_mountdir = strdup(mnt->mnt_dir);
        me->me_type = strdup(mnt->mnt_type);
        me->me_type_malloced = 1;
        me->me_dummy = ME_DUMMY (me->me_devname, me->me_type);
        me->me_remote = ME_REMOTE (me->me_devname, me->me_type);

        /* Add to the linked list. */
        *mtail = me;
        mtail = &me->me_next;
      }
    }

    endmntent(fp);
  }
#endif

  *mtail = NULL;
  return mount_list;
}

void display_single_fs(const char *filesystem)
{
	struct statfs s;
	
	if (statfs(filesystem, &s) == -1) {
		perror("statfs()");
		return;
	}

#ifdef BSD
	statfs_display_single_fs(&s, s.f_mntfromname, 
			s.f_mntonname, s.f_fstypename);
#endif
#ifdef __linux__
         {
           struct mount_entry * mount_list, * mnt;
           struct statfs t;

           mount_list = read_filesystem_list("all");
           if (!mount_list) return;

           for (mnt=mount_list; mnt!=NULL; mnt=mnt->me_next)
           {
             if (statfs(mnt->me_mountdir, &t) == -1) {
               ERROR("damn!");	
               return;
             }
             if (memcmp(&s,&t,sizeof(struct statfs))==0) { /* found ! */
               statfs_display_single_fs(&s,mnt->me_devname,mnt->me_mountdir,mnt->me_type);
               return; /* only one possible match */
             }
           }
           /* not found ?! */
         }
#endif
}

void statfs_display_single_fs(const struct statfs *s, const char *device, const char *mountpoint, const char *fstype)
{
	uint64_t total, free, used;
	int usage;	
	
	total = (double)s->f_blocks * (double)s->f_bsize / blocksize;
	free = (double)s->f_bfree * (double)s->f_bsize / blocksize;
	used = (double)total - (double)free;

	header();

	/* check for pseudofs */
	if (total != 0)	
		usage = (int)rint((double)((1.0 - (double)free/(double)total)*100.0));
	else
		usage = 100;
	
	(void)printf("%s%-12s%s %7s %s %s %s %-9s %s %s(%i%%)%s\n", 
		     	fs_color,
		        device,
			data_color,
			fstype,
			numeric_value((double)free),
			numeric_value((double)used),
			numeric_value((double)total),
			mountpoint,
			bar((int)rint(usage / 10.0)),
			perc_color,
			usage,
			NORMAL
			);

}

void show_dev(const struct mount_entry * mnt)
{
  struct statfs s;

  if (statfs(mnt->me_mountdir, &s) == -1) {
    ERROR("damn!");	
    return;
  }

#ifdef BSD
	statfs_display_single_fs(&s,s.f_mntfromname,s.f_mntonname,s.f_fstypename);
#endif
#ifdef __linux__
	statfs_display_single_fs(&s,mnt->me_devname,mnt->me_mountdir,mnt->me_type);
#endif
}

void display_all_fs(const char *fstype)
{
  struct mount_entry * mount_list, * mnt;

  mount_list = read_filesystem_list(fstype);
  if (!mount_list) return;

  for (mnt=mount_list; mnt!=NULL; mnt=mnt->me_next)
  {
    show_dev(mnt);
  }
}	

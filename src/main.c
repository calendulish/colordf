/*
 * Copyright (C) 2004, 2005  Roman Bogorodskiy
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
 * $Id: main.c 26 2005-03-05 17:04:42Z novel $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "stat.h"
#include "common.h"
#include "colors.h"
#include "conf.h"

static void show_help();
static void usage();

int main(int argc, char **argv)
{
	int i,
	    ch;
	char *fs_type = "all";
	
	blocksize = 1048576;
	show_pseudofs = 0;

	read_config_file();

	if (get_config_item("human_readable")) {
		if (atoi((const char*)get_config_item("human_readable")) == 1) {
			human_readable = 1;
			blocksize = 1;
		}
	}
			
     	while ((ch = getopt(argc, argv, "Haghkmt:v")) != -1)
        	switch (ch) {
			case 'a':
				show_pseudofs = 1;
				break;
             		case 'k':
				blocksize = 1024;
                     		break;
             		case 'm':
				blocksize = 1048576;
                     		break;
			case 'g':
				blocksize = 1073741824;
				break;
			case 'h':
				human_readable = 1;
				blocksize = 1; 
				break;
			case 't':
				fs_type = strdup(optarg);
				break;		
			case 'v':
				(void)fprintf(stderr, "%s\n\n", PACKAGE_STRING);
				return 0;
			case 'H':
				show_help();
             		case '?':
             		default:
                     		usage();
             	}
	argc -= optind;
     	argv += optind;

	read_colors();
	
	if (argc == 0) 
		display_all_fs(fs_type);
	else 
		for (i = 0; i< argc; i++)
			display_single_fs(argv[i]);
	
	return 0;
}

static void show_help()
{
	(void)printf("%s\n\n"
		     "Options:\n"
		     "\t-a\t	show pseudofs\n"
		     "\t-k\t	use 1K blocksize\n"
		     "\t-m\t	use 1M blocksize\n"
		     "\t-g\t	use 1G blocksize\n"
		     "\t-h\t	human-readable output\n"
		     "\t-t type\t	show only filesyitems of specified type\n"
		     "\t-v\t	print version and exit\n"
		     "\t-H\t	print this text and exit\n\n",
		     PACKAGE_STRING);
		  
	exit(0);
}

static void usage()
{

	(void)fprintf(stderr, "Usage: cdf [ -aghkm ] [ -t type ] [ -v ] [ -H ]\n\n");

	exit(0);
}

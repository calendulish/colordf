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
 * $Id: common.c 25 2005-02-05 11:53:17Z pollux $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "colors.h"

int header_showed = 0;

char *bar(unsigned short n)
{
	int i;
	char *gauge = (char *)malloc(11);
	char *ret = (char *)malloc(64);

        *gauge = '\0'; /* avoid apparition of artefacts: strcat on non-initialized memory ... */
	
	if (n > 10)
		return NULL;

	for (i = 1; i <= 10; i++) {
		if (i <= n)
			gauge = strcat(gauge, ">");
		else
			gauge = strcat(gauge, " ");
	}

	sprintf(ret, "%s[%s%s%s]%s", bracket_color, gauge_color,
				gauge, bracket_color, NORMAL);


	return ret;
}

void header()
{
	printf("%s", header_color);
	
	if (header_showed == 0) {
		printf("%-12s %7s %7s %7s %7s %-9s %s\n", 
				"Filesystem",
				"Type",
				"Free",
				"Used",
				"Total",
				"Mnt pnt",
				"Capacity"
				);
		header_showed = 1;
	}

	printf("%s", NORMAL);
}

/* expand_filename(): ~/bar -> /home/foo/bar */

char *expand_filename(char *str)
{

	if (str[0] != '~')
		return str;
	str++;
	
	if ((int)getenv("HOME") != -1) {
		char *home;
		home = (char *)getenv("HOME");
		str = strcat(home, str);
	} else {
		(void)fprintf(stderr, "Error: environment variable HOME is not set.\n");
		 exit(-1);
	}
	
	return str;
}													      

short is_pseudofs(const char *fs_type)
{
	/* XXX:
	   - this list is not complete yet
	   - I'm not sure how it will work on Linux 
	*/

	if ((strcmp(fs_type, "devfs") == 0) ||
		(strcmp(fs_type, "devpts") == 0) ||
		(strcmp(fs_type, "proc") == 0) ||
		(strcmp(fs_type, "sysfs") == 0) ||
		(strcmp(fs_type, "usbfs") == 0)) {
			return 1;
	}
			     
	return 0;
}

char *numeric_value(const double bytes)
{
	char *buf;

	buf = (char *)malloc(256);

	if (human_readable) {
		if ((bytes/1073741824) >= 1) {
			(void)snprintf(buf, 255, "%6.0fG", (bytes/1073741824));
		} else if ((bytes/1048576) >= 1) {
			(void)snprintf(buf, 255, "%6.0fM", (bytes/1048576));
		} else 	if ((bytes/1024) >= 1) {
			(void)snprintf(buf, 255, "%6.0fK", (bytes/1024));
		} else {
			(void)snprintf(buf, 255, "%7.0f", bytes);
		}
	} else
		(void)snprintf(buf, 255, "%7.0f", bytes);
		
	return buf;
}

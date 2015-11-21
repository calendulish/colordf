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
 * $Id: conf.c 23 2005-02-03 19:33:01Z novel $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "conf.h"
#include "hash.h"

#define MAXLEN	255

static char *get_config_filename() 
{
	/* 
	 * we try to respect XDG Base Directory Specification:
	 * http://standards.freedesktop.org/basedir-spec/basedir-spec-0.6.html
	 */
	char *config_home;
	char *config_full_path;
	char *xdg_config_home;
	
	config_home = (char *)malloc(256);
	config_full_path = (char *)malloc(256);
	
	xdg_config_home = getenv("XDG_CONFIG_HOME");
	
	if (xdg_config_home != NULL) {
		if (strlen(xdg_config_home) != 0) {
			(void)snprintf(config_home, 255, "%s/.config", xdg_config_home);
		}
	} else {
		char *home;
		home = getenv("HOME");
		
		if (home != NULL) {
			(void)snprintf(config_home, 255, "%s/.config", home);
		} else 
			return NULL;
	}


	(void)snprintf(config_full_path, 256, "%s/cdfrc", config_home);
	free(config_home);

	return config_full_path;
}	

/* some notes:
 *
 *  - the dirty label / goto can be cleverly changed to a do { } while loop
 *  - we should add the case were value begins with a " or '
 *  - all spaces before or after value are ignored, but NOT inside value
 *  - a (very) simple optimization would be to get indexes of all special chars in one pass:
 *     =, #, first non-null char, last char
 */

int read_config_file(void)
{
	FILE* cfg_file = NULL;
	char *m, *m2;
	char *line, *comment;
        char *ptr;
        unsigned int length;
	char *filename;

	filename = (char *)malloc(256);
	filename = get_config_filename();
	
	m = (char *)malloc(MAXLEN);
        m2 = (char *)malloc(MAXLEN);
	line = m;
	
	if ((cfg_file = fopen((char *)filename, "r")) == NULL)
		goto cleanup;
	
        /* -1 because fgets keeps the \n */
	while (fgets(line, MAXLEN-1, cfg_file)) {
		char *var = (char *)malloc(MAXLEN);
		char *val = (char *)malloc(MAXLEN);
		
dirty_label:
		/* skip emtpy strings */
		if (strlen(line) < 2)
			continue;

                if (line[strlen(line)-1] == '\n')
                	line[strlen(line)-1] = '\0';
		
		/* get rid of whitespaces at the beginning of line */
		while (*line && isspace(*line))
			line++;

		/* skip commented lines and lines without "=" */
		if (!line[0] || line[0] == '#' || !strchr(line, '='))
			continue;

                comment = strchr(line,'#');
                if (comment) {
                  /* first, strip right part of line */
                  	*comment-- = '\0';
                }
                  
                length = strlen(line);

                /* now, strip trailing spaces */
                while ( length > 0 && isspace(line[length-1]) )
                {
                	line[--length] = '\0';
                }

                /* check if var is multi-line */
                if (line[length-1] == '\\') {
                  /* read next line */
                  	if (!fgets(m2, MAXLEN, cfg_file)) {
                    		fprintf(stderr, "nothing more to read, awaiting at least one more line\n");
                    	exit (1);
                  	}
                  
			/* skip leading spaces */
                  	ptr = m2;
                  	while (*ptr && isspace(*ptr))
                    		ptr++;
                  
			/* offset is that hard bcs we moved line from its orig position .. */
                  	/* we use -1 to remove \ */
                  	strncpy(line+length-1, ptr, MAXLEN-length-(line-m));
                  	goto dirty_label;
                }

                var = (char *)strtok_r(line, "=", &val);
		var[strlen(var) - 1] = '\0';
		
                /* remove trailing spaces in var, and leading spaces in value */
                ptr = var + strlen(var) - 1;
                while (ptr > var && isspace(*ptr)) ptr--;
                while (*val && isspace(*val)) val++;

		(void)install(var, val);
	}


	fclose(cfg_file);

cleanup:
	free(filename);
	free(m2);
	free(m);
	
	return 0;
}

char *get_config_item(char *name)
{
	struct hash_t *np;

	if ((np = lookup(name)) != NULL)
		return np->value;
	
	return NULL;
}

	

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
#include <ctype.h>

#include "conf.h"
#include "hash.h"

#define MAXLEN 255

static char *get_config_filename() {
    /*
     * we try to respect XDG Base Directory Specification:
     * http://standards.freedesktop.org/basedir-spec/basedir-spec-0.6.html
     */
    char *config_home;
    char *config_full_path;
    char *xdg_config_home;

    config_home = (char *) malloc(MAXLEN + 1);
    config_full_path = (char *) malloc(MAXLEN + 1);

    xdg_config_home = getenv("XDG_CONFIG_HOME");

    if (xdg_config_home != NULL && strlen(xdg_config_home) != 0) {
        snprintf(config_home, MAXLEN, "%s/.config", xdg_config_home);
    } else {
        char *home;
        home = getenv("HOME");

        if (home != NULL && strlen(home) != 0) {
            snprintf(config_home, MAXLEN, "%s/.config", home);
        } else
            return NULL;
    }

    snprintf(config_full_path, MAXLEN, "%s/cutedf.conf", config_home);
    free(config_home);

    return config_full_path;
}

int init_config(void) {
    FILE *cfg_file = NULL;
    char *m, *m2;
    char *line, *comment;
    char *ptr;
    unsigned int length;
    char *filename;

    install("bracket_color", "blue");
    install("gauge_color", "black");
    install("header_color", "light_yellow");
    install("fs_color", "yellow");
    install("data_color", "default");
    install("perc_color", "cyan");

    install("bracket_background", "default");
    install("gauge_background", "red");
    install("header_background", "blue");
    install("fs_background", "default");
    install("data_background", "default");
    install("perc_background", "default");

    filename = (char *) malloc(MAXLEN + 1);
    filename = get_config_filename();

    if (!filename) {
        fprintf(stderr, "Failed to get config filename\n");
        free(filename);
        return 1;
    }

    m = (char *) malloc(MAXLEN);
    m2 = (char *) malloc(MAXLEN);
    line = m;

    if ((cfg_file = fopen(filename, "r")) == NULL) {
        free(filename);
        free(m2);
        free(m);
        return 1;
    }

    while (fgets(line, MAXLEN - 1, cfg_file)) {
        char *var = (char *) malloc(MAXLEN);
        char *val = (char *) malloc(MAXLEN);

        while (strlen(line) > 1) {
            if (line[strlen(line) - 1] == '\n')
                line[strlen(line) - 1] = '\0';

            /* get rid of whitespaces at the beginning of line */
            while (*line && isspace(*line))
                line++;

            /* skip commented lines and lines without "=" */
            if (!line[0] || line[0] == '#' || !strchr(line, '='))
                break;

            comment = strchr(line, '#');
            if (comment) {
                /* first, strip right part of line */
                *comment-- = '\0';
            }

            length = strlen(line);

            /* now, strip trailing spaces */
            while (length > 0 && isspace(line[length - 1])) {
                line[--length] = '\0';
            }

            /* check if var is multi-line */
            if (line[length - 1] == '\\') {
                /* read next line */
                if (!fgets(m2, MAXLEN, cfg_file)) {
                    fprintf(stderr, "nothing more to read, awaiting at least one more line\n");
                    free(filename);
                    free(m2);
                    free(m);
                    fclose(cfg_file);
                    return 1;
                }

                /* skip leading spaces */
                ptr = m2;
                while (*ptr && isspace(*ptr))
                    ptr++;

                /* offset is that hard bcs we moved line from its orig position... */
                /* we use -1 to remove \ */
                strncpy(line + length - 1, ptr, MAXLEN - length - (line - m));
            }

            break;
        }

        var = strtok_r(line, "=", &val);

        if (var) {
            var[strlen(var) - 1] = '\0';

            /* remove trailing spaces in var, and leading spaces in value */
            ptr = var + strlen(var) - 1;
            while (ptr > var && isspace(*ptr)) ptr--;
            while (*val && isspace(*val)) val++;

            (void) install(var, val);
        }
    }

    fclose(cfg_file);
    free(filename);
    free(m2);
    free(m);

    return 0;
}

char *get_config_item(char *name) {
    struct hash_t *np;

    if ((np = lookup(name)) != NULL)
        return np->value;

    return NULL;
}

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
#include <libmount/libmount.h>

#include "common.h"
#include "colors.h"
#include "conf.h"

double blocksize;
short human_readable;
short show_pseudofs;
int header_showed = 0;

char *bar(unsigned short n) {
    int i = 1;
    char *gauge = (char *) malloc(40);
    char *gauge_symbol = get_config_item("gauge_symbol");

    *gauge = '\0'; /* avoid apparition of artefacts: strcat on non-initialized memory ... */

    if (n > 10)
        return NULL;

    while (i <= n) {
        gauge = strncat(gauge, gauge_symbol, 4);
        i++;
    }

    if (i <= 10)
        snprintf(gauge + strlen(gauge), 40, "%s%*s", RESET_COLOR, 11 - i, " ");

    return gauge;
}

void header(void) {
    if (header_showed == 0) {
        printf("%s%s%-14s %12s %7s %7s %7s %-18s    %5s      %s\n",
               header_background,
               header_color,
               "Filesystem",
               "Type",
               "Total",
               "Used",
               "Avail",
               "Mounted on",
               "Capacity",
               RESET_COLOR
        );
        header_showed = 1;
    }
}

char *numeric_value(const double bytes) {
    char *buf;

    buf = (char *) malloc(256);

    if (human_readable) {
        if ((bytes / 1073741824) >= 1) {
            snprintf(buf, 255, "%6.1fG", (bytes / 1073741824));
        } else if ((bytes / 1048576) >= 1) {
            snprintf(buf, 255, "%6.1fM", (bytes / 1048576));
        } else if ((bytes / 1024) >= 1) {
            snprintf(buf, 255, "%6.1fK", (bytes / 1024));
        } else {
            snprintf(buf, 255, "%7.0f", bytes);
        }
    } else {
        snprintf(buf, 255, "%7.0f", bytes);
    }

    return buf;
}

int check_suffix(char *str, char suffix) {
    size_t str_len = strlen(str);
    char suffix_lower = tolower(suffix);

    if (str_len >= 1 &&
        (!memcmp(str + str_len - 1, &suffix, 1) ||
         !memcmp(str + str_len - 1, &suffix_lower, 1))) {
        str[str_len - 1] = '\0';
        return 1;
    }

    return 0;
}

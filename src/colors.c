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

#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "conf.h"

char *bracket_color;
char *gauge_color;
char *header_color;
char *fs_color;
char *data_color;
char *perc_color;

char *cl(const char *color) {
    if (!color)
        return NULL;
    else if (strcmp(color, "normal") == 0)
        return NORMAL;
    else if (strcmp(color, "red") == 0)
        return RED;
    else if (strcmp(color, "green") == 0)
        return GREEN;
    else if (strcmp(color, "yellow") == 0)
        return YELLOW;
    else if (strcmp(color, "blue") == 0)
        return BLUE;
    else if (strcmp(color, "magenta") == 0)
        return MAGENTA;
    else if (strcmp(color, "cyan") == 0)
        return CYAN;
    else if (strcmp(color, "white") == 0)
        return WHITE;

    return NULL;
}

int read_colors() {
    bracket_color = (char *) malloc(64);
    gauge_color = (char *) malloc(64);
    header_color = (char *) malloc(64);
    fs_color = (char *) malloc(64);
    data_color = (char *) malloc(64);
    perc_color = (char *) malloc(64);


    if (!(bracket_color = cl(get_config_item("bracket_color"))))
        bracket_color = BLUE;
    if (!(gauge_color = cl(get_config_item("gauge_color"))))
        gauge_color = YELLOW;
    if (!(header_color = cl(get_config_item("header_color"))))
        header_color = YELLOW;
    if (!(fs_color = cl(get_config_item("fs_color"))))
        fs_color = CYAN;
    if (!(data_color = cl(get_config_item("data_color"))))
        data_color = NORMAL;
    if (!(perc_color = cl(get_config_item("perc_color"))))
        perc_color = CYAN;

    return 0;
}

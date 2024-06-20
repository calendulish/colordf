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

#include "common.h"
#include "colors.h"
#include "conf.h"

char *bracket_color;
char *gauge_color;
char *header_color;
char *fs_color;
char *data_color;
char *perc_color;

char *bracket_background;
char *gauge_background;
char *header_background;
char *fs_background;
char *data_background;
char *perc_background;

char *cl(const char *color, int flags) {
    if (!color || STREQ(color, "default"))
        return RESET_COLOR;
    else if (STREQ(color, "black"))
        return flags == BACKGROUND ? BACKGROUND_BLACK : BLACK;
    else if (STREQ(color, "red"))
        return flags == BACKGROUND ? BACKGROUND_RED : RED;
    else if (STREQ(color, "green"))
        return flags == BACKGROUND ? BACKGROUND_GREEN : GREEN;
    else if (STREQ(color, "yellow"))
        return flags == BACKGROUND ? BACKGROUND_YELLOW : YELLOW;
    else if (STREQ(color, "blue"))
        return flags == BACKGROUND ? BACKGROUND_BLUE : BLUE;
    else if (STREQ(color, "magenta"))
        return flags == BACKGROUND ? BACKGROUND_MAGENTA : MAGENTA;
    else if (STREQ(color, "cyan"))
        return flags == BACKGROUND ? BACKGROUND_CYAN : CYAN;
    else if (STREQ(color, "gray"))
        return flags == BACKGROUND ? BACKGROUND_GRAY : GRAY;
    else if (STREQ(color, "white"))
        return flags == BACKGROUND ? BACKGROUND_WHITE : WHITE;
    else if (STREQ(color, "light_red"))
        return flags == BACKGROUND ? BACKGROUND_LIGHT_RED : LIGHT_RED;
    else if (STREQ(color, "light_green"))
        return flags == BACKGROUND ? BACKGROUND_LIGHT_GREEN : LIGHT_GREEN;
    else if (STREQ(color, "light_yellow"))
        return flags == BACKGROUND ? BACKGROUND_LIGHT_YELLOW : LIGHT_YELLOW;
    else if (STREQ(color, "light_blue"))
        return flags == BACKGROUND ? BACKGROUND_LIGHT_BLUE : LIGHT_BLUE;
    else if (STREQ(color, "light_magenta"))
        return flags == BACKGROUND ? BACKGROUND_LIGHT_MAGENTA : LIGHT_MAGENTA;
    else if (STREQ(color, "light_cyan"))
        return flags == BACKGROUND ? BACKGROUND_LIGHT_CYAN : LIGHT_CYAN;
    else if (STREQ(color, "light_gray"))
        return flags == BACKGROUND ? BACKGROUND_LIGHT_GRAY : LIGHT_GRAY;
    else if (STREQ(color, "pink"))
        return flags == BACKGROUND ? BACKGROUND_PINK : PINK;
    else if (STREQ(color, "rose"))
        return flags == BACKGROUND ? BACKGROUND_ROSE : ROSE;
    else if (STREQ(color, "orange"))
        return flags == BACKGROUND ? BACKGROUND_ORANGE : ORANGE;
    else if (STREQ(color, "purple"))
        return flags == BACKGROUND ? BACKGROUND_PURPLE : PURPLE;
    else if (STREQ(color, "violet"))
        return flags == BACKGROUND ? BACKGROUND_VIOLET : VIOLET;

    return NULL;
}

int read_colors(void) {
    bracket_color = (char *) malloc(64);
    gauge_color = (char *) malloc(64);
    header_color = (char *) malloc(64);
    fs_color = (char *) malloc(64);
    data_color = (char *) malloc(64);
    perc_color = (char *) malloc(64);
    bracket_background = (char *) malloc(64);
    gauge_background = (char *) malloc(64);
    header_background = (char *) malloc(64);
    fs_background = (char *) malloc(64);
    data_background = (char *) malloc(64);
    perc_background = (char *) malloc(64);

    bracket_color = cl(get_config_item("bracket_color"), 0);
    gauge_color = cl(get_config_item("gauge_color"), 0);
    header_color = cl(get_config_item("header_color"), 0);
    fs_color = cl(get_config_item("fs_color"), 0);
    data_color = cl(get_config_item("data_color"), 0);
    perc_color = cl(get_config_item("perc_color"), 0);

    bracket_background = cl(get_config_item("bracket_background"), BACKGROUND);
    gauge_background = cl(get_config_item("gauge_background"), BACKGROUND);
    header_background = cl(get_config_item("header_background"), BACKGROUND);
    fs_background = cl(get_config_item("fs_background"), BACKGROUND);
    data_background = cl(get_config_item("data_background"), BACKGROUND);
    perc_background = cl(get_config_item("perc_background"), BACKGROUND);

    return 0;
}

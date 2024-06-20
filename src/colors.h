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

#ifndef COLORS_H
#define COLORS_H

#define BACKGROUND 1
#define RESET_COLOR "\033[m"

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define GRAY "\033[90m"
#define WHITE "\033[1;37m"

#define LIGHT_GRAY "\033[1;90m"
#define LIGHT_RED "\033[1;91m"
#define LIGHT_GREEN "\033[1;92m"
#define LIGHT_YELLOW "\033[1;93m"
#define LIGHT_BLUE "\033[1;94m"
#define LIGHT_MAGENTA "\033[1;95m"
#define LIGHT_CYAN "\033[1;96m"

#define BACKGROUND_BLACK "\033[40m"
#define BACKGROUND_RED "\033[41m"
#define BACKGROUND_GREEN "\033[42m"
#define BACKGROUND_YELLOW "\033[43m"
#define BACKGROUND_BLUE "\033[44m"
#define BACKGROUND_MAGENTA "\033[45m"
#define BACKGROUND_CYAN "\033[46m"
#define BACKGROUND_GRAY "\033[100m"
#define BACKGROUND_WHITE "\033[107m"

#define BACKGROUND_LIGHT_RED "\033[101m"
#define BACKGROUND_LIGHT_GREEN "\033[102m"
#define BACKGROUND_LIGHT_YELLOW "\033[103m"
#define BACKGROUND_LIGHT_BLUE "\033[104m"
#define BACKGROUND_LIGHT_MAGENTA "\033[105m"
#define BACKGROUND_LIGHT_CYAN "\033[106m"
#define BACKGROUND_LIGHT_GRAY "\033[47m"

// colors bellow needs 256 colors support
#define PINK "\033[38;5;198m"
#define ROSE "\033[38;5;219m"
#define ORANGE "\033[38;5;208m"
#define PURPLE "\033[38;5;129m"
#define VIOLET "\033[38;5;99m"

#define BACKGROUND_PINK "\033[48;5;198m"
#define BACKGROUND_ROSE "\033[48;5;219m"
#define BACKGROUND_ORANGE "\033[48;5;208m"
#define BACKGROUND_PURPLE "\033[48;5;129m"
#define BACKGROUND_VIOLET "\033[48;5;99m"

char *cl(const char *color, int flags);

int read_colors(void);

extern char *bracket_color;
extern char *gauge_color;
extern char *header_color;
extern char *fs_color;
extern char *data_color;
extern char *perc_color;

extern char *bracket_background;
extern char *gauge_background;
extern char *header_background;
extern char *fs_background;
extern char *data_background;
extern char *perc_background;

#endif

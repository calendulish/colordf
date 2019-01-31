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
 *               2016  Lara Maia <dev@lara.click>
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#define ERROR(s) (void)fprintf(stderr, "%s\n", s)

char *bar(unsigned short n);

void header();

double blocksize;
char bs_suff;
short human_readable;

short show_pseudofs;

short is_pseudofs(const char *fs_type);

char *numeric_value(const double bytes);

#endif

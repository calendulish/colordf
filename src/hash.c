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

#include <string.h>
#include <stdlib.h>

#include "hash.h"

#define HASHSIZE 101
struct hash_t *hashtab[HASHSIZE];

unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct hash_t *lookup(char *s) {
    struct hash_t *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct hash_t *install(char *name, char *value) {
    struct hash_t *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct hash_t *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *) np->value);

    if ((np->value = strdup(value)) == NULL)
        return NULL;

    return np;
}

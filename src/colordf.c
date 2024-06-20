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

#define VERSION "CuteDF v1.0.0"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "colordf.h"
#include "stat.h"
#include "common.h"
#include "colors.h"
#include "conf.h"

static struct option long_options[] = {
        {"show-pseudofs",  no_argument,       NULL, 'a'},
        {"block-size",     required_argument, NULL, 'B'},
        {"human-readable", no_argument,       NULL, 'h'},
        {"fstype",         required_argument, NULL, 't'},
        {"version",        no_argument,       NULL, 'v'},
        {"help",           no_argument,       NULL, 'H'},
        {NULL, 0,                             NULL, 0}
};

int main(int argc, char **argv) {
    int i, ch;
    int option_index = 0;
    char *fs_type = "all";

    blocksize = 1048576;
    show_pseudofs = 0;

    init_config();

    if (get_config_item("human_readable")) {
        if (strtol((const char *) get_config_item("human_readable"), NULL, 0)) {
            human_readable = 1;
            blocksize = 1;
        }
    }

    double block_multiply = 1;
    while ((ch = getopt_long(argc, argv, "HB:aghkmt:v", long_options, &option_index)) != -1)
        switch (ch) {
            case 'a':
                show_pseudofs = 1;
                break;
            case 'B':
                if (check_suffix(optarg, 'K'))
                    block_multiply = 1024;
                else if (check_suffix(optarg, 'M'))
                    block_multiply = 1048576;
                else if (check_suffix(optarg, 'G'))
                    block_multiply = 1073741824;

                blocksize = strtod(optarg, NULL) * block_multiply;
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
                (void) fprintf(stderr, "%s\n\n", VERSION);
                return 0;
            case '?':
                break;
            default:
                show_help();
        }

    argc -= optind;
    argv += optind;

    read_colors();

    if (argc == 0)
        display_all_fs(fs_type);
    else
        for (i = 0; i < argc; i++)
            display_single_fs(argv[i]);

    return 0;
}

static void show_help(void) {
    (void) printf("%s <dev@lara.monster> 2024\n\n"
                  "Options:\n"
                  "\t-B, --block-size=[size]\t    set the blocksize\n"
                  "\t   -k use 1K blocksize\n"
                  "\t   -m use 1M blocksize\n"
                  "\t   -g use 1G blocksize\n\n"
                  "\t-h, --human-readable\t    human-readable output\n"
                  "\t-t, --fstype=[type]\t    show only filesystems of specified type\n"
                  "\t-a, --show-pseudofs\t    show pseudofs\n"
                  "\t-v, --version\t\t    print version and exit\n"
                  "\t-H, --help\t\t    print this text and exit\n\n",
                  VERSION);

    exit(0);
}

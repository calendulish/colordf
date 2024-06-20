colordf
======
[![colordf](https://lara.monster/archive/colordf.png)](https://github.com/calendulish/colordf)

[![GitHub license](https://img.shields.io/badge/license-GPLv2-brightgreen.svg?style=flat)](https://www.gnu.org/licenses/gpl-3.0.html)
[![GitHub release](https://img.shields.io/github/release/calendulish/colordf.svg?style=flat)](https://github.com/calendulish/colordf/releases)

This is a colored and configurable version of df, forked from [cdf](https://sourceforge.net/projects/bmp-plugins.berlios/).  
The df program show information about the file system as size, type, mount point, etc.

Config Options
--------------
colordf support some config options using a config file named:  
~/.config/colordf.conf

default config (special value `default` uses the current terminal config):
```ini
gauge_symbol=▮
human_readable=0
bracket_color=blue
bracket_background=default
gauge_color=red
gauge_background=default
header_color=light_yellow
header_background=blue
fs_color=yellow
fs_background=default
data_color=default
data_background=default
perc_color=cyan
prec_background=default
```

colors available to use with the above options:

| normal colours                                                      | light colours                              | special colours                    |
|---------------------------------------------------------------------|--------------------------------------------|------------------------------------|
| $`\color{black}\textsf{black}`$  $`\color{white}\textsf{(black)}`$  |                                            |                                    |
| $`\color{red}\textsf{red}`$                                         | $`\color{#ff4d4d}\textsf{light\_red}`$     | $`\color{#FF1493}\textsf{pink}`$   |
| $`\color{green}\textsf{green}`$                                     | $`\color{#7FFF00}\textsf{light\_green}`$   | $`\color{#DDA0DD}\textsf{rose}`$   |
| $`\color{#D2691E}\textsf{yellow}`$                                  | $`\color{yellow}\textsf{light\_yellow}`$   | $`\color{orange}\textsf{orange}`$  |
| $`\color{#00008B}\textsf{blue}`$                                    | $`\color{blue}\textsf{light\_blue}`$       | $`\color{#9400D3}\textsf{purple}`$ |
| $`\color{#8B008B}\textsf{magenta}`$                                 | $`\color{magenta}\textsf{light\_magenta}`$ | $`\color{#6600cc}\textsf{violet}`$ |
| $`\color{#008B8B}\textsf{cyan}`$                                    | $`\color{cyan}\textsf{light\_cyan}`$       |                                    |
| $`\color{gray}\textsf{gray}`$                                       | $`\color{#A9A9A9}\textsf{light\_gray}`$    |                                    |
| $`\color{white}\textsf{white}`$  $`\color{black}\textsf{(white)}`$  |                                            |                                    |

Command Line Interface
-----------------
```commandline
CuteDF v1.0.0 <dev@lara.monster> 2024

Options:
        -B, --block-size=[size]     set the blocksize
           -k use 1K blocksize
           -m use 1M blocksize
           -g use 1G blocksize

        -h, --human-readable        human-readable output
        -t, --fstype=[type]         show only filesystems of specified type
        -a, --show-pseudofs         show pseudofs
        -v, --version               print version and exit
        -H, --help                  print this text and exit
```
___________________________________________________________________________________________

You can request improvements and/or new features at https://github.com/calendulish/colordf/issues

The colordf is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.

The colordf is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.

Lara Maia <dev@lara.monster> 2015 ~ 2024

[![Made with](https://img.shields.io/badge/made%20with-girl%20power-f070D0.svg?longCache=true&style=for-the-badge)](https://lara.monster)

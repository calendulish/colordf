cmake_minimum_required(VERSION 3.27)
project(colordf C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -O2 -lm -lmount -pedantic")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LibMount REQUIRED mount)

add_executable(colordf
        src/colors.c
        src/colors.h
        src/common.c
        src/common.h
        src/conf.c
        src/conf.h
        src/colordf.c
        src/hash.c
        src/hash.h
        src/stat.c
        src/stat.h)

target_link_libraries(colordf ${LibMount_LIBRARIES})
target_include_directories(colordf PUBLIC ${LibMount_INCLUDE_DIRS})
target_compile_options(colordf PUBLIC ${LibMount_CFLAGS_OTHER})

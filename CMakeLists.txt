cmake_minimum_required(VERSION 3.27)
project(cutedf C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -O2 -lm -lmount -pedantic")

find_package(ECM NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(LibMount REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LibMount REQUIRED mount)

add_executable(cutedf
        src/colors.c
        src/colors.h
        src/common.c
        src/common.h
        src/conf.c
        src/conf.h
        src/cutedf.c
        src/hash.c
        src/hash.h
        src/stat.c
        src/stat.h)

target_link_libraries(cutedf ${LibMount_LIBRARIES})
target_include_directories(cutedf PUBLIC ${LibMount_INCLUDE_DIRS})
target_compile_options(cutedf PUBLIC ${LibMount_CFLAGS_OTHER})

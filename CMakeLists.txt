cmake_minimum_required(VERSION 3.24)
project(socnetwork2)

set(CMAKE_CXX_STANDARD 14)

include_directories(source/headers)

add_executable(socnetwork2
        resources/usertest.csv
        source/headers/hash_functions.h
        source/headers/hash_table.h
        source/headers/prime.h
        source/sources/hash_functions.c
        source/sources/hash_table.c
        source/sources/prime.c
        source/headers/common.h
        source/headers/community.h
        source/headers/menu.h
        source/headers/user.h
        source/headers/utils.h
        source/sources/community.c
        source/sources/main.c
        source/sources/menu.c
        source/sources/user.c
        source/sources/utils.c source/sources/common.c source/headers/stop_words.h source/sources/stop_words.c)

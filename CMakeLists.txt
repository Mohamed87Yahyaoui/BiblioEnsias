cmake_minimum_required(VERSION 3.17)
project(ProjetBiblioC C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ProjetBiblioC
        adherant.h
        livre.h
        main.c)

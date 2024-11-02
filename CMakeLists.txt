cmake_minimum_required(VERSION 3.28.1)
project(projekt_studia C)

set(CMAKE_C_STANDARD 23)

add_executable(projekt_studia main.c
        geometry.c
        geometry.h
        console_grid.c
        console_grid.h
)

cmake_minimum_required(VERSION 4.0)
project(NoteViewer C)

set(CMAKE_C_STANDARD 99)

add_executable(NoteViewer main.c
        sequence.h
        types.h
        sequence.c
        consts.h
        utils.h
        parse.c
        parse.h
        utils.c
)

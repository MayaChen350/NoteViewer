cmake_minimum_required(VERSION 3.16)
project(NoteViewer C)

set(CMAKE_C_STANDARD 99)

add_executable(noteviewer main.c
        sequence.h
        types.h
        sequence.c
        consts.h
        utils.h
        multiParser.c
        multiParser.h
        singleParser.c
        singleParser.h
        utils.c
)

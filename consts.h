//
// Created by mayachen on 2025-09-20.
//

#ifndef NOTEVIEWER_CONSTS_H
// Consts and etc
#define NOTEVIEWER_CONSTS_H
#include <stdint.h>

// I'm sure this makes sense trust plus why not a bit of conditional macros magic
#if INTPTR_MAX == INT32_MAX
#define CHUNK_SIZE 32
#elif INTPTR_MAX == INT64_MAX
#define CHUNK_SIZE 64
#elif INTPTR_MAX == INT16_MAX
#define CHUNK_SIZE 16
#elif INTPTR_MAX == INT128_MAX
// Future-proof design
#define CHUNK_SIZE 128
#else
#error "Compilation failure. I don't think this will work on your computer."
#endif

#endif //NOTEVIEWER_CONSTS_H
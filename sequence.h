//
// Created by mayachen on 2025-09-19.
//

#ifndef NOTEVIEWER_SEQUENCE_H
#define NOTEVIEWER_SEQUENCE_H
#include <stddef.h>

#include "consts.h"
#include "types.h"

struct sequence_strs {
    str elem;
    struct sequence_strs *next;
};

typedef struct sequence_strs sequence_t;

sequence_t *attach(sequence_t *curr_seq_ptr, str new_elem);

str assemble_str(sequence_t *seq, const wchar_t rest_of_the_chars[CHUNK_SIZE / sizeof(wchar_t)]);


#endif //NOTEVIEWER_SEQUENCE_H

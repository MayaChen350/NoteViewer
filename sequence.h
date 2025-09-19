//
// Created by mayachen on 2025-09-19.
//

#ifndef NOTEVIEWER_SEQUENCE_H
#define NOTEVIEWER_SEQUENCE_H

struct sequence_strs {
    char *elem;
    struct sequence_strs *next;
};

typedef struct sequence_strs sequence_t;

sequence_t *attach(sequence_t *curr_seq_ptr, char *new_elem);


#endif //NOTEVIEWER_SEQUENCE_H

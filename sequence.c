//
// Created by mayachen on 2025-09-19.
//

#include "sequence.h"
#include <stdlib.h>

sequence_t *attach(sequence_t *curr_seq_ptr, char *new_elem) {
    sequence_t *new_seq_ptr = malloc(sizeof(sequence_t));
    new_seq_ptr->elem = new_elem;

    curr_seq_ptr->next = new_seq_ptr;
    return new_seq_ptr;
}

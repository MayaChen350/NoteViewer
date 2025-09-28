//
// Created by mayachen on 2025-09-19.
//

#include "sequence.h"
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "types.h"

// Returns a pointer to the `next` element.
sequence_t *attach(sequence_t *curr_seq_ptr, const str new_elem) {
    sequence_t *new_seq_ptr = malloc(sizeof(sequence_t));
    new_seq_ptr->elem = new_elem;

    curr_seq_ptr->next = new_seq_ptr;
    return new_seq_ptr;
}

// The seq should be NULL at the end
str assemble_str(sequence_t *seq, const wchar_t rest_of_the_chars[CHUNK_SIZE / sizeof(wchar_t)]) {
    void *backup = seq; // Save starting addresses
    wchar_t *ret_str;

    // I'm sure the compiler will be glad to optimize this "scope" :clueless:
    {
        size_t len = wcslen(rest_of_the_chars);
        // Reused pointer backup variable
        while (seq->elem != NULL) {
            len += wcslen(seq->elem);
            seq = seq->next; // truly the peakest type of loops
        }

        ret_str = malloc((len + 1) * sizeof(wchar_t));
    }

    seq = (sequence_t *) backup;
    backup = ret_str;

    while (seq->elem != NULL) {
        wcscpy(ret_str, seq->elem);
        ret_str += wcslen(seq->elem);
        sequence_t *old_seq = seq;
        seq = seq->next;
        free(old_seq); // it has served its purpose
        // it can now enjoy crystal stasis
    }

    free(seq);
    wcscpy(ret_str, rest_of_the_chars); // it fits well its name

    ret_str = backup;

    return ret_str;
}

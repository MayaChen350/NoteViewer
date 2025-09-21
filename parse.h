//
// Created by mayachen on 2025-09-20.
//

#ifndef NOTEVIEWER_PARSE_H
#define NOTEVIEWER_PARSE_H
#include <stdio.h>

#include "sequence.h"

void parse_file_content(FILE *file, const wchar_t *word_to_base_output_on, sequence_t const**curr_seq_ptr);
#endif //NOTEVIEWER_PARSE_H
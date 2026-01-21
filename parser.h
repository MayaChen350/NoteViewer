//
// Created by mayachen on 2025-09-20.
//

#ifndef NOTEVIEWER_PARSE_H
#define NOTEVIEWER_PARSE_H
#include <stdio.h>

#include "sequence.h"

typedef enum { UNDEFINED, READING_TAG, SKIP, SAVE } ReadingState;
typedef struct {
  // wchar_t *parsed_content;
  ReadingState reading_state;
} Parser;

Parser parser_init(); 
void parse();

#endif // NOTEVIEWER_PARSE_H

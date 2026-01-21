//
// Created by mayachen on 2025-09-19.
//

#ifndef NOTEVIEWER_SEQUENCE_H
#define NOTEVIEWER_SEQUENCE_H
#include <stddef.h>

#include "consts.h"
#include "types.h"

struct seq_element {
  void *elem;
  struct seq_element *next;
};

struct sequence {
  struct seq_element *head;
  struct seq_element *tail;
};

typedef struct sequence seq_t;
typedef struct seq_element seq_elem;

seq_t *seq_init(seq_t *self);
seq_t *seq_create(); 
void seq_destroy(seq_t *self, void (*elem_destroy)(void *));

void seq_attach(seq_t *self, void *new_elem);

#endif // NOTEVIEWER_SEQUENCE_H

//
// Created by mayachen on 2025-09-19.
//

#include <stdlib.h>

#include "sequence.h"

seq_elem *seq_elem_create(void *elem) {
  seq_elem *it = malloc(sizeof(seq_elem));
  it->elem = elem;
  it->next = NULL;

  return it;
}

seq_t *seq_init(seq_t *self) {
  self->head = self->tail = NULL;
  return self;
}

seq_t *seq_create(void) {
  seq_t *seq = malloc(sizeof(seq_t));

  return seq_init(seq);
}

// DESTROY EACH ELEMENT WITH seq_destroy //

void seq_attach_first(seq_t *self, void *new_elem) {
  self->head = self->tail = seq_elem_create(new_elem);
}

// Attach a new element to the chain.
void seq_attach(seq_t *self, void *new_elem) {
  if (self->head == NULL)
    return seq_attach_first(self, new_elem);

  self->tail = self->tail->next = seq_elem_create(new_elem);
}

void seq_destroy(seq_t *self, void (*elem_destroy)(void *)) {
  seq_elem *el = self->head;
  while (el != NULL) {
    elem_destroy(el->elem);
    seq_elem *next = el->next;

    free(el);

    el = next;
  };
}

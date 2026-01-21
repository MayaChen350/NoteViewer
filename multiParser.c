#include "multiParser.h"
#include "parser.h"
#include "sequence.h"
#include <stdlib.h>
#include <wchar.h>

typedef struct {
  wchar_t *name;
  wchar_t *parsed_content;
} Tag;

static Tag *tag_create(str name, size_t name_len) {
  Tag *tag = malloc(sizeof(*tag));

  tag->name = wcsdup(name);

  tag->parsed_content = NULL;

  return tag;
}

static void tag_destroy(Tag *self) {
  free(self->name);
  free(self->parsed_content);
  free(self);
}

typedef struct {
  Parser super;
  seq_t /*<elem: Tag>*/ tags;
} MultiParser;

static MultiParser multiParser_init() {
  MultiParser self;
  self.super = parser_init();
  self.tags = *seq_init(&self.tags);

  return self;
}

static void multiParser_clean(MultiParser *self) {
  seq_destroy(&self->tags, (void (*)(void *))tag_destroy);
}

const char *multiParse(FILE *file) {
  MultiParser parser = multiParser_init();

  return "";
}

#include "parser.h"
#include <stdlib.h>
#include <wchar.h>

Parser parser_init() {
  Parser self;
  self.reading_state = READING_TAG;
  return self;
}

void parse() {
  Parser parser = parser_init();
}

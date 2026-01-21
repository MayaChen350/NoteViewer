#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "consts.h"
#include "sequence.h"
#include "multiParser.h"
#include "singleParser.h"
#include "types.h"

int main(int argc, char **argv) {
  // TODO: Read each files in the current directory with idk what criteria yet

  FILE *file = fopen("test.txt", "r");

  if (strcmp(argv[1], "--single"))
    if (argv[2] == NULL) {
      printf("Missing arguments.");
      return 1;
    }
    else {
      size_t arg2_len = strlen(argv[2]);
      wchar_t *word_to_base_output_on = malloc(sizeof(wchar_t) * arg2_len);
      mbstowcs(word_to_base_output_on, argv[2], arg2_len);
      printf("%s", singleParse(file, word_to_base_output_on));
    }
  else {
      printf("%s", multiParse(file));
  }

  return 0;
}

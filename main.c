#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "consts.h"
#include "parse.h"
#include "sequence.h"
#include "types.h"



int main(int argc, char **argv) {
    // TODO: Read each files in the current directory with idk what criteria yet

    FILE *file = fopen("test.txt", "r");

    const char *arg2 = argv[1];
    wchar_t *word_to_base_output_on = alloca(sizeof(wchar_t)*strlen(arg2)); // allocated on the stack because speed
    mbstowcs(word_to_base_output_on, arg2, strlen(arg2));

    sequence_t main_sequence_of_chars; // Also the start of sequence
    sequence_t *seq_ptr = &main_sequence_of_chars; // movable pointer, start at the thing above

    parse_file_content(file, word_to_base_output_on, &seq_ptr);
    fclose(file);

    // TODO: Formatting
    while (main_sequence_of_chars.next != NULL) {
        seq_ptr = &main_sequence_of_chars;
        wprintf(L"%ls", seq_ptr->elem);

        // no time to free anything

        seq_ptr = seq_ptr->next;
    }

    return 0;
}
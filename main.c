#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <wchar.h>

#include "sequence.h"
#include "types.h"

// I'm sure this makes sense trust plus why not a bit of conditional macros magic
#if INTPTR_MAX == INT32_MAX
#define CHUNK_SIZE 32
#elif INTPTR_MAX == INT64_MAX
#define CHUNK_SIZE 64
#elif INTPTR_MAX == INT16_MAX
#define CHUNK_SIZE 16
#elif INTPTR_MAX == INT128_MAX
// Future-proof design
#define CHUNK_SIZE 128
#else
#error "Compilation failure. I don't think this will work on your computer."
#endif

int main(int argc, char **argv) {
    // TODO: Read each files in the current directory with idk what criteria yet

    FILE *file = fopen("test.txt", "r");

    char *word_to_base_output_on = argv[1];
    // TODO: Replace by wchar_t later on
    int curr_char = fgetc(file);

    while (curr_char != '[' && curr_char != EOF)
        curr_char = fgetc(file);

    int line_counter = 1;

    str string_to_save = NULL;
    int string_size = 0;

    sequence_t start_of_sequence;
    start_of_sequence.elem = string_to_save;
    start_of_sequence.next = NULL;

    sequence_t *current_seq_elem = &start_of_sequence;

    enum reading_state_t {
        UNDEFINED,
        READING_TITLE,
        SKIP,
        SAVE
    };

    enum reading_state_t reading_state = UNDEFINED;

    // Chunk of bytes to consume from the file everytime
    wchar_t current_chunk[CHUNK_SIZE / sizeof(wchar_t)];

    // TODO: Send to threads and queues
    while (fgetws(current_chunk, CHUNK_SIZE / sizeof(wchar_t), file) != NULL) {
        for (int i = 0; i < CHUNK_SIZE / sizeof(wchar_t); i++) {
            curr_char = current_chunk[i];
            if (curr_char == '\n') {
                line_counter++;
            }

            switch (reading_state) {
                case SKIP:
                case SAVE:
                case UNDEFINED:
                    if (curr_char == '[') {
                        if (reading_state == SAVE) {
                            attach(current_seq_elem, string_to_save);
                        }

                        reading_state = READING_TITLE;
                        string_to_save = file->_IO_write_ptr + 1;
                        string_size = 0;
                    } else if (reading_state == SAVE) string_size++;
                    break;
                case READING_TITLE:
                    if (curr_char == ']') {
                        // Error handling
                        if (string_size == 0) {
                            fprintf(stderr, "Empty tag at %i", line_counter);
                            exit(EXIT_FAILURE);
                        }

                        if (strcmp(word_to_base_output_on, string_to_save) != 0)
                            reading_state = SKIP;
                        else {
                            string_to_save = file->_IO_write_ptr + 1;
                            reading_state = SAVE;
                        }
                    } else string_size++;
                    break;
            }
        }
    }


    // TODO: Formatting
    while (start_of_sequence.next != NULL) {
        printf("%s", start_of_sequence.next->elem);
    }

    return 0;
}

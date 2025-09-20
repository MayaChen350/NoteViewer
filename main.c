#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "consts.h"
#include "sequence.h"
#include "types.h"

int main(int argc, char **argv) {
    // TODO: Read each files in the current directory with idk what criteria yet

    FILE *file = fopen("test.txt", "r");

    const str word_to_base_output_on = alloca(sizeof(wchar_t)*strlen(argv[1]));
    mbtowc(word_to_base_output_on, argv[1], strlen(argv[1]));
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
    wchar_t reading_chars[wcslen(word_to_base_output_on) + 1];
    int reading_chars_index = 0;

    // Chunk of bytes to consume from the file everytime
    wchar_t current_chunk[CHUNK_SIZE / sizeof(wchar_t)];
    sequence_t *stack_of_chunks;

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
                            wchar_t chars_saved_so_far[CHUNK_SIZE / sizeof(wchar_t)];
                            wcslcpy(chars_saved_so_far, current_chunk, i);
                            const str new_string = assemble_str(stack_of_chunks, chars_saved_so_far);
                            attach(current_seq_elem, new_string);
                        }

                        reading_state = READING_TITLE;
                        stack_of_chunks = malloc(sizeof(sequence_t));
                        string_size = 0;
                    } else if (reading_state == SAVE) string_size++; // this basically becomes the evil twin chunk index
                    break;
                case READING_TITLE:
                    if (curr_char == ']') {
                        // Error handling
                        if (string_size == 0) {
                            fprintf(stderr, "Empty tag at %i", line_counter);
                            exit(EXIT_FAILURE);
                        }

                        if (wcslen(word_to_base_output_on) != string_size
                            || wcpcpy(word_to_base_output_on, reading_chars) != 0) {
                            reading_state = SKIP;
                        } else {
                            reading_state = SAVE;
                        }
                    } else {
                        string_size++;
                        if (string_size <= wcslen(word_to_base_output_on)) {
                            reading_chars[reading_chars_index] = curr_char;
                            reading_chars_index++;
                        } else {
                            reading_state = SKIP;
                            // bzero(reading_chars, strlen(word_to_base_output_on)); /// no need

                            reading_chars[reading_chars_index] = 0;
                            // resetting this index will be enough since it will overwrite the earlier string
                            // plus, this string is only compared to its right length
                        }
                    }
                    break;
            }
        }

        if (reading_state == SAVE) {
            attach(stack_of_chunks, current_chunk); // if it's null deal with it
            string_size = 0;
        }
    }


    // TODO: Formatting
    while (start_of_sequence.next != NULL) {
        printf("%ls", (*start_of_sequence.next).elem);

        // no time to free anything

        start_of_sequence = *start_of_sequence.next;
    }

    return 0;
}

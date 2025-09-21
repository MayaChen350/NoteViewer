//
// Created by mayachen on 2025-09-20.
//

#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "sequence.h"

// not global functions to give the compiler for dinner //

void advance_file_ptr_or_fail(FILE *const*file);

// Insane I finally used pointers of pointers
void save_chars(wchar_t current_chunk[CHUNK_SIZE / sizeof(wchar_t)],
                int string_size,
                sequence_t *const*stack_of_chunks,
                sequence_t **seq_ptr
);

enum reading_state_t {
    UNDEFINED,
    READING_TITLE,
    SKIP,
    SAVE
};

// File reading state. (Please use the pointer instead for ARM's sake)
enum reading_state_t reading_statee;

// ARM cpus will thank me for putting this variable nearby
//
// If it's even put nearby
enum reading_state_t __attribute__((section(".text"))) *const reading_state_ptr = &reading_statee;

void save_chars(wchar_t current_chunk[CHUNK_SIZE / sizeof(wchar_t)],
                const int string_size,
                sequence_t *const*stack_of_chunks,
                sequence_t ***seq_ptr
) {
    wchar_t chars_saved_so_far[CHUNK_SIZE / sizeof(wchar_t)];
    wcslcpy(chars_saved_so_far, current_chunk, string_size);
    const str new_string = assemble_str(*stack_of_chunks, chars_saved_so_far);
    *seq_ptr = attach(*seq_ptr, new_string);
}

void advance_file_ptr_or_fail(FILE *const*file) {
    wchar_t curr_char;

    while ((curr_char = fgetc(*file) != '['))
        if (curr_char == EOF)
            perror("File format error. No tags found!");

    *reading_state_ptr = READING_TITLE;
}

void parse_file_content(FILE *file, const wchar_t *word_to_base_output_on, sequence_t const **curr_seq_ptr) {
    advance_file_ptr_or_fail(&file);

    int line_counter = 1;

    int string_size = 0;

    sequence_t start_of_sequence;
    start_of_sequence.elem = NULL;
    start_of_sequence.next = NULL;

    sequence_t *current_seq_elem = &start_of_sequence;


    wchar_t reading_chars[wcslen(word_to_base_output_on) + 1];
    int reading_chars_index = 0;

    // Chunk of bytes to consume from the file everytime
    wchar_t current_chunk[CHUNK_SIZE / sizeof(wchar_t)];
    sequence_t *stack_of_chunks;

    // TODO: Send to threads and queues
    while (fgetws(current_chunk, CHUNK_SIZE / sizeof(wchar_t), file) != NULL) {
        wchar_t *curr_char_ptr = alloca(sizeof(wchar_t));
        for (int i = 0; i < CHUNK_SIZE / sizeof(wchar_t); i++) {
            wchar_t curr_char = *curr_char_ptr;
            if (curr_char == '\n') {
                line_counter++;
            }

            switch (*reading_state_ptr) {
                case SKIP:
                case SAVE:
                case UNDEFINED:
                    if (curr_char == '[') {
                        if (*reading_state_ptr == SAVE) {
                            save_chars(current_chunk, string_size, &stack_of_chunks, curr_seq_ptr);
                        }

                        *reading_state_ptr = READING_TITLE;
                        stack_of_chunks = malloc(sizeof(sequence_t));
                        string_size = 0;
                    } else if (*reading_state_ptr == SAVE) string_size++;
                    // this basically becomes the evil twin chunk index
                    break;
                case READING_TITLE:
                    if (curr_char == ']') {
                        // Error handling
                        if (string_size == 0) {
                            fprintf(stderr, "Empty tag at %i", line_counter);
                            exit(EXIT_FAILURE);
                        }

                        if (wcslen(word_to_base_output_on) != string_size
                            || wcscmp(word_to_base_output_on, reading_chars) != 0) {
                            *reading_state_ptr = SKIP;
                        } else {
                            *reading_state_ptr = SAVE;
                        }
                    } else {
                        string_size++;
                        if (string_size <= wcslen(word_to_base_output_on)) {
                            reading_chars[reading_chars_index] = curr_char;
                            reading_chars_index++;
                        } else {
                            *reading_state_ptr = SKIP;
                            // bzero(reading_chars, strlen(word_to_base_output_on)); /// no need

                            reading_chars[reading_chars_index] = 0;
                            // resetting this index will be enough since it will overwrite the earlier string
                            // plus, this string is only compared to its right length
                        }
                    }
                    break;
            }
        }

        if (*reading_state_ptr == SAVE) {
            attach(stack_of_chunks, current_chunk); // if it's null deal with it
            string_size = 0;
        }
    }
}

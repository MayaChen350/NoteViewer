//
// Created by mayachen on 2025-09-20.
//

//
// Created by mayachen on 2025-09-20.
//

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>


// "Throw with error code"
void throww_errcode(const char *err_msg, const int err_code) {
    perror(err_msg);
    exit(err_code);
}

// Throw an error like it was a high level language (okay it doesn't print the stack trace)
inline void throw(const char *err_msg) {
    throww_errcode(err_msg, 1);
}

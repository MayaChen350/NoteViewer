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

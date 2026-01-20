//
// Created by mayachen on 2025-09-20.
//

#ifndef NOTEVIEWER_UTILS_H
#define NOTEVIEWER_UTILS_H

void throww_errcode(const char *err_msg, int err_code);

// Throw an error like it was a high level language (okay it doesn't print the
// stack trace)
inline void throww(const char *err_msg) { throww_errcode(err_msg, 1); }

#endif // NOTEVIEWER_UTILS_H

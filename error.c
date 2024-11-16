// error.c
// Riešenie IJC-DU1, príklad B), 25.3.2024
// Autor: Ronald Bednár (xbednar00), FIT
// Preložené: Apple Clang 15.0.0

#include <stdarg.h>
#include <stdio.h>
#include "error.h"
#include <stdlib.h>

void warning(const char *fmt, ...) {
    fprintf(stderr, "Warning: ");
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void error_exit(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}

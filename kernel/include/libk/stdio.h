#ifndef _LIBK_STDIO_H
#define _LIBK_STDIO_H 

#include <stdbool.h>
#include <stddef.h>

#define EOF (-1)

bool print(const char* data, size_t lenght);
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

#endif

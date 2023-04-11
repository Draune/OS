#ifndef _LIBK_STDLIB_H
#define _LIBK_STDLIB_H
#include <stddef.h>

void* malloc(size_t memory_size);

void free(void * pointer);

void* realloc(void* pointer, size_t memory_size);

#endif
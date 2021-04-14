#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>

static void* safe_malloc(size_t n, unsigned long line)
{
    void* p = malloc(n);
    if (!p)
    {
        fprintf(stderr, "[%s:%ul]Out of memory(%ul bytes)\n",
            __FILE__, line, (unsigned long)n);
        exit(EXIT_FAILURE);
    }
    return p;
}
#define SAFEMALLOC(n) safe_malloc(n, __LINE__)

#endif // UTILS_H_
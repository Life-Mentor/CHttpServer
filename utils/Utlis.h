#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include <stdio.h>
#include <assert.h> 

typedef struct {
    size_t size;
    char *data;
} ResponseBuffer;

ResponseBuffer *CreateBuffer(ResponseBuffer *buffer, size_t bufferSize);

void die(char *s);
#endif

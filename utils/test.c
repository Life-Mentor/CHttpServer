#include "./Utlis.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    ResponseBuffer *buffer = NULL;
    CreateBuffer(buffer, 1024);
    printf("%zu\n",buffer->size);
    return EXIT_SUCCESS;
}


#include "./Utlis.h"

ResponseBuffer *CreateBuffer(ResponseBuffer *Buffer, size_t BufferSize)
{
    if (NULL == Buffer) {
        die("BufferError:");
    }
    Buffer->size = BufferSize;
    Buffer->data = (char *)malloc(BufferSize * sizeof(char *));
    if (Buffer->data == NULL) {
        die("BufferError");
    }

    return Buffer;
}

void die(char *s)
{
    perror(s);
    exit(1);
}


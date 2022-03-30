#ifndef RINGBUFFERGENERIC_H
#define RINGBUFFERGENERIC_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    void *buffer;
    void *bufferEnd;
    size_t bufferSize;
    size_t itemSize;
    void *head;
    void *tail;
    size_t count;
}Ringbuffer_t;

bool RingbufferInit(Ringbuffer_t *buff, size_t buffSize, size_t itemSize);
void RingbufferDeInit(Ringbuffer_t *buff);
bool RingbufferIsEmpty(Ringbuffer_t *buff);
void RingbufferPushItem(Ringbuffer_t *buff, void *item);
bool RingbufferGetItem(Ringbuffer_t *buff, void *item);

#endif /* RINGBUFFERGENERIC_H */
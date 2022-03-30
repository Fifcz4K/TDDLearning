#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    void *buffer;
    void *bufferEnd;
    size_t bufferSize;
    size_t itemSize;
    size_t count;
    void *head;
    void *tail;
}Ringbuffer_t;

bool RingbufferInit(Ringbuffer_t *ringbuffer, size_t bufferSize, size_t itemSize);
void RingbufferDeInit(Ringbuffer_t *ringbuffer);
bool RingbufferIsEmpty(Ringbuffer_t *ringbuffer);
void RingbufferPushItem(Ringbuffer_t *ringbuffer, void *item);
bool RingbufferGetItem(Ringbuffer_t *ringbuffer, void *item);

#endif // RINGBUFFER_H

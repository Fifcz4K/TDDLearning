#include "Ringbuffer.h"

bool RingbufferInit(Ringbuffer_t *ringbuffer, size_t bufferSize, size_t itemSize)
{
    ringbuffer->buffer = malloc(bufferSize * itemSize);
    if(ringbuffer->buffer == NULL)
        return false;
    
    ringbuffer->bufferEnd = (char*)ringbuffer->buffer + (bufferSize * itemSize);
    ringbuffer->bufferSize = bufferSize;
    ringbuffer->itemSize = itemSize;
    ringbuffer->count = 0;
    ringbuffer->head = ringbuffer->buffer;
    ringbuffer->tail = ringbuffer->buffer;

    return true;
}

void RingbufferDeInit(Ringbuffer_t *ringbuffer)
{
    free(ringbuffer->buffer);
    ringbuffer->count = 0;
}

bool RingbufferIsEmpty(Ringbuffer_t *ringbuffer)
{
    if(ringbuffer->count == 0)
    {
        if(ringbuffer->head == ringbuffer->tail)
        {
            return true;
        }
    }
    
    return false;
}

void RingbufferPushItem(Ringbuffer_t *ringbuffer, void *item)
{
    ringbuffer->count++;
    if(ringbuffer->count > ringbuffer->bufferSize)
    {
        ringbuffer->count = ringbuffer->bufferSize;
        ringbuffer->tail = (char*)ringbuffer->tail + ringbuffer->itemSize;
        if(ringbuffer->tail == ringbuffer->bufferEnd)
        {
            ringbuffer->tail = ringbuffer->buffer;
        }
    }

    memcpy(ringbuffer->head, item, ringbuffer->itemSize);
    ringbuffer->head = (char*)ringbuffer->head + ringbuffer->itemSize;
    if(ringbuffer->head == ringbuffer->bufferEnd)
    {
        ringbuffer->head = ringbuffer->buffer;
    }
}

bool RingbufferGetItem(Ringbuffer_t *ringbuffer, void *item)
{
    if(RingbufferIsEmpty(ringbuffer))
        return false;

    ringbuffer->count--;

    memcpy(item, ringbuffer->tail, ringbuffer->itemSize);

    ringbuffer->tail = (char*)ringbuffer->tail + ringbuffer->itemSize;
    if(ringbuffer->tail == ringbuffer->bufferEnd)
    {
        ringbuffer->tail = ringbuffer->buffer;
    }

    return true;
}
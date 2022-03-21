#include "RingbufferGeneric.h"

bool RingbufferInit(Ringbuffer_t *buff, size_t buffSize, size_t itemSize)
{
    buff->buffer = malloc(buffSize * itemSize);

    if(buff->buffer == NULL)
    {
        return false;
    }

    buff->bufferSize = buffSize;
    buff->itemSize = itemSize;
    buff->count = 0;

    buff->bufferEnd = (char*)buff->buffer + (buffSize * itemSize);
    buff->head = buff->buffer;
    buff->tail = buff->buffer;

    return true;
}

void RingbufferDeInit(Ringbuffer_t *buff)
{
    free(buff->buffer);
    buff->bufferSize = 0;
    buff->itemSize = 0;
    buff->count = 0;
}

bool RingbufferIsEmpty(Ringbuffer_t *buff)
{
    if(buff->count == 0)
    {
        if(buff->head == buff->tail)
        {
            return true;
        }
    }

    return false;    
}

void RingbufferPushItem(Ringbuffer_t *buff, void *item)
{
    if(++buff->count > buff->bufferSize)
    {
        buff->count = buff->bufferSize;
        buff->tail = (char*)buff->tail + buff->itemSize;
        if(buff->tail == buff->bufferEnd)
            buff->tail = buff->buffer;
    }

    memcpy(buff->head, item, buff->itemSize);
    buff->head = (char*)buff->head + buff->itemSize;
    if(buff->head == buff->bufferEnd)
        buff->head = buff->buffer;
}

bool RingbufferGetItem(Ringbuffer_t *buff, void *item)
{
    if(buff->count == 0)
        return false;

    memcpy(item, buff->tail, buff->itemSize);

    buff->count--;
    buff->tail = (char*)buff->tail + buff->itemSize;
    if(buff->tail == buff->bufferEnd)
        buff->tail = buff->buffer;

    return true;
}
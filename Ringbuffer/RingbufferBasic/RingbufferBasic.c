#include "RingbufferBasic.h"

void RingbufferInit(Ringbuffer_t *buff)
{
    memset(buff->items, 0, sizeof(Item_t) * RINGBUFFER_SIZE);
    buff->head = 0;
    buff->tail = 0;
    buff->count = 0;
}

bool RingbufferIsEmpty(Ringbuffer_t *buff)
{
    if(buff->count == 0)
        return true;

    return false;
}

void RingbufferAddItem(Ringbuffer_t *buff, Item_t item)
{
    buff->items[buff->head++] = item;
    buff->head %= RINGBUFFER_SIZE;
    if(++buff->count > RINGBUFFER_SIZE)
    {
        buff->count = RINGBUFFER_SIZE;
        buff->tail = (buff->tail + 1) % RINGBUFFER_SIZE;
    }
}

bool RingbufferReceiveItem(Ringbuffer_t *buff, Item_t *item)
{
    if(buff->count == 0)
        return false;

    *item = buff->items[buff->tail++];
    buff->tail %= RINGBUFFER_SIZE;
    buff->count--;

    return true;
}
#include "unity.h"
#include "Ringbuffer.h"

Ringbuffer_t ringbuffer;
typedef uint32_t item_t;
#define BUFFER_SIZE 100
#define ITEM_SIZE sizeof(item_t)

void setUp(void)
{
    RingbufferInit(&ringbuffer, BUFFER_SIZE, ITEM_SIZE);
}

void tearDown(void)
{
    RingbufferDeInit(&ringbuffer);
}

void test_init(void)
{
    TEST_ASSERT(ringbuffer.buffer);
    TEST_ASSERT_EQUAL_PTR(ringbuffer.buffer + (BUFFER_SIZE * ITEM_SIZE), ringbuffer.bufferEnd);
    TEST_ASSERT_EQUAL(BUFFER_SIZE, ringbuffer.bufferSize);
    TEST_ASSERT_EQUAL(ITEM_SIZE, ringbuffer.itemSize);
    TEST_ASSERT_EQUAL(0, ringbuffer.count);
    TEST_ASSERT_EQUAL_PTR(ringbuffer.buffer, ringbuffer.head);
    TEST_ASSERT_EQUAL_PTR(ringbuffer.buffer, ringbuffer.tail);
    TEST_ASSERT(RingbufferIsEmpty(&ringbuffer));
}

void test_get_from_empty_ringbuffer_returns_false(void)
{
    item_t received = 0;
    TEST_ASSERT_EQUAL(false, RingbufferGetItem(&ringbuffer, &received));
}

void test_not_empty_after_pushing_item(void)
{
    item_t itemToPush = 25;
    RingbufferPushItem(&ringbuffer, &itemToPush);

    TEST_ASSERT_EQUAL(false, RingbufferIsEmpty(&ringbuffer));
}

void test_get_pushed_item(void)
{
    item_t toPush = 25, toReceive = 0;
    RingbufferPushItem(&ringbuffer, &toPush);

    TEST_ASSERT(RingbufferGetItem(&ringbuffer, &toReceive));
    TEST_ASSERT_EQUAL(toPush, toReceive);
}

void test_push_and_get_2_elements(void)
{
    item_t toPush1 = 0xAA, toPush2 = 0xBB;
    item_t toReceive1 = 0, toReceive2 = 0;

    RingbufferPushItem(&ringbuffer, &toPush1);
    RingbufferPushItem(&ringbuffer, &toPush2);

    TEST_ASSERT(RingbufferGetItem(&ringbuffer, &toReceive1));
    TEST_ASSERT(RingbufferGetItem(&ringbuffer, &toReceive2));

    TEST_ASSERT_EQUAL(toPush1, toReceive1);
    TEST_ASSERT_EQUAL(toPush2, toReceive2);
    
}

void test_push_max_get_all_then_push_one_item_and_get_it(void)
{
    item_t *expectedValues = (item_t*)malloc(BUFFER_SIZE * ITEM_SIZE);
    item_t *receivedValues = (item_t*)malloc(BUFFER_SIZE * ITEM_SIZE);
    item_t toPush = 0, toGet = 0;
    size_t getCounter = 0;

    for(size_t i = 0; i < BUFFER_SIZE; i++)
    {
        toPush = (item_t)i;
        expectedValues[i] = toPush;
        RingbufferPushItem(&ringbuffer, &toPush);
    }

    TEST_ASSERT_EQUAL(false, RingbufferIsEmpty(&ringbuffer));

    while(RingbufferGetItem(&ringbuffer, &receivedValues[getCounter]))
    {
        getCounter++;
    }

    TEST_ASSERT_EQUAL(true, RingbufferIsEmpty(&ringbuffer));
    TEST_ASSERT_EQUAL(BUFFER_SIZE, getCounter);
    TEST_ASSERT_EQUAL_MEMORY(expectedValues, receivedValues, BUFFER_SIZE);

    toPush = 0xAA;
    RingbufferPushItem(&ringbuffer, &toPush);

    TEST_ASSERT_EQUAL(false, RingbufferIsEmpty(&ringbuffer));
    TEST_ASSERT(RingbufferGetItem(&ringbuffer, &toGet));
    TEST_ASSERT_EQUAL(toPush, toGet);
    TEST_ASSERT_EQUAL(true, RingbufferIsEmpty(&ringbuffer));

    free(expectedValues);
    free(receivedValues);
}

void test_push_max_twice_and_get_all_stored_items(void)
{
    item_t *expectedValues = (item_t*)malloc(BUFFER_SIZE * ITEM_SIZE);
    item_t *receivedValues = (item_t*)malloc(BUFFER_SIZE * ITEM_SIZE);
    item_t toPush = 0;
    size_t getCounter = 0;

    for(size_t i = 0; i < BUFFER_SIZE * 2; i++)
    {
        toPush = (item_t)i;
        RingbufferPushItem(&ringbuffer, &toPush);
        if(i >= BUFFER_SIZE)
            expectedValues[i - BUFFER_SIZE] = toPush;
    }

    TEST_ASSERT_EQUAL(false, RingbufferIsEmpty(&ringbuffer));

    while(RingbufferGetItem(&ringbuffer, &receivedValues[getCounter]))
    {
        getCounter++;
    }

    TEST_ASSERT_EQUAL(true, RingbufferIsEmpty(&ringbuffer));
    TEST_ASSERT_EQUAL(BUFFER_SIZE, getCounter);
    TEST_ASSERT_EQUAL_MEMORY(expectedValues, receivedValues, BUFFER_SIZE);

    free(expectedValues);
    free(receivedValues);
}




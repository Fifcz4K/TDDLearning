#include <gtest/gtest.h>

extern "C"
{
    #include "../RingbufferGeneric.h"
}

#define BUFFER_SIZE (100000)
typedef float item_t;
#define ITEM_SIZE (sizeof(item_t))

struct RingbufferGenericTests : public ::testing::Test
{
    Ringbuffer_t ringbuffer;
    virtual void SetUp() override 
    {
        RingbufferInit(&ringbuffer, BUFFER_SIZE, ITEM_SIZE);
    }

    virtual void TearDown() override 
    {
        RingbufferDeInit(&ringbuffer);
    }
};

TEST_F(RingbufferGenericTests, Initialization)
{
    ASSERT_TRUE(ringbuffer.buffer);
    ASSERT_EQ(BUFFER_SIZE, ringbuffer.bufferSize);
    ASSERT_EQ(ITEM_SIZE, ringbuffer.itemSize);
    ASSERT_EQ(ringbuffer.buffer, ringbuffer.head);
    ASSERT_EQ(ringbuffer.buffer, ringbuffer.tail);
    ASSERT_EQ((uint8_t*)ringbuffer.buffer + (BUFFER_SIZE * ITEM_SIZE), (uint8_t*)ringbuffer.bufferEnd);
    EXPECT_TRUE(RingbufferIsEmpty(&ringbuffer));
}

TEST_F(RingbufferGenericTests, GetFromEmptyBufferReturnsFalse)
{
    EXPECT_FALSE(RingbufferGetItem(&ringbuffer, NULL));
}

TEST_F(RingbufferGenericTests, NotEmptyAfterAddingItem)
{
    item_t item = 10;
    RingbufferPushItem(&ringbuffer, &item);

    EXPECT_FALSE(RingbufferIsEmpty(&ringbuffer));
}

TEST_F(RingbufferGenericTests, GetAddedItem)
{
    item_t item = 10, receivedItem = 0;
    RingbufferPushItem(&ringbuffer, &item);

    ASSERT_FALSE(RingbufferIsEmpty(&ringbuffer));

    EXPECT_TRUE(RingbufferGetItem(&ringbuffer, &receivedItem)); // Get function should return TRUE if ringbuffer wasn't empty
    EXPECT_EQ(item, receivedItem);
    EXPECT_TRUE(RingbufferIsEmpty(&ringbuffer));
}

TEST_F(RingbufferGenericTests, OverflowWithReadingAfterEachPush)
{
    item_t *receivedItems = (item_t*)malloc(BUFFER_SIZE * ITEM_SIZE); // Allocate memory for collecting data from ringbuffer
    item_t *expectedItems = (item_t*)malloc(BUFFER_SIZE * ITEM_SIZE); // Allocate memory to prepare expected values
    item_t itemToPush = 0;
    item_t lastItemToReceive = 0;

    for(size_t i = 0; i < BUFFER_SIZE; i++)
    {
        itemToPush = (item_t)i;
        RingbufferPushItem(&ringbuffer, &itemToPush); // Push BUFFER_SIZE items to ringbuffer
        ASSERT_TRUE(RingbufferGetItem(&ringbuffer, receivedItems + i)); // And read item after each push
    }

    ASSERT_EQ(ringbuffer.head, ringbuffer.buffer); // Both head and tail pointers should point to the start address of the ringbuffer
    ASSERT_EQ(ringbuffer.tail, ringbuffer.buffer);

    ASSERT_TRUE(RingbufferIsEmpty(&ringbuffer));

    for(size_t i = 0; i < BUFFER_SIZE; i++)
    {
        *(expectedItems + i) = i; // Prepare expected values: 0, 1, 2, ..., (BUFFER_SIZE - 1)
    }

    EXPECT_EQ(0, memcmp(expectedItems, receivedItems, BUFFER_SIZE * ITEM_SIZE)); // Compare read and expected values

    itemToPush = 0xAA;
    RingbufferPushItem(&ringbuffer, &itemToPush); // Push one more item to the ringbuffer, it should be the only item in the ringbuffer now

    ASSERT_FALSE(RingbufferIsEmpty(&ringbuffer));         

    EXPECT_TRUE(RingbufferGetItem(&ringbuffer, &lastItemToReceive)); // Get function should return TRUE if ringbuffer wasn't empty
    EXPECT_TRUE(RingbufferIsEmpty(&ringbuffer));
    EXPECT_EQ(itemToPush, lastItemToReceive);

    ASSERT_EQ(ringbuffer.head, (item_t*)ringbuffer.buffer + 1); // Both head and tail pointers should point to the (start address + 1) of the ringbuffer
    ASSERT_EQ(ringbuffer.tail, (item_t*)ringbuffer.buffer + 1);

    free(receivedItems); // Free allocated memory
    free(expectedItems);
}

TEST_F(RingbufferGenericTests, OverflowWithoutReadingAfterEachPush)
{
    item_t *receivedItems = (item_t*)malloc(BUFFER_SIZE * ITEM_SIZE); // Allocate memory for collecting data from ringbuffer
    item_t *expectedItems = (item_t*)malloc(BUFFER_SIZE * ITEM_SIZE); // Allocate memory to prepare expected values
    size_t readCounter = 0;
    item_t itemToPush = 0;

    for(size_t i = 0; i < BUFFER_SIZE; i++) 
    {
        itemToPush = (item_t)i;
        RingbufferPushItem(&ringbuffer, &itemToPush); // Fill ringbuffer with values from 0 to BUFFER_SIZE
    }

    ASSERT_EQ(ringbuffer.head, ringbuffer.buffer); // Both head and tail pointers should point to the start address of the ringbuffer
    ASSERT_EQ(ringbuffer.tail, ringbuffer.buffer);

    itemToPush = 0xAA;
    RingbufferPushItem(&ringbuffer, &itemToPush); // Push one more item to the full ringbuffer, ringbuffer now should contain values: item, 1, 2, 3, ..., BUFFER_SIZE

    for(size_t i = 0; i < BUFFER_SIZE - 1; i++)
    {
        *(expectedItems + i) = i + 1; // Prepare expected values: 1, 2, 3, ...
    }

    *(expectedItems + (BUFFER_SIZE - 1)) = itemToPush; // Change last item in expected values buffer to item

    ASSERT_FALSE(RingbufferIsEmpty(&ringbuffer));

    while(RingbufferGetItem(&ringbuffer, receivedItems + readCounter) != false) // Read all items from ringbuffer
    {
        readCounter++; // Count number of successful readings from ringbuffer
    }

    EXPECT_TRUE(RingbufferIsEmpty(&ringbuffer));
    EXPECT_EQ(BUFFER_SIZE, readCounter); // If ringbuffer was full, while loop should be able to read successfully from it BUFFER_SIZE times
    EXPECT_EQ(0, memcmp(expectedItems, receivedItems, BUFFER_SIZE * ITEM_SIZE)); // Compare read and expected values

    ASSERT_EQ(ringbuffer.head, (item_t*)ringbuffer.buffer + 1); // Both head and tail pointers should point to the (start address + 1) of the ringbuffer
    ASSERT_EQ(ringbuffer.tail, (item_t*)ringbuffer.buffer + 1);

    free(receivedItems); // Free allocated memory
    free(expectedItems);
}

TEST_F(RingbufferGenericTests, WriteTwiceAsMaxSizeAndRead)
{
    item_t *receivedItems = (item_t*)malloc(BUFFER_SIZE * ITEM_SIZE); // Allocate memory for collecting data from ringbuffer
    item_t *expectedItems = (item_t*)malloc(BUFFER_SIZE * ITEM_SIZE); // Allocate memory to prepare expected values
    size_t readCounter = 0;
    item_t itemToPush = 0;

    for(size_t i = 0; i < BUFFER_SIZE * 2; i++)
    {
        itemToPush = (item_t)i;
        RingbufferPushItem(&ringbuffer, &itemToPush); // Fill ringbuffer twice
        if(i >= BUFFER_SIZE)
            *(expectedItems + i - BUFFER_SIZE) = i; // Prepare expected values
    }

    ASSERT_EQ(ringbuffer.head, ringbuffer.buffer); // Both head and tail pointers should point to the start address of the ringbuffer
    ASSERT_EQ(ringbuffer.tail, ringbuffer.buffer);
    ASSERT_FALSE(RingbufferIsEmpty(&ringbuffer));

    while(RingbufferGetItem(&ringbuffer, receivedItems + readCounter) != false) // Read all items from ringbuffer
    {
        readCounter++; // Count number of successful readings from ringbuffer
    }

    EXPECT_EQ(BUFFER_SIZE, readCounter); // If ringbuffer was full, while loop should be able to read successfully from it BUFFER_SIZE times
    EXPECT_TRUE(RingbufferIsEmpty(&ringbuffer));
    EXPECT_EQ(0, memcmp(receivedItems, expectedItems, BUFFER_SIZE * ITEM_SIZE)); // Compare read and expected values

    ASSERT_EQ(ringbuffer.head, ringbuffer.buffer); // Both head and tail pointers should point to the start address of the ringbuffer
    ASSERT_EQ(ringbuffer.tail, ringbuffer.buffer);

    free(receivedItems); // Free allocated memory
    free(expectedItems);
}



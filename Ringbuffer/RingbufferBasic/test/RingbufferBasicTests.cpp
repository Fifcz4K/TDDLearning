#include <gtest/gtest.h>

extern "C"
{
    #include "../RingbufferBasic.h"
}

struct RingbufferBasicTests : public ::testing::Test
{
    Ringbuffer_t ringbuffer;
    virtual void SetUp() override 
    {
        RingbufferInit(&ringbuffer);
    }

    virtual void TearDown() override 
    {

    }
};

TEST_F(RingbufferBasicTests, Initialization)
{
    EXPECT_TRUE(RingbufferIsEmpty(&ringbuffer));
}

TEST_F(RingbufferBasicTests, NotEmptyAfterAddingItem)
{
    Item_t item = 10;
    RingbufferAddItem(&ringbuffer, item);

    EXPECT_FALSE(RingbufferIsEmpty(&ringbuffer));
}

TEST_F(RingbufferBasicTests, RecevingFromEmptyBufferReturnsFalse)
{
    Item_t itemReceived;
    bool receiveResult = RingbufferReceiveItem(&ringbuffer, &itemReceived);

    EXPECT_FALSE(receiveResult);
}

TEST_F(RingbufferBasicTests, ReceivingTheOnlyElementMakesRingBufferEmptyAgainAndReceivesTheElement)
{
    Item_t item = 10;
    RingbufferAddItem(&ringbuffer, item);

    Item_t itemReceived = 0;
    bool receiveResult = RingbufferReceiveItem(&ringbuffer, &itemReceived);

    EXPECT_TRUE(RingbufferIsEmpty(&ringbuffer));
    EXPECT_TRUE(receiveResult);
    EXPECT_EQ(item, itemReceived);
}

TEST_F(RingbufferBasicTests, OverflowWithReading)
{
    Item_t itemReceived;

    for(size_t i = 0; i < RINGBUFFER_SIZE; i++)
    {
        RingbufferAddItem(&ringbuffer, i);
        RingbufferReceiveItem(&ringbuffer, &itemReceived);
    }

    Item_t item = 0xAA;
    RingbufferAddItem(&ringbuffer, item);   

    ASSERT_FALSE(RingbufferIsEmpty(&ringbuffer));         

    bool receiveResult = RingbufferReceiveItem(&ringbuffer, &itemReceived);

    EXPECT_TRUE(RingbufferIsEmpty(&ringbuffer));
    EXPECT_TRUE(receiveResult);
    EXPECT_EQ(item, itemReceived);
}

TEST_F(RingbufferBasicTests, OverflowWithoutReading)
{
    Item_t itemReceived;

    for(size_t i = 0; i < RINGBUFFER_SIZE; i++)
    {
        RingbufferAddItem(&ringbuffer, i);
    }

    Item_t item = 0xAA;
    RingbufferAddItem(&ringbuffer, item);   

    ASSERT_FALSE(RingbufferIsEmpty(&ringbuffer));         

    bool receiveResult = RingbufferReceiveItem(&ringbuffer, &itemReceived);

    EXPECT_FALSE(RingbufferIsEmpty(&ringbuffer));
    EXPECT_TRUE(receiveResult);
    EXPECT_EQ(1, itemReceived);
}

TEST_F(RingbufferBasicTests, WriteTwiceAsMaxSizeAndRead)
{
    Item_t items[RINGBUFFER_SIZE * 2];
    for(size_t i = 0; i < RINGBUFFER_SIZE * 2; i++)
    {
        items[i] = i;
        RingbufferAddItem(&ringbuffer, i);
    }

    Item_t receivedItems[RINGBUFFER_SIZE];
    size_t timesRead = 0;
    while(RingbufferReceiveItem(&ringbuffer, &receivedItems[timesRead]) != false)
    {
        timesRead++;
    }

    EXPECT_EQ(RINGBUFFER_SIZE, timesRead);
    EXPECT_EQ(0, memcmp(&items[RINGBUFFER_SIZE], receivedItems, RINGBUFFER_SIZE * sizeof(Item_t)));
}






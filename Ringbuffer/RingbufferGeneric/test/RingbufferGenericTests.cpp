#include <gtest/gtest.h>

extern "C"
{
    #include "../RingbufferGeneric.h"
}

struct RingbufferGenericTests : public ::testing::Test
{
    virtual void SetUp() override 
    {
        
    }

    virtual void TearDown() override 
    {

    }
};

TEST_F(RingbufferGenericTests, Initialization)
{
    EXPECT_TRUE(false);
}





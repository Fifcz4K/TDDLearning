#include "unity.h"

#include "Doors100.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Doors(void)
{
    TEST_ASSERT_EQUAL_STRING("Incorrect number of doors!", GetDoorsState(0));
    TEST_ASSERT_EQUAL_STRING("Incorrect number of doors!", GetDoorsState(101));

    TEST_ASSERT_EQUAL_STRING("@##", GetDoorsState(3));

    TEST_ASSERT_EQUAL_STRING("@##@##", GetDoorsState(6));

    TEST_ASSERT_EQUAL_STRING("@##@####", GetDoorsState(8));

    TEST_ASSERT_EQUAL_STRING("@##@####@######@########@##########@############@##############@################@##################@", GetDoorsState(100));

    TEST_ASSERT_EQUAL_STRING("@", GetDoorsState(1));
}


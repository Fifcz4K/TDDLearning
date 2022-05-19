#include "unity.h"

#include "RomanNumerals.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_one_character_numbers(void)
{
    TEST_ASSERT_EQUAL_STRING("I", Convert(1));
    TEST_ASSERT_EQUAL_STRING("V", Convert(5));
    TEST_ASSERT_EQUAL_STRING("X", Convert(10));
    TEST_ASSERT_EQUAL_STRING("L", Convert(50));
    TEST_ASSERT_EQUAL_STRING("C", Convert(100));
    TEST_ASSERT_EQUAL_STRING("D", Convert(500));
    TEST_ASSERT_EQUAL_STRING("M", Convert(1000));
}

void test_first_10_numbers(void)
{
    TEST_ASSERT_EQUAL_STRING("I", Convert(1));
    TEST_ASSERT_EQUAL_STRING("II", Convert(2));
    TEST_ASSERT_EQUAL_STRING("III", Convert(3));
    TEST_ASSERT_EQUAL_STRING("IV", Convert(4));
    TEST_ASSERT_EQUAL_STRING("V", Convert(5));
    TEST_ASSERT_EQUAL_STRING("VI", Convert(6));
    TEST_ASSERT_EQUAL_STRING("VII", Convert(7));
    TEST_ASSERT_EQUAL_STRING("VIII", Convert(8));
    TEST_ASSERT_EQUAL_STRING("IX", Convert(9));
    TEST_ASSERT_EQUAL_STRING("X", Convert(10));
}

void test_random_numbers(void)
{
    TEST_ASSERT_EQUAL_STRING("CLXXXIV", Convert(184));
    TEST_ASSERT_EQUAL_STRING("CCCXXXVIII", Convert(338));
    TEST_ASSERT_EQUAL_STRING("DCCII", Convert(702));
    TEST_ASSERT_EQUAL_STRING("MCDXXIX", Convert(1429));
    TEST_ASSERT_EQUAL_STRING("MCDXCIX", Convert(1499));
    TEST_ASSERT_EQUAL_STRING("MMXL", Convert(2040));
    TEST_ASSERT_EQUAL_STRING("MMDCCCLXXXVIII", Convert(2888));
}
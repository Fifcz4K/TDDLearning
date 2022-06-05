#include "unity.h"

#include "RomanNumerals.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_arabic_to_roman(void)
{
    TEST_ASSERT_EQUAL_STRING("I", ConvertArabicToRoman(1));
    TEST_ASSERT_EQUAL_STRING("II", ConvertArabicToRoman(2));
    TEST_ASSERT_EQUAL_STRING("III", ConvertArabicToRoman(3));
    TEST_ASSERT_EQUAL_STRING("IV", ConvertArabicToRoman(4));
    TEST_ASSERT_EQUAL_STRING("V", ConvertArabicToRoman(5));
    TEST_ASSERT_EQUAL_STRING("VI", ConvertArabicToRoman(6));
    TEST_ASSERT_EQUAL_STRING("VII", ConvertArabicToRoman(7));
    TEST_ASSERT_EQUAL_STRING("VIII", ConvertArabicToRoman(8));
    TEST_ASSERT_EQUAL_STRING("IX", ConvertArabicToRoman(9));
    TEST_ASSERT_EQUAL_STRING("X", ConvertArabicToRoman(10));
    TEST_ASSERT_EQUAL_STRING("L", ConvertArabicToRoman(50));
    TEST_ASSERT_EQUAL_STRING("C", ConvertArabicToRoman(100));
    TEST_ASSERT_EQUAL_STRING("D", ConvertArabicToRoman(500));
    TEST_ASSERT_EQUAL_STRING("M", ConvertArabicToRoman(1000));

    TEST_ASSERT_EQUAL_STRING("CLXXXIV", ConvertArabicToRoman(184));
    TEST_ASSERT_EQUAL_STRING("CCCXXXVIII", ConvertArabicToRoman(338));
    TEST_ASSERT_EQUAL_STRING("DCCII", ConvertArabicToRoman(702));
    TEST_ASSERT_EQUAL_STRING("MCDXXIX", ConvertArabicToRoman(1429));
    TEST_ASSERT_EQUAL_STRING("MCDXCIX", ConvertArabicToRoman(1499));
    TEST_ASSERT_EQUAL_STRING("MMXL", ConvertArabicToRoman(2040));
    TEST_ASSERT_EQUAL_STRING("MMDCCCLXXXVIII", ConvertArabicToRoman(2888));
}


void test_roman_to_arabic(void)
{
    TEST_ASSERT_EQUAL(1, ConvertRomanToArabic("I"));
    TEST_ASSERT_EQUAL(2, ConvertRomanToArabic("II"));
    TEST_ASSERT_EQUAL(3, ConvertRomanToArabic("III"));
    TEST_ASSERT_EQUAL(4, ConvertRomanToArabic("IV"));
    TEST_ASSERT_EQUAL(5, ConvertRomanToArabic("V"));
    TEST_ASSERT_EQUAL(6, ConvertRomanToArabic("VI"));
    TEST_ASSERT_EQUAL(7, ConvertRomanToArabic("VII"));
    TEST_ASSERT_EQUAL(8, ConvertRomanToArabic("VIII"));
    TEST_ASSERT_EQUAL(9, ConvertRomanToArabic("IX"));
    TEST_ASSERT_EQUAL(10, ConvertRomanToArabic("X"));
    TEST_ASSERT_EQUAL(50, ConvertRomanToArabic("L"));
    TEST_ASSERT_EQUAL(100, ConvertRomanToArabic("C"));
    TEST_ASSERT_EQUAL(500, ConvertRomanToArabic("D"));
    TEST_ASSERT_EQUAL(1000, ConvertRomanToArabic("M"));

    TEST_ASSERT_EQUAL(184, ConvertRomanToArabic("CLXXXIV"));
    TEST_ASSERT_EQUAL(338, ConvertRomanToArabic("CCCXXXVIII"));
    TEST_ASSERT_EQUAL(702, ConvertRomanToArabic("DCCII"));
    TEST_ASSERT_EQUAL(1429, ConvertRomanToArabic("MCDXXIX"));
    TEST_ASSERT_EQUAL(1499, ConvertRomanToArabic("MCDXCIX"));
    TEST_ASSERT_EQUAL(2040, ConvertRomanToArabic("MMXL"));
    TEST_ASSERT_EQUAL(2888, ConvertRomanToArabic("MMDCCCLXXXVIII"));
}
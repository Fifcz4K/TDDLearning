#include "unity.h"

#include "NumbersToWords.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_NumbersToWords(void)
{
    TEST_ASSERT_EQUAL_STRING("Zero", ConvertNumberToWord(0));
    TEST_ASSERT_EQUAL_STRING("One", ConvertNumberToWord(1));
    TEST_ASSERT_EQUAL_STRING("Two", ConvertNumberToWord(2));
    TEST_ASSERT_EQUAL_STRING("Three", ConvertNumberToWord(3));
    TEST_ASSERT_EQUAL_STRING("Four", ConvertNumberToWord(4));
    TEST_ASSERT_EQUAL_STRING("Five", ConvertNumberToWord(5));
    TEST_ASSERT_EQUAL_STRING("Six", ConvertNumberToWord(6));
    TEST_ASSERT_EQUAL_STRING("Seven", ConvertNumberToWord(7));
    TEST_ASSERT_EQUAL_STRING("Eight", ConvertNumberToWord(8));
    TEST_ASSERT_EQUAL_STRING("Nine", ConvertNumberToWord(9));
    TEST_ASSERT_EQUAL_STRING("Ten", ConvertNumberToWord(10));

    TEST_ASSERT_EQUAL_STRING("Eleven", ConvertNumberToWord(11));
    TEST_ASSERT_EQUAL_STRING("Twelve", ConvertNumberToWord(12));
    TEST_ASSERT_EQUAL_STRING("Thirteen", ConvertNumberToWord(13));
    TEST_ASSERT_EQUAL_STRING("Fourteen", ConvertNumberToWord(14));
    TEST_ASSERT_EQUAL_STRING("Fiveteen", ConvertNumberToWord(15));
    TEST_ASSERT_EQUAL_STRING("Sixteen", ConvertNumberToWord(16));
    TEST_ASSERT_EQUAL_STRING("Seventeen", ConvertNumberToWord(17));
    TEST_ASSERT_EQUAL_STRING("Eighteen", ConvertNumberToWord(18));
    TEST_ASSERT_EQUAL_STRING("Nineteen", ConvertNumberToWord(19));
    TEST_ASSERT_EQUAL_STRING("Twenty", ConvertNumberToWord(20));

    TEST_ASSERT_EQUAL_STRING("Twenty Five", ConvertNumberToWord(25));
    TEST_ASSERT_EQUAL_STRING("Twenty Eight", ConvertNumberToWord(28));
    TEST_ASSERT_EQUAL_STRING("Thirty Three", ConvertNumberToWord(33));
    TEST_ASSERT_EQUAL_STRING("Thirty Seven", ConvertNumberToWord(37));
    TEST_ASSERT_EQUAL_STRING("Forty Two", ConvertNumberToWord(42));
    TEST_ASSERT_EQUAL_STRING("Fifty Five", ConvertNumberToWord(55));
    TEST_ASSERT_EQUAL_STRING("Sixty One", ConvertNumberToWord(61));
    TEST_ASSERT_EQUAL_STRING("Seventy Nine", ConvertNumberToWord(79));
    TEST_ASSERT_EQUAL_STRING("Eighty Eight", ConvertNumberToWord(88));
    TEST_ASSERT_EQUAL_STRING("Ninety", ConvertNumberToWord(90));
    
    TEST_ASSERT_EQUAL_STRING("One Hundred", ConvertNumberToWord(100));
    TEST_ASSERT_EQUAL_STRING("Two Hundred", ConvertNumberToWord(200));
    TEST_ASSERT_EQUAL_STRING("Six Hundred", ConvertNumberToWord(600));
    TEST_ASSERT_EQUAL_STRING("Nine Hundred", ConvertNumberToWord(900));

    TEST_ASSERT_EQUAL_STRING("Two Hundred And Thirty", ConvertNumberToWord(230));
    TEST_ASSERT_EQUAL_STRING("Three Hundred Sixty One", ConvertNumberToWord(361));
    TEST_ASSERT_EQUAL_STRING("Five Hundred Fifty Five", ConvertNumberToWord(555));
    TEST_ASSERT_EQUAL_STRING("Four Hundred", ConvertNumberToWord(400));
    TEST_ASSERT_EQUAL_STRING("Eight Hundred And Ten", ConvertNumberToWord(810));
    TEST_ASSERT_EQUAL_STRING("Nine Hundred Ninety Nine", ConvertNumberToWord(999));

    TEST_ASSERT_EQUAL_STRING("One Thousand", ConvertNumberToWord(1000));
    TEST_ASSERT_EQUAL_STRING("Three Thousand", ConvertNumberToWord(3000));
    TEST_ASSERT_EQUAL_STRING("Nine Thousand", ConvertNumberToWord(9000));

    TEST_ASSERT_EQUAL_STRING("Two Thousand One Hundred Eleven", ConvertNumberToWord(2111));
    TEST_ASSERT_EQUAL_STRING("Three Thousand Two Hundred Ninety One", ConvertNumberToWord(3291));
    TEST_ASSERT_EQUAL_STRING("Five Thousand Six Hundred Eighty Eight", ConvertNumberToWord(5688));
    TEST_ASSERT_EQUAL_STRING("Seven Thousand Four Hundred And Twenty", ConvertNumberToWord(7420));
    TEST_ASSERT_EQUAL_STRING("Nine Thousand Nine Hundred Ninety Nine", ConvertNumberToWord(9999));

    TEST_ASSERT_EQUAL_STRING("Put in number from 0 to 9999!", ConvertNumberToWord(10000));
}

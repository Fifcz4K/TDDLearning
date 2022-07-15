#include <gtest/gtest.h>
#include <stdlib.h>
#include "m_led_mock.h"
#include "m_adc_mock.h"

using ::testing::Return;

extern "C"
{
    #include "../LowBatteryAlarm.h"
}

struct LowBatteryAlarmTests : public ::testing::Test
{
    LedMock ledMock{};
    AdcMock adcMock{};
    virtual void SetUp() override 
    {
        ledMockInit(&ledMock);
        adcMockInit(&adcMock);
        vbatInit();
    }

    virtual void TearDown() override 
    {
    }
};

TEST_F(LowBatteryAlarmTests, LedOffAfterInit)
{
    EXPECT_CALL(ledMock, LedOff());
    vbatInit();
}

TEST_F(LowBatteryAlarmTests, LedOnAfter5LowMeasures)
{
    ON_CALL(adcMock, getAdcValue()).WillByDefault(Return(LOW_BATTERY_ADC_VALUE - 1));
    EXPECT_CALL(ledMock, LedOff()).Times(0);
    EXPECT_CALL(ledMock, LedOn());

    for(uint8_t i = 0; i < ALARM_AFTER_N_LOW_MEASURES; i++)
    {
        vbatCheck();
    }
}

TEST_F(LowBatteryAlarmTests, NoLedActionWhen4TooLowThenCorrectThen4TooLowAgain)
{
    EXPECT_CALL(adcMock, getAdcValue())
    .Times(9)
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1));
    EXPECT_CALL(ledMock, LedOff()).Times(0);
    EXPECT_CALL(ledMock, LedOn()).Times(0);

    for(uint8_t i = 0; i < 9; i++)
    {
        vbatCheck();
    }
}

TEST_F(LowBatteryAlarmTests, LedOnWhen4TooLowThenCorrectThen5TooLow)
{
    EXPECT_CALL(adcMock, getAdcValue())
    .Times(10)
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1))
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE - 1));
    EXPECT_CALL(ledMock, LedOff()).Times(0);
    EXPECT_CALL(ledMock, LedOn());

    for(uint8_t i = 0; i < 10; i++)
    {
        vbatCheck();
    }
}
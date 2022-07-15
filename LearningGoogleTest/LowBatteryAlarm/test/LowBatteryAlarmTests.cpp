#include <gtest/gtest.h>
#include <stdlib.h>
#include "m_led_mock.h"
#include "m_adc_mock.h"

using ::testing::Return;
using ::testing::InSequence;

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
    InSequence s;
    EXPECT_CALL(adcMock, getAdcValue())
    .Times(4)
    .WillRepeatedly(Return(LOW_BATTERY_ADC_VALUE - 1));
    EXPECT_CALL(adcMock, getAdcValue())
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE));
    EXPECT_CALL(adcMock, getAdcValue())
    .Times(4)
    .WillRepeatedly(Return(LOW_BATTERY_ADC_VALUE - 1));
    EXPECT_CALL(ledMock, LedOff()).Times(0);
    EXPECT_CALL(ledMock, LedOn()).Times(0);

    for(uint8_t i = 0; i < 9; i++)
    {
        vbatCheck();
    }
}

TEST_F(LowBatteryAlarmTests, LedOnWhen4TooLowThenCorrectThen5TooLow)
{
    InSequence s;
    EXPECT_CALL(adcMock, getAdcValue())
    .Times(4)
    .WillRepeatedly(Return(LOW_BATTERY_ADC_VALUE - 1));
    EXPECT_CALL(adcMock, getAdcValue())
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE));
    EXPECT_CALL(adcMock, getAdcValue())
    .Times(5)
    .WillRepeatedly(Return(LOW_BATTERY_ADC_VALUE - 1));
    EXPECT_CALL(ledMock, LedOff()).Times(0);
    EXPECT_CALL(ledMock, LedOn());

    for(uint8_t i = 0; i < 10; i++)
    {
        vbatCheck();
    }
}

TEST_F(LowBatteryAlarmTests, LedStillOnWhenCorrectMeasureAfterAlarm)
{
    InSequence s;
    EXPECT_CALL(adcMock, getAdcValue())
    .Times(5)
    .WillRepeatedly(Return(LOW_BATTERY_ADC_VALUE - 1));
    EXPECT_CALL(ledMock, LedOn());
    EXPECT_CALL(adcMock, getAdcValue())
    .WillOnce(Return(LOW_BATTERY_ADC_VALUE));
    EXPECT_CALL(ledMock, LedOff()).Times(0);

    for(uint8_t i = 0; i < 6; i++)
    {
        vbatCheck();
    }
}
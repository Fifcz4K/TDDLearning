#include "LowBatteryAlarm.h"

static uint8_t lowBatteryCnt = 0;

void vbatInit(void)
{
    lowBatteryCnt = 0;
    LedOff();
}

void vbatCheck(void)
{
    adc_value_t adcValue = getAdcValue();

    if(adcValue < LOW_BATTERY_ADC_VALUE)
    {
        lowBatteryCnt++;
        if(lowBatteryCnt == ALARM_AFTER_N_LOW_MEASURES)
        {
            LedOn();
        }
    }
    else
    {
        lowBatteryCnt = 0;
    }
}
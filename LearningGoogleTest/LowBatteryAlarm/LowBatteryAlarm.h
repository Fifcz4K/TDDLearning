#ifndef LOWBATTERYALARM_H
#define LOWBATTERYALARM_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "m_led.h"
#include "m_adc.h"

#define LOW_BATTERY_ADC_VALUE 2850
#define ALARM_AFTER_N_LOW_MEASURES 5

void vbatInit(void);
void vbatCheck(void);


#endif /* LOWBATTERYALARM_H */
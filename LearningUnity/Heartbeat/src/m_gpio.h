#ifndef M_GPIO_H
#define M_GPIO_H

typedef enum
{
    GPIO_LOW,
    GPIO_HIGH
}GPIO_State_t;

GPIO_State_t heartbeat_pin_get(void);

#endif //M_GPIO_H
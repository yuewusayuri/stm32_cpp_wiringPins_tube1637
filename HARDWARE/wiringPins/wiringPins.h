#ifndef WIRINGPINS_H
#define WIRINGPINS_H

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif
    
typedef enum
{
    PA0 ,
    PA1 ,
    PA2 ,
    PA3 ,
    PA4 ,
    PA5 ,
    PA6 ,
    PA7 ,
    PA8 ,
    PA9 ,
    PA10,
    PA11,
    PA12,
    PA13,
    PA14,
    PA15,
    PB0 ,
    PB1 ,
    PB2 ,
    PB3 ,
    PB4 ,
    PB5 ,
    PB6 ,
    PB7 ,
    PB8 ,
    PB9 ,
    PB10,
    PB11,
    PB12,
    PB13,
    PB14,
    PB15,
    PC0 ,
    PC1 ,
    PC2 ,
    PC3 ,
    PC4 ,
    PC5 ,
    PC6 ,
    PC7 ,
    PC8 ,
    PC9 ,
    PC10,
    PC11,
    PC12,
    PC13,
    PC14,
    PC15,
    PD0 ,
    PD1 ,
    PD2 ,
    PD3 ,
    PD4 ,
    PD5 ,
    PD6 ,
    PD7 ,
    PD8 ,
    PD9 ,
    PD10,
    PD11,
    PD12,
    PD13,
    PD14,
    PD15,
    PE0 ,
    PE1 ,
    PE2 ,
    PE3 ,
    PE4 ,
    PE5 ,
    PE6 ,
    PE7 ,
    PE8 ,
    PE9 ,
    PE10,
    PE11,
    PE12,
    PE13,
    PE14,
    PE15,
} digitalPins_Type;

typedef enum {
    LOW,
    HIGH,
} digitalLevel_Type;

#define GET_GPIO_PORT(pins) ( \
    ((pins) / 16 == 0) ? (GPIOA) : \
    ((pins) / 16 == 1) ? (GPIOB) : \
    ((pins) / 16 == 2) ? (GPIOC) : \
    ((pins) / 16 == 3) ? (GPIOD) : \
    ((pins) / 16 == 4) ? (GPIOE) : NULL \
)

#define GET_GPIO_PIN(pins)   ((uint16_t)1 << ((pins) % 16))

#define FIND_GPIO(pins, pin, port) do { \
    (pin) = GET_GPIO_PIN(pins); \
    (port) = GET_GPIO_PORT(pins); \
} while(0)

void pinMode(digitalPins_Type pins, uint32_t Mode);
void digitalWrite(digitalPins_Type pins, digitalLevel_Type pinsLevel);
void digitalToggle(digitalPins_Type pins);
uint8_t digitalRead(digitalPins_Type pins);

#ifdef __cplusplus
}
#endif

#endif

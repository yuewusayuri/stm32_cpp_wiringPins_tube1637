#ifndef __LED_H
#define __LED_H

#include "main.h"
#include "wiringPins.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
#define LED_ON		LOW
#define LED_OFF 	HIGH
#define LED_PIN     PC13
    
void led_init(void);
void led_set(digitalLevel_Type lv);
void led_flip(digitalPins_Type pins);

#ifdef __cplusplus
}
#endif
#endif


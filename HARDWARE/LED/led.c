#include "led.h"

void led_init(void)
{
    pinMode(PC13, GPIO_MODE_OUTPUT_PP);
    led_set(LED_OFF);
	
}

void led_set(digitalLevel_Type lv)
{
    digitalWrite(LED_PIN, lv);
}

void led_flip(digitalPins_Type pins)
{
    digitalToggle(pins);
}

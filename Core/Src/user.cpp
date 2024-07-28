#include "user.h"
#include "OLED.h"
#include "my_usart.h"
#include "led.h"
#include "tm1637.h"
#include "wiringPins.h"

TM1637 tube;

void hardware_init(void)
{
//    OLED_Init();
    
    /* led */
    led_init();
    led_set(LED_OFF);
    /* tm1637 */
    tube.init(PA5, PA6); /* SCL, SDA 可以随意更改位置 */
    tube.clear();
}

void user_loop(void)
{
    static int i = 0;
    i %= 8;

    tube.digiTubeDisp(0, i);
    tube.setBrightness(i++);

    led_flip(LED_PIN);

    HAL_Delay(500);
}


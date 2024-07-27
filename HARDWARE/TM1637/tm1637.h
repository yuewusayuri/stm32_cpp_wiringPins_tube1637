#ifndef __TM1637_H
#define __TM1637_H

#include "main.h"
#include "wiringPins.h"

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char Digital_tube_code_table[];
    
#define ADDRESS_PLUS     0x40        // 地址自加模式    
#define ADDRESS_FIXED    0x44        // 固定地址模式
#define DISPLAY_OFF      0x80
#define DISPLAY_ON       0x88

#define WIRING_SWI2C_INIT(SCL, SDA) do { \
     pinMode(SCL, GPIO_MODE_OUTPUT_OD); \
     pinMode(SDA, GPIO_MODE_OUTPUT_OD); \
    digitalWrite(SCL, HIGH); \
    digitalWrite(SDA, HIGH); \
} while(0)
    
class TM1637 {
public:
    TM1637();

    void init(digitalPins_Type TM1637_SCL_Pin, digitalPins_Type TM1637_SDA_Pin);
    void displayInc();
    void digiTubeDisp(uint8_t address, uint8_t value);
    void setBrightness(unsigned char level);
    void turnOff();
    void clear();

private:
    digitalPins_Type SCL;
    digitalPins_Type SDA;

    void iic_start();
    void iic_stop();
    void iic_send_byte(uint8_t byte);
    uint8_t iic_receive_ack();
    void iic_send_ack(uint8_t AckBit);

    void iic_w_sda(digitalLevel_Type lv);
    void iic_w_scl(digitalLevel_Type lv);
    uint8_t iic_r_sda(void);
};

#ifdef __cplusplus
}
#endif

#endif // __TM1637_H

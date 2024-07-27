/**
* @file         tm1637.cpp
* @brief        tm1637 Four digit digital tube driver
* @details      iic protocol，*LSB First*
* @author       yuewusayuri
* @date         2024.7.28
* @version      v3.0
*/
#include "tm1637.h"


unsigned char Digital_tube_code_table[] = {
    0x3F,  //"0"
    0x06,  //"1"
    0x5B,  //"2"
    0x4F,  //"3"
    0x66,  //"4"
    0x6D,  //"5"
    0x7D,  //"6"
    0x07,  //"7"
    0x7F,  //"8"
    0x6F,  //"9"
    0x77,  //"A"
    0x7C,  //"B"
    0x39,  //"C"
    0x5E,  //"D"
    0x79,  //"E"
    0x71,  //"F"
    0x76,  //"H"
    0x38,  //"L"
    0x37,  //"n"
    0x3E,  //"u"
    0x73,  //"P"
    0x5C,  //"o"
    0x40,  //"-"
    0x00  //close
};

/**
 * @brief Constructor for the TM1637 class.
 *
 * Initializes the TM1637 object. The initialization for the I2C pins is not done here;
 * it is done in the `init` method.
 */
TM1637::TM1637()
{
    // Constructor
//    WIRING_SWI2C_INIT(PB10, PB11);
}

/**
 * @brief Initializes the TM1637 driver with specified I2C pins.
 *
 * This method sets the I2C pins for the TM1637 display and configures them
 * as output open-drain. The SCL and SDA pins are initialized for communication.
 *
 * @param TM1637_SCL_Pin Pin number for the I2C clock line (SCL).
 * @param TM1637_SDA_Pin Pin number for the I2C data line (SDA).
 */
void TM1637::init(digitalPins_Type TM1637_SCL_Pin, digitalPins_Type TM1637_SDA_Pin)
{
    WIRING_SWI2C_INIT(TM1637_SCL_Pin, TM1637_SDA_Pin);
    SCL = TM1637_SCL_Pin;
    SDA = TM1637_SDA_Pin;
}

/**
 * @brief Displays an incremental sequence on the TM1637 display.
 *
 * This method sends data to the TM1637 display to incrementally show characters.
 * It starts by sending the address increment command, followed by the data to be displayed.
 */
void TM1637::displayInc()
{
    iic_start();
    iic_send_byte(ADDRESS_PLUS);                     // 发送自增地址命令
    iic_receive_ack();
    iic_stop();

    iic_start();
    iic_send_byte(0xC0);                            // 设置起始地址为0xC0
    iic_receive_ack();
    for(uint8_t i = 0; i < 6; i++) {
        iic_send_byte(Digital_tube_code_table[i]);  // 发送数字管编码表中的数据
        iic_receive_ack();
    }
    iic_stop();
}

/**
 * @brief Displays a specific value on a specific address of the TM1637 display.
 *
 * This method sets the display address and sends the value to be shown at that address.
 *
 * @param address The address on the display where the value should be shown.
 * @param value   The value to be displayed at the specified address.
 */
void TM1637::digiTubeDisp(uint8_t address, uint8_t value)
{
    iic_start();
    iic_send_byte(ADDRESS_FIXED);                   // 发送固定地址命令
    iic_receive_ack();
    iic_stop();

    iic_start();
    iic_send_byte(0xC0 | address);                  // 发送显示地址命令
    iic_receive_ack();

    iic_send_byte(Digital_tube_code_table[value]); // 发送显示的数值编码
    iic_receive_ack();
    iic_stop();
}

/**
 * @brief Sets the brightness level of the TM1637 display.
 *
 * This method sends a command to set the brightness level of the display.
 *
 * @param level The brightness level to set (0-7).
 */
void TM1637::setBrightness(unsigned char level)
{
    iic_start();
    iic_send_byte(DISPLAY_ON | level);   // 发送显示打开命令和亮度等级
    iic_receive_ack();
    iic_stop();
}

/**
 * @brief Turns off the TM1637 display.
 *
 * This method sends a command to turn off the display.
 */
void TM1637::turnOff()
{
    iic_start();
    iic_send_byte(DISPLAY_OFF);         // 发送显示关闭命令
    iic_receive_ack();
    iic_stop();
}

/**
 * @brief Clears the TM1637 display.
 *
 * This method sends commands to clear the display by writing zero to all display positions.
 */
void TM1637::clear()
{
    iic_start();
    iic_send_byte(ADDRESS_PLUS);        // 发送自增地址命令
    iic_receive_ack();
    iic_stop();

    iic_start();
    iic_send_byte(0xC0);                // 设置起始地址为0xC0
    iic_receive_ack();
    for(uint8_t i = 0; i < 6; i++) {
        iic_send_byte(0x00);            // 发送0x00表示清除显示
        iic_receive_ack();
    }
    iic_stop();
}

/************* private **************/
void TM1637::iic_start()
{
    iic_w_sda(HIGH);
    iic_w_scl(HIGH);
    iic_w_sda(LOW);
    iic_w_scl(LOW);
}

void TM1637::iic_stop()
{
    iic_w_sda(LOW);
    iic_w_scl(HIGH);
    iic_w_sda(HIGH);
}

void TM1637::iic_send_byte(uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++) {   //先放最低位，左移i位
        iic_w_sda((byte & (0x01 << i)) ? HIGH : LOW); //每放一位施行释放SCL拉低SCL
        iic_w_scl(HIGH);                   //SCL以低位结束，方便拼接
        iic_w_scl(LOW);
    }
}

uint8_t TM1637::iic_receive_ack()       //主机释放SDA，从机把应答位放到SDA上
{
    uint8_t ack = iic_r_sda();          //SCL高电平，主机读取应答位
    iic_w_scl(HIGH);                       //主机读取应答位 ，读到0代表从机给予应答
    iic_w_scl(LOW);                       //SCL低电平进入下一个时序单元
    return ack;
}

void TM1637::iic_send_ack(uint8_t AckBit)
{
    iic_w_sda(AckBit ?  HIGH : LOW);
    iic_w_scl(HIGH);						//SCL高电平从机读取
    iic_w_scl(LOW);						//SCL以低位结束，方便拼接
}

static inline void iic_delay_us(uint32_t udelay)
{
    __IO uint32_t Delay = udelay * 72 / 8;
    do {
        __NOP();
    } while (Delay --);
}

void TM1637::iic_w_sda(digitalLevel_Type lv)
{
    digitalWrite(SDA, lv);
    iic_delay_us(10);
}

void TM1637::iic_w_scl(digitalLevel_Type lv)
{
    digitalWrite(SCL, lv);
    iic_delay_us(10);
}

uint8_t TM1637::iic_r_sda(void)
{
    return digitalRead(SDA);
}

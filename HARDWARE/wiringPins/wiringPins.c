/**
* @file         wiringPins.c
* @brief        Arduino-like STM32 HAL library gpio initialization function
* @author       yuewusayuri
* @date         2024.7.28
* @version      v1.0
*/
#include "wiringPins.h"

void pinMode(digitalPins_Type pins, uint32_t Mode)
{
    switch (pins / 16)
    {
        case 0: __HAL_RCC_GPIOA_CLK_ENABLE(); break;
        case 1: __HAL_RCC_GPIOB_CLK_ENABLE(); break;
        case 2: __HAL_RCC_GPIOC_CLK_ENABLE(); break;
        case 3: __HAL_RCC_GPIOD_CLK_ENABLE(); break;
        case 4: __HAL_RCC_GPIOE_CLK_ENABLE(); break;
    }

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    GPIO_TypeDef* IO_GPIOx;
    uint16_t IO_Pin;
    FIND_GPIO(pins, IO_Pin, IO_GPIOx);

    GPIO_InitStruct.Pin = IO_Pin;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Mode = Mode;
    HAL_GPIO_Init(IO_GPIOx, &GPIO_InitStruct);
}

void digitalWrite(digitalPins_Type pins, digitalLevel_Type pinsLevel)
{
    GPIO_TypeDef* IO_GPIOx;
    uint16_t IO_Pin;
    FIND_GPIO(pins, IO_Pin, IO_GPIOx);
    HAL_GPIO_WritePin(IO_GPIOx, IO_Pin, (GPIO_PinState)pinsLevel);
}

void digitalToggle(digitalPins_Type pins)
{
    GPIO_TypeDef* IO_GPIOx;
    uint16_t IO_Pin;
    FIND_GPIO(pins, IO_Pin, IO_GPIOx);
    HAL_GPIO_TogglePin(IO_GPIOx, IO_Pin);
}

uint8_t digitalRead(digitalPins_Type pins)
{
    GPIO_TypeDef* IO_GPIOx;
    uint16_t IO_Pin;
    FIND_GPIO(pins, IO_Pin, IO_GPIOx);
    return HAL_GPIO_ReadPin(IO_GPIOx, IO_Pin);
}

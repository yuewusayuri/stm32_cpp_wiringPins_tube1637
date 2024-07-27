#ifndef __MY_USART_H
#define __MY_USART_H

#include "usart.h"

#define  USART1_BUFFER_SIZE  (255)

#ifdef __cplusplus
extern "C"
{
#endif
void start_usart_rx(void);
void UsartPrintf(UART_HandleTypeDef USARTx, char *fmt,...);

#ifdef __cplusplus
}
#endif
#endif

#ifndef __MY_USART_H
#define __MY_USART_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "usart.h"

#define  USART1_BUFFER_SIZE  (255)


void start_usart_rx(void);
void UsartPrintf(UART_HandleTypeDef USARTx, char *fmt,...);

#ifdef __cplusplus
}
#endif

#endif

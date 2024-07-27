#include <my_usart.h>
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


uint8_t g_usart1_rx_buf[USART1_BUFFER_SIZE];
uint8_t g_idle_rx_cplt =0;
uint8_t g_usart1_rx_cplt =0;

extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart1_rx;


/* 启动接收 */
void start_usart_rx(void)
{
		/* use dma+idle to rx */
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, g_usart1_rx_buf, USART1_BUFFER_SIZE);
		__HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);/* 关闭串口接收过半中断 */	
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
		if(huart == &huart1)
		{
			uint8_t data_length  = USART1_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
			g_idle_rx_cplt = 1;	
			/* tx-dma-usart1 */
			HAL_UART_Transmit_DMA(&huart1,g_usart1_rx_buf, data_length);
		}
}

/* 接收回调函数 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		g_usart1_rx_cplt = 1;
		uint8_t data_length  = USART1_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
		HAL_UART_Transmit_DMA(&huart1, g_usart1_rx_buf, data_length);/* 这个代码不需要清理缓冲区 */
		
	}
}
void UsartPrintf(UART_HandleTypeDef USARTx, char *fmt,...)
{
 
	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							
	va_end(ap);
	
	while(*pStr != NULL)
	{
      HAL_UART_Transmit(&USARTx ,(uint8_t *)pStr++,1,HAL_MAX_DELAY );		
	}
 
}

/* 重定向prinf */
int std::fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}
static int g_last_char;
static int g_backspace = 0;
 /**
  * @brief 重定向scanf
  *
  * @param dev The device.
  * @param name The name of the device.
  * @param type The type of the device.
  * @param flags The support flags of the device.
  * @param ops The operations of the device.
  * @param drv The driver of the device.
  *
  * @return 0 on success, otherwise an error code.
  */ 
int std::fgetc(FILE *f)
{
    uint8_t ch = 0;
	if(g_backspace)
	{
		g_backspace =0;
		return g_last_char;
	}
    HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
	g_last_char = ch;
    return ch;
}
int __backspace(FILE *stream)/* 判断字符，如果不对，则还回去用上一次的字符 */
{
	g_backspace = 1;
	return 0;
}


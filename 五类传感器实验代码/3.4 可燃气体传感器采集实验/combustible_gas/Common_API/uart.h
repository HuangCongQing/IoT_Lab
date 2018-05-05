#ifndef __UART_H
#define __UART_H
#include"stm32f10x_conf.h"

#define COM_NUM 80 //定义数组大小;

typedef struct
{
	uint8_t ComBuf[COM_NUM];
	uint8_t num;
	
}TypedefUart;

void UartInit(uint8_t Uartx,uint32_t baud);
void SendByte(uint8_t Uartx,uint8_t Data);
void SendStr(u8 Uartx,uint8_t *str,uint8_t lenth);
void Uart1DataProcess(uint8_t Recv);
void Uart3DataProcess(uint8_t Recv);

void prvvUARTTxReadyISR( void );
void prvvUARTRxISR( void );

#endif



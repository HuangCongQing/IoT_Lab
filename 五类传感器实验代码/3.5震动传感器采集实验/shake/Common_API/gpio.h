#ifndef __GPIO_H__
#define __GPIO_H__

#include"stm32f10x_conf.h"

#define STATUS_L        GPIO_ResetBits(GPIOB,GPIO_Pin_4)  //status
#define STATUS_H        GPIO_SetBits(GPIOB,GPIO_Pin_4)

#define RS_485_RX_L     GPIO_ResetBits(GPIOB,GPIO_Pin_5)  //RS485_T
#define RS_485_RX_H     GPIO_SetBits(GPIOB,GPIO_Pin_5)   

#define RS_485_TX_L     GPIO_ResetBits(GPIOB,GPIO_Pin_6)  //RS485_R
#define RS_485_TX_H     GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define USER_L          GPIO_ResetBits(GPIOB,GPIO_Pin_7)  //USER1
#define USER_H          GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define RS485_L         GPIO_ResetBits(GPIOA,GPIO_Pin_1)  //RS485¿ØÖÆ¶Ë
#define RS485_H         GPIO_SetBits(GPIOA,GPIO_Pin_1)

void LedGpioInit(char port,uint8_t status,uint8_t rx,uint8_t tx,uint8_t user);
void LedOn(uint8_t Ledx);
void LedOff(uint8_t Ledx);

void Sm_GPIOInit(uint8_t channel);

#endif


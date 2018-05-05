#ifndef __DELAY_H__
#define __DELAY_H__
#include"stm32f10x_conf.h"
void TickDelayInit(uint8_t sysclk);
void TickDelayUs(uint32_t nus);
void TickDelayMs(uint16_t nms);

void DelayUs(uint16_t nus) ;
void DelayMs(uint16_t nms);

#endif


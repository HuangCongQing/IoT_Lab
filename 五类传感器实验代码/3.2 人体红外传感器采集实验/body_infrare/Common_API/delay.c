/********************************************************************************
* Copyright (c) 2015,联创中控（北京）科技有限公司
* All rights reserved.
*
* 文件名称：delay.c
* 摘    要：系统滴答定时器初始化，微妙，毫秒延时；2）for死循环微妙，毫秒延时;
* 当前版本: V1.1
* 作    者：姜怀伟
* 完成日期：2015年12月24日
* 修改摘要：

* 取代版本: V1.0
* 原 作 者：姜怀伟
* 完成日期：2015年11月19日
* 修改摘要: 
********************************************************************************/

#include  "main.h"

static uint16_t  fac_us=0;
static uint16_t  fac_ms=0;
/****************************************************
*systick(系统定时器定时说明)：
*驱动系统定时器的时钟源有两个，分别为(HCLK)或者(HCLK/8);
*系统时钟定时器的周期与两个因素有关，分别如下：
1）时钟频率，2）reload值；
****************************************************/

void TickDelayInit(uint8_t sysclk)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	   //滴答时钟为系统时钟的8分频;即最高频率为9MHz；
	fac_us=sysclk/8;         //fac_us = 9;	 reload值为9，   即系统时钟周期为1us；
	fac_ms=(u16)fac_us*1000; //fac_ms = 9000;reload值为9000，即系统时钟周期为1ms;
}								    

/*****************************************************
*函数名称： SmTickDelayUs();
*输入参数： nus 重装载数值; 
*输出参数： 无；
*说明    ： 如1ms周期，则nus = 1000;
******************************************************/
void TickDelayUs(uint32_t nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us;   		 
	SysTick->VAL=0x00;        
	SysTick->CTRL=0x01 ;       	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));  
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;      
}

/*****************************************************
*函数名称： SmTickDelayMs();
*输入参数： nms 重装载数值; 
*输出参数： 无；
*说明    ： 如10ms周期，则nms = 10;
******************************************************/
void TickDelayMs(uint16_t nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;           
	SysTick->CTRL=0x01 ;          
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;        	    
}   

/*****************************************************
*函数名称： DelayUs();
*输入参数： nus 重装载数值; 
*输出参数： 无；
*说明    ： 如1ms周期，则nus = 1000;最大值65535
******************************************************/
void DelayUs(uint16_t nus)   
{
	unsigned char j,k;
	for(j=0;j<nus;j++)
	  for(k=0;k<93;k++);
}

/*****************************************************
*函数名称： DelayMs();
*输入参数： nms 重装载数值; 
*输出参数： 无；
*说明    ： 如1ms周期，则nms = 1;   最大值65535
******************************************************/
void DelayMs(uint16_t nms)
{
   unsigned int j,k;
   for(j=0;j<nms;j++)
      for(k=0;k<10000;k++);
} 

/**********************end_file@*****************************************/



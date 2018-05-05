/********************************************************************************
* Copyright (c) 2015,联创中控（北京）科技有限公司
* All rights reserved.
*
* 文件名称：gpio.c
* 摘    要：完成标准API GPIO初始化功能，LED灯初始化;RS485控制初始化;
* 当前版本: V1.1
* 作    者：姜怀伟
* 完成日期：2015年12月24日
* 修改摘要：

* 取代版本: V1.0
* 原 作 者：姜怀伟
* 完成日期：2015年11月19日
* 修改摘要: 
********************************************************************************/

#include"main.h"

/**************************************************************************
	函数名          ：LedGpioInit();
	入口参数port    ：选择GPIOA或者GPIOB，如GPIOA 怎参数输‘A’,GPIOB 则输入'B';
	入口参数status  ：开机指示灯端口初始化;
	入口参数rx      ：RS485接收指示灯端口初始化;
	入口参数tx      ：RS485发送指示灯端口初始化；
	入口参数user    ：传感器工作指示灯端口初始化;
	出口参数        ：无；
	功能            ：实现模块LED灯初始化功能,并打开status led,rx,tx,user led;	
***************************************************************************/
void LedGpioInit(char port,uint8_t status,uint8_t rx,uint8_t tx,uint8_t user)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	if(port == 'A')
	{
		GPIO_InitStructure.GPIO_Pin   =   (1 << status)|(1 << rx)|(1 << tx)|(1 << user);
		GPIO_InitStructure.GPIO_Speed =   GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode  =   GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure); 	
	}
	if(port == 'B')
	{
		GPIO_InitStructure.GPIO_Pin   =   (1 << status)|(1 << rx)|(1 << tx)|(1 << user);
		GPIO_InitStructure.GPIO_Speed =   GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode  =   GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure); 		
	}
	LedOn(4);  
	LedOff(5); 
	LedOff(6); 
	LedOff(7); 			
}

/**************************************************************************
	函数名          ：Sm_GPIOInit();
	输入参数 channel：选择传感器输入端口号
	输出参数        ：无
	功能            ：实现传感器模块输入端口初始化功能;	RS485控制使能;
***************************************************************************/
void Sm_GPIOInit(uint8_t channel)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin   =   (1<< channel);
  GPIO_InitStructure.GPIO_Speed =   GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  =   GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin   =   GPIO_Pin_1;   //RS485控制端口
  GPIO_InitStructure.GPIO_Speed =   GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  =   GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 	
}

/**************************************************************************
	函数名          ：LedOn();
	输入参数 Ledx   ：LED端口号选择：【4 status】【5 RX】【6 TX】【 7 user】；
	输出参数        ：无
	功能            ：实现对指定LED灯打开操作;
***************************************************************************/
void LedOn(uint8_t Ledx)
{
	 GPIO_ResetBits(GPIOB,(1 << Ledx));
}

/**************************************************************************
	函数名          ：LedOff();
	输入参数 Ledx   ：LED端口号选择：【4 status】【5 RX】【6 TX】【 7 user】；
	输出参数        ：无
	功能            ：实现对指定LED灯关闭操作;
***************************************************************************/
void LedOff(uint8_t Ledx)
{
	 GPIO_SetBits(GPIOB,(1 << Ledx));
}


/**********************end_file@*****************************************/














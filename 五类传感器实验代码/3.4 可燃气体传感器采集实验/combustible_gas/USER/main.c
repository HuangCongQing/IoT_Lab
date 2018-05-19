/********************************************************************************
* Copyright (c) 2015,联创中控（北京）科技有限公司
* All rights reserved.
*
* 文件名称：main.c
* 摘    要：完成函数初始化，信号采集，并通过串口2上传数据给PC机。
* 当前版本: V1.3
* 作    者：张仁旺
* 完成日期：2017年2月7日
* 修改摘要：将传感器数据由串口1，RS232（USB3.0口）输出修改为由串口2，RS485（RJ11口）输出
********************************************************************************/

#include"main.h"

float value = 0;       								 					// ADC采集传感器获取值变量;
uint32_t delaytime = 0; 												// 延时变量;

/***************************************************/
/*函数名称 : McuInit();                            */
/*输入参数 ：无                                    */
/*输出参数 ：无                                    */
/*功能说明 : 1) 完成系统时钟初始化，倍频72MHz;     */
/*           2) LED端口初始化；                    */
/* 			     3）串口初始化；                       */
/*	         4) 芯片状态处理，初值设定;		         */
/***************************************************/
void McuInit(void)
{
	RCC_Configuration();     											 // clock config,打开相应外设时钟;
	LedGpioInit('B',4,5,8,9);											// LED灯初始化
	Sm_GPIOInit(4);														    // 将PA4配置为ADC1的通道4同时将485控制引脚初始化
	SmAdcInit(4);           											// ADC采样初始化 
	UartInit(2,115200);													 // USART2初始化
}

///**************************************************
//*函数名称 : main();
//*输入参数 ：无
//*输出参数 ：无
//*功能说明 : 1) MCUInit函数初始化，之后进入死循环，等待上位机查询；
//*           2) 每隔1秒查询一次传感器数据;
//**************************************************/
int main(void)
{
	McuInit();
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	printf("\r\n可燃气气体传感器采集实验r\n");
	while(1)
	{
		if(delaytime==500000)
			LedOff(4);
		if((delaytime++)>=1000000)
		{
			delaytime=0;
			value=read_ADC(4)/4096.0*3.3;
			value=value*4*100;
			LedOn(4);
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			printf("??????:%d ppm\r\n",(uint16_t)value);
		}
	}
}
/**********************end_file@*****************************************/





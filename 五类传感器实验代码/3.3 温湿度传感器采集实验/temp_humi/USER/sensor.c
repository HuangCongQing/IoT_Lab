/********************************************************************************
* Copyright (c) 2015,联创中控（北京）科技有限公司
* All rights reserved.
*
* 文件名称：sensor.c
* 摘    要：获取通道值，并返回; 温湿度传感器数据读取;
* 当前版本: V1.2
* 作    者：鲍兴慧
* 完成日期：2015年12月26日
* 修改摘要：

* 取代版本: V1.1
* 原 作 者：姜怀伟
* 完成日期：2015年12月24日
* 修改摘要: 
********************************************************************************/

#include"main.h"

static GPIO_InitTypeDef GPIO_InitStructure;

/**************************************************************************
	函数名          ：GetInput();
	输入参数 channel: 通道号;
	输出参数        ：端口值，取值范围【0,1】
	功能            ：获取传感器采样值；
***************************************************************************/
uint8_t GetInput(uint8_t  channel)
{
	return((GPIO_ReadInputDataBit(GPIOB, (1 << channel)) == 1));
}

/**************************************************************************
	函数名          ：SetOutput();
	输入参数 channel: 通道号;
	输入参数 value  ：取值范围【0,1】
	功能            ：对端口置0或置1
***************************************************************************/
void SetOutput(uint8_t channel, uint8_t value)
{
	
}

/**************************************************************************
	函数名      ：DHT11_Init();
	输入参数    : 无；
	输入参数    ：无；
	功能        ：对温湿度传感器端口初始化;
***************************************************************************/
void DHT11_Init(void)
{
		 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		// 开漏输出
	GPIO_Init(GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_10);						// 开机置“1”
}

/*****************************************************
*函数名称： SmDHT11IOIn();
*输入参数： 无；
*输出参数： 无；
*说明    ： 改变为输入模式;
******************************************************/
static void SmDHT11IOIn(void)
{
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIO_PORT, &GPIO_InitStructure);	
}

/*****************************************************
*函数名称： SmDHT11IOOut();
*输入参数： 无；
*输出参数： 无；
*说明    ： 改变为输出模式;
******************************************************/
static void SmDHT11IOOut(void)
{
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIO_PORT, &GPIO_InitStructure);
}

/*****************************************************
*函数名称： SmDHT11ReadBitState();
*输入参数： 无；
*输出参数： 无；
*说明    ： 读取端口值状态;
******************************************************/
static uint8_t SmDHT11ReadBitState(void)
{
  return GPIO_ReadInputDataBit(GPIO_PORT, GPIO_PIN);
}

/*****************************************************
*函数名称： SmDHT11Reset();
*输入参数： 无；
*输出参数： 无
*说明    ： 单总线命令：主机发送复位脉冲(总线拉低)，时间至少18ms;
*           从机等待15 - 60us；
*           从机发送应答命令;(总线拉低)，拉低时间 60- 240us;
******************************************************/
void SmDHT11Reset(void)	   
{                 
	SmDHT11IOOut();									// 将PB10设置为输出模式
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);				// PB10输出低电平
	TickDelayMs(18);								// 延时18ms
	GPIO_SetBits(GPIOB,GPIO_Pin_10);				// PB10输出高电平
	TickDelayUs(30);								// 延时30ms
}

/*****************************************************
*函数名称： SmDHT11Check();
*输入参数： 无；
*输出参数： 无；
*说明    ： 读取端口值状态,从机是否应答成功;
******************************************************/
uint8_t SmDHT11Check(void) 	   
{   
  u8 retry=0;
  SmDHT11IOIn();									// 将PB10设置为输入模式
  while(!SmDHT11ReadBitState() && (retry<100))
  {													// 检测PB10持续为高电平的时间
    retry++;
    TickDelayUs(1);
  }	 
  if(retry>=100)return 1;							// 如果该时间过长，不符合时序，返回1，表示读取失败。
  else retry=0;										// retry清零
  while(SmDHT11ReadBitState() && (retry<100))
  {													// 检测PB10持续为低电平的时间
    retry++;
    TickDelayUs(1);
  }
  if(retry>=100)return 1;							// 如果该时间过长，不符合时序，返回1，表示读取失败。
  return 0;											// 接收完DHT11的低电平和高电平信号，准备接收数据。
}

/*****************************************************
*函数名称： SmDHT11ReadBit();
*输入参数： 无；
*输出参数： 二进制位;
*说明    ： 无；
******************************************************/
uint8_t SmDHT11ReadBit(void)						// 接收位
{
  u8 retry=0;
  while(SmDHT11ReadBitState() && (retry<100))		// 等待PB10变为低电平，因为DHT11会先发送低电平。
  {
    retry++;
    TickDelayUs(1);
  }
  retry=0;											// retry清零
  while(!SmDHT11ReadBitState() && (retry<100))		// 等待PB10变为高电平
  {
    retry++;
    TickDelayUs(1);
  }
  TickDelayUs(40);									// 延时40μs
  if(SmDHT11ReadBitState())return 1;				// 如果此时仍为高电平，该位数据为“1”
  else return 0;									// 如果此时为低电平，该位数据为“0”
}

/*****************************************************
*函数名称： SmDHT11ReadByte();
*输入参数： 无；
*输出参数： 读一个字节数据；
*说明    ： 无；
******************************************************/
uint8_t SmDHT11ReadByte(void)						// 每8个位保存为一个字节
{
  uint8_t i,dat = 0;
	
  for(i=0;i<8;i++)									// 将接收到的位数据依次保存到dat中
  {
    dat<<=1; 
    dat|=SmDHT11ReadBit();
  }						    
  return dat;										// 接收并保存完8位数据，返回dat，完成一个字节的接收
}

/*****************************************************
*函数名称： SmDHT11ReadData();
*输入参数： 无；
*输出参数： 读一包数据；
*说明    ： 如果SmDHT11Check()函数返回1，则数据错误；直接返回；
*           如果返回0，表示应答成功；            
******************************************************/
uint8_t SmDHT11ReadData(void)    
{
	uint8_t buf[5];
	uint8_t i;       
	static unsigned int t, h;
	SmDHT11Reset();									// 给DHT11发送复位命令，等待应答信号;
	if(SmDHT11Check())								// 检查是否应答成功;
	{
		return 1;									// 未检测到正确的应答信号，返回
	}
	for(i=0;i<5;i++)								// 存储DHT11发送的5个字节到数组buf[5]中
	{
		buf[i]=SmDHT11ReadByte();
	}
	if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])		// 验证校验位
	{
		h = buf[0];
		t = buf[2];
		LedOn(7);									// 验证成功，点亮发送指示灯User1
		printf("humi: %u%% %RH,temp: %u ℃\r\n", h, t);		// 通过USART2打印温湿度值
	}
	return 0;	    
}

/**********************end_file@*****************************************/


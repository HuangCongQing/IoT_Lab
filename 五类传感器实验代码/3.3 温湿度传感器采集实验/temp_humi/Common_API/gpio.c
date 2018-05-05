/********************************************************************************
* Copyright (c) 2015,�����пأ��������Ƽ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�gpio.c
* ժ    Ҫ����ɱ�׼API GPIO��ʼ�����ܣ�LED�Ƴ�ʼ��;RS485���Ƴ�ʼ��;
* ��ǰ�汾: V1.1
* ��    �ߣ�����ΰ
* ������ڣ�2015��12��24��
* �޸�ժҪ��

* ȡ���汾: V1.0
* ԭ �� �ߣ�����ΰ
* ������ڣ�2015��11��19��
* �޸�ժҪ: 
********************************************************************************/

#include"main.h"

/**************************************************************************
	������          ��LedGpioInit();
	��ڲ���port    ��ѡ��GPIOA����GPIOB����GPIOA �������䡮A��,GPIOB ������'B';
	��ڲ���status  ������ָʾ�ƶ˿ڳ�ʼ��;
	��ڲ���rx      ��RS485����ָʾ�ƶ˿ڳ�ʼ��;
	��ڲ���tx      ��RS485����ָʾ�ƶ˿ڳ�ʼ����
	��ڲ���user    ������������ָʾ�ƶ˿ڳ�ʼ��;
	���ڲ���        ���ޣ�
	����            ��ʵ��ģ��LED�Ƴ�ʼ������,����status led,rx,tx,user led;	
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
	������          ��Sm_GPIOInit();
	������� channel��ѡ�񴫸�������˿ں�
	�������        ����
	����            ��ʵ�ִ�����ģ������˿ڳ�ʼ������;	RS485����ʹ��;
***************************************************************************/
void Sm_GPIOInit(uint8_t channel)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin   =   (1<< channel);
  GPIO_InitStructure.GPIO_Speed =   GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  =   GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin   =   GPIO_Pin_1;   //RS485���ƶ˿�
  GPIO_InitStructure.GPIO_Speed =   GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  =   GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 	
}

/**************************************************************************
	������          ��LedOn();
	������� Ledx   ��LED�˿ں�ѡ�񣺡�4 status����5 RX����6 TX���� 7 user����
	�������        ����
	����            ��ʵ�ֶ�ָ��LED�ƴ򿪲���;
***************************************************************************/
void LedOn(uint8_t Ledx)
{
	 GPIO_ResetBits(GPIOB,(1 << Ledx));
}

/**************************************************************************
	������          ��LedOff();
	������� Ledx   ��LED�˿ں�ѡ�񣺡�4 status����5 RX����6 TX���� 7 user����
	�������        ����
	����            ��ʵ�ֶ�ָ��LED�ƹرղ���;
***************************************************************************/
void LedOff(uint8_t Ledx)
{
	 GPIO_SetBits(GPIOB,(1 << Ledx));
}


/**********************end_file@*****************************************/














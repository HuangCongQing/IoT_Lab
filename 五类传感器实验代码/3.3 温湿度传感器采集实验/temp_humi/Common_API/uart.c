/********************************************************************************
* Copyright (c) 2015,�����пأ��������Ƽ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�uart.c
* ժ    Ҫ�����ڳ�ʼ�����硾1 2 3�������ڽ����жϴ���; ����1���ͺ�����ӳ��;
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

TypedefUart Comm1;
TypedefUart Comm3;

/********************************************************
*�������ƣ�UartNvicInit();
*����������� 
*����������ޣ�
*ע��    �����������ж�����;
********************************************************/
void UartNvicInit(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
    /*-----------------//����1�ж�����----------------------------------*/
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;  //����1
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);
	
	  /*-----------------//����3�ж�����----------------------------------*/
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;  //����3
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);
}

/**************************************************************************
	������          ��UartInit();
	��ڲ���Uartx   ��ѡ�񴮿ںţ�
	��ڲ���baud    ��ѡ������;
	���ڲ���        ���ޣ�
	����            ������ѡ�����ʵ�ִ���1������2������3�ĳ�ʼ����
***************************************************************************/
void UartInit(uint8_t Uartx,uint32_t baud)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;

    if(Uartx == 1)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);
			/*--------------------------����1 GPIO��ʼ��--------------------------*/
			//TXD1����Ϊ����������� 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_9 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;	     // �����������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     // ����������50MHz
			GPIO_Init(GPIOA, &GPIO_InitStructure);				         // ѡ��A�˿�
			
			//RXD1����Ϊ���ù������� 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_10 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING; // ���ù�������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     // ����������50MHz
			GPIO_Init(GPIOA, &GPIO_InitStructure);				         // ѡ��A�˿�
			/*------------------------����1 ģʽ��ʼ��---------------------------*/
			USART_InitStructure.USART_BaudRate = baud;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART1, &USART_InitStructure);

			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			USART_Cmd (USART1, ENABLE);
		}	
		else if(Uartx == 2)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);
			/*-------------------------����2 GPIO��ʼ��-------------------------*/
			//TXD2����Ϊ����������� 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_2 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;		   // �����������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   // ����������50MHz
			GPIO_Init(GPIOA, &GPIO_InitStructure);				         // ѡ��A�˿�
			
			//RXD2����Ϊ���ù������� 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_3 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING; // ���ù�������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     // ����������50MHz
			GPIO_Init(GPIOA, &GPIO_InitStructure);				         // ѡ��A�˿�

			/*--------------------------USART2 ģʽ��ʼ��-----------------------------*/ 
			USART_InitStructure.USART_BaudRate = baud;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART2, &USART_InitStructure);

			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
			USART_Cmd (USART2, ENABLE);			
		}
		else if(Uartx == 3)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
			/*-------------------------����3 GPIO��ʼ��-------------------------*/
			//TXD3����Ϊ����������� 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_10 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;		     // �����������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		     // ����������50MHz
			GPIO_Init(GPIOB, &GPIO_InitStructure);				           // ѡ��B�˿�
			//RXD3����Ϊ���ù������� 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_11 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;   // ���ù�������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	       // ����������50MHz
			GPIO_Init(GPIOB, &GPIO_InitStructure);				           // ѡ��B�˿�

			/*--------------------------USART3 ģʽ��ʼ��-----------------------------*/ 
			USART_InitStructure.USART_BaudRate = baud;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART3, &USART_InitStructure);

			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
			USART_Cmd (USART3, ENABLE);			
		}	
    UartNvicInit(); //��������1������3�����ж�;		
}

/**************************************************************************
    ������         :SendByte();
    ��ڲ���Uartx  :���ڷ��Ͷ˿ں�ѡ��;
    ��ڲ���Data   :��Ҫ���͵�����;
    ���ڲ�����     :��
    ����           :ָ�����ںŷ���һ���ֽ�����;
***************************************************************************/
void SendByte(uint8_t Uartx,uint8_t Data)
{
	  if(Uartx == 1)
		{
			USART_ClearFlag(USART1,USART_FLAG_TC);
			USART_SendData(USART1, Data);
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
			USART_ClearFlag(USART1,USART_FLAG_TC);			
		}
	  if(Uartx == 2)
		{
			USART_ClearFlag(USART2,USART_FLAG_TC);
			USART_SendData(USART2, Data);
			while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
			USART_ClearFlag(USART2,USART_FLAG_TC);			
		}		
	  if(Uartx == 3)
		{
			USART_ClearFlag(USART3,USART_FLAG_TC);
			USART_SendData(USART3, Data);
			while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
			USART_ClearFlag(USART3,USART_FLAG_TC);			
		}				
}

/**************************************************************************
    ������         :SendStr();
    ��ڲ���Uartx  :���ڷ��Ͷ˿ں�ѡ��;
    ��ڲ���*str   :��Ҫ���͵�����ָ��;
    ��ڲ���lenth  :�������ݳ���;
    ���ڲ�����     :��
    ����           :ָ�����ںŷ���һ���ֽ�����;
***************************************************************************/
void SendStr(u8 Uartx,uint8_t *str,uint8_t lenth)
{
	  uint8_t i;
	  if(Uartx <= 3)
		{
	     for(i = 0;i < lenth; i++)
       {
				 SendByte(Uartx , *str++);
			 }
		}		
}

/**************************************************************************
    ������         :Uart1DataProcess();
    ��ڲ��� Recv  :���յ�����1���ݣ����洢;
    ���ڲ�����     :��
    ����           :����1�жϺ���������һ���ַ���
***************************************************************************/
void Uart1DataProcess(uint8_t Recv)
{
	 if(Comm1.num >= COM_NUM)Comm1.num = 0;
	 Comm1.ComBuf[Comm1.num++] = Recv;
	 SendByte(1,Recv);
}

/**************************************************************************
    ������         :Uart3DataProcess();
    ��ڲ��� Recv  :���յ�����3���ݣ����洢;
    ���ڲ�����     :��
    ����           :����3�жϺ���������һ���ַ���
***************************************************************************/
/*void Uart3DataProcess(uint8_t Recv)
{
	 if(Comm3.num >= COM_NUM)Comm3.num = 0;
	 Comm3.ComBuf[Comm3.num++] = Recv;	
	 SendByte(3,Recv);
}*/

/**************************************************************************
    ������         :USART1_IRQHandler();
    ��ڲ���       :��
    ���ڲ�����     :��
    ����           :����1�жϺ���������һ���ַ���
***************************************************************************/
void USART1_IRQHandler(void)
{ 
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
	   USART_ClearITPendingBit(USART1, USART_IT_RXNE);//����жϱ�־λ
		 Uart1DataProcess(USART_ReceiveData(USART1));
	}
}

/**************************************************************************
    ������         :USART3_IRQHandler();
    ��ڲ���       :��
    ���ڲ�����     :��
    ����           :����3�жϺ���������һ���ַ���
***************************************************************************/
/*void USART3_IRQHandler(void)
{ 
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
	   USART_ClearITPendingBit(USART3, USART_IT_RXNE);//����жϱ�־λ
		 Uart3DataProcess(USART_ReceiveData(USART3));
	}
}
*/
/**************************************************************************
    ������         :USART2_IRQHandler();
    ��ڲ���       :��
    ���ڲ�����     :��
    ����           :����2�жϺ���������һ���ַ���modbus�й��ж�;
***************************************************************************/
/*void USART2_IRQHandler(void)
{ 
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)//���������ж�
	{
			prvvUARTRxISR(); //����жϱ�־λ
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
		
	if(USART_GetITStatus(USART2, USART_IT_TC) == SET)  //��������ж�,��λ���;
	{
			prvvUARTTxReadyISR();//����жϱ�־
			USART_ClearITPendingBit(USART2, USART_IT_TC);
	}
}*/

/**************************************************************************
    ������  ��      fputc
    ��ڲ�����	    ch
    ��ڲ�����	    *f
    ���ڲ�����      ��
    ����    ��		  ��������ض���
***************************************************************************/
int fputc(int ch, FILE *f)		  
{
		USART_SendData(USART2, (unsigned char) ch); 
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
		return (int)ch;
}

/**********************end_file@*****************************************/


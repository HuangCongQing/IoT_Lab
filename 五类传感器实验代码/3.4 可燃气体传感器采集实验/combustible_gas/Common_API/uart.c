/********************************************************************************
* Copyright (c) 2015,联创中控（北京）科技有限公司
* All rights reserved.
*
* 文件名称：uart.c
* 摘    要：串口初始化，如【1 2 3】；串口接收中断处理; 串口1发送函数重映射;
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

TypedefUart Comm1;
TypedefUart Comm3;

/********************************************************
*函数名称：UartNvicInit();
*输入参数：无 
*输出参数：无；
*注释    ：开启串口中断向量;
********************************************************/
void UartNvicInit(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
    /*-----------------//串口1中断向量----------------------------------*/
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;  //串口1
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);
	
	  /*-----------------//串口3中断向量----------------------------------*/
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;  //串口3
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);
}

/**************************************************************************
	函数名          ：UartInit();
	入口参数Uartx   ：选择串口号；
	入口参数baud    ：选择波特率;
	出口参数        ：无；
	功能            ：根据选择可以实现串口1，串口2，串口3的初始化；
***************************************************************************/
void UartInit(uint8_t Uartx,uint32_t baud)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;

    if(Uartx == 1)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);
			/*--------------------------串口1 GPIO初始化--------------------------*/
			//TXD1设置为复用推挽输出 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_9 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;	     // 复用推挽输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     // 最高输出速率50MHz
			GPIO_Init(GPIOA, &GPIO_InitStructure);				         // 选择A端口
			
			//RXD1设置为复用功能输入 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_10 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING; // 复用功能输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     // 最高输出速率50MHz
			GPIO_Init(GPIOA, &GPIO_InitStructure);				         // 选择A端口
			/*------------------------串口1 模式初始化---------------------------*/
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
			/*-------------------------串口2 GPIO初始化-------------------------*/
			//TXD2设置为复用推挽输出 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_2 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;		   // 复用推挽输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   // 最高输出速率50MHz
			GPIO_Init(GPIOA, &GPIO_InitStructure);				         // 选择A端口
			
			//RXD2设置为复用功能输入 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_3 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING; // 复用功能输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     // 最高输出速率50MHz
			GPIO_Init(GPIOA, &GPIO_InitStructure);				         // 选择A端口

			/*--------------------------USART2 模式初始化-----------------------------*/ 
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
			/*-------------------------串口3 GPIO初始化-------------------------*/
			//TXD3设置为复用推挽输出 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_10 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;		     // 复用推挽输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		     // 最高输出速率50MHz
			GPIO_Init(GPIOB, &GPIO_InitStructure);				           // 选择B端口
			//RXD3设置为复用功能输入 
			GPIO_InitStructure.GPIO_Pin   =	GPIO_Pin_11 ; 								
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;   // 复用功能输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	       // 最高输出速率50MHz
			GPIO_Init(GPIOB, &GPIO_InitStructure);				           // 选择B端口

			/*--------------------------USART3 模式初始化-----------------------------*/ 
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
    UartNvicInit(); //开启串口1，串口3接收中断;		
}

/**************************************************************************
    函数名         :SendByte();
    入口参数Uartx  :串口发送端口号选择;
    入口参数Data   :需要发送的数据;
    出口参数：     :无
    功能           :指定串口号发送一个字节数据;
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
    函数名         :SendStr();
    入口参数Uartx  :串口发送端口号选择;
    入口参数*str   :需要发送的数据指针;
    入口参数lenth  :发送数据长度;
    出口参数：     :无
    功能           :指定串口号发送一个字节数据;
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
    函数名         :Uart1DataProcess();
    入口参数 Recv  :接收到串口1数据，并存储;
    出口参数：     :无
    功能           :串口1中断函数，接收一个字符；
***************************************************************************/
void Uart1DataProcess(uint8_t Recv)
{
	 if(Comm1.num >= COM_NUM)Comm1.num = 0;
	 Comm1.ComBuf[Comm1.num++] = Recv;
	 SendByte(1,Recv);
}

/**************************************************************************
    函数名         :Uart3DataProcess();
    入口参数 Recv  :接收到串口3数据，并存储;
    出口参数：     :无
    功能           :串口3中断函数，接收一个字符；
***************************************************************************/
/*void Uart3DataProcess(uint8_t Recv)
{
	 if(Comm3.num >= COM_NUM)Comm3.num = 0;
	 Comm3.ComBuf[Comm3.num++] = Recv;	
	 SendByte(3,Recv);
}*/

/**************************************************************************
    函数名         :USART1_IRQHandler();
    入口参数       :无
    出口参数：     :无
    功能           :串口1中断函数，接收一个字符；
***************************************************************************/
void USART1_IRQHandler(void)
{ 
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
	   USART_ClearITPendingBit(USART1, USART_IT_RXNE);//清除中断标志位
		 Uart1DataProcess(USART_ReceiveData(USART1));
	}
}

/**************************************************************************
    函数名         :USART3_IRQHandler();
    入口参数       :无
    出口参数：     :无
    功能           :串口3中断函数，接收一个字符；
***************************************************************************/
/*void USART3_IRQHandler(void)
{ 
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
	   USART_ClearITPendingBit(USART3, USART_IT_RXNE);//清除中断标志位
		 Uart3DataProcess(USART_ReceiveData(USART3));
	}
}
*/
/**************************************************************************
    函数名         :USART2_IRQHandler();
    入口参数       :无
    出口参数：     :无
    功能           :串口2中断函数，接收一个字符；modbus有关中断;
***************************************************************************/
/*void USART2_IRQHandler(void)
{ 
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)//发生接收中断
	{
			prvvUARTRxISR(); //清除中断标志位
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
		
	if(USART_GetITStatus(USART2, USART_IT_TC) == SET)  //发生完成中断,移位完成;
	{
			prvvUARTTxReadyISR();//清除中断标志
			USART_ClearITPendingBit(USART2, USART_IT_TC);
	}
}*/

/**************************************************************************
    函数名  ：      fputc
    入口参数：	    ch
    入口参数：	    *f
    出口参数：      无
    功能    ：		  输出函数重定向
***************************************************************************/
int fputc(int ch, FILE *f)		  
{
		USART_SendData(USART2, (unsigned char) ch); 
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
		return (int)ch;
}

/**********************end_file@*****************************************/


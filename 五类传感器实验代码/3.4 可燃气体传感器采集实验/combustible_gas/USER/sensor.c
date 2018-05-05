/********************************************************************************
* Copyright (c) 2015,联创中控（北京）科技有限公司
* All rights reserved.
*
* 文件名称：sensor.c
* 摘    要：获取通道值，并返回;
* 当前版本: V1.2
* 作    者：UICollege
* 修改摘要: 
********************************************************************************/

#include"main.h"
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

/*****************************************************
*   函数名称：SmAdcInit();
*   入口参数：channel ADC通道号选择；
*   出口参数：无；
*   说明    ：开启ADC采样时钟，数据采集模式，并开启ADC采样模式；
*****************************************************/
void SmAdcInit(uint8_t channel)
{
    ADC_InitTypeDef ADC_InitStruct;
	  
    ADC_DeInit(ADC1);									// 复位ADC1
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;     // ADC1工作在独立模式
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	// ADC数据右对齐
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;    // 禁止连续转换
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;// 由软件触发模数转换
    ADC_InitStruct.ADC_NbrOfChannel = channel; 			// 选择通道号    
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;			// 单通道模式
    ADC_Init(ADC1, &ADC_InitStruct);					// 根据结构体ADC_InitStruct配置ADC1
     
    ADC_RegularChannelConfig(ADC1,channel, 1, ADC_SampleTime_71Cycles5);	// 设置ADC1的指定通道的转化顺序和采样时间
    ADC_Cmd(ADC1,ENABLE);								// 使能ADC1
    ADC_ResetCalibration(ADC1);							// 重置ADC1的校准寄存器

    while(ADC_GetResetCalibrationStatus(ADC1)); 		// 等待复位校正完成;
    
    ADC_StartCalibration(ADC1);							// 开启ADC1的校准状态
    while(ADC_GetCalibrationStatus(ADC1));				// 等待ADC1校准完成
            
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);				// 使能ADC1的软件转换启动功能
}

/*****************************************************
*   函数名称：read_ADC();
*   入口参数：无；
*   出口参数：ADC采集数据值；
*   说明    ：采集对应通道的数据；指定规则组通道，一个序列，采样时间
*****************************************************/
uint16_t read_ADC(uint8_t channel) 
{
	uint16_t temp = 0;
    	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				// 启动ADC转换
    while(! ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));		// 等待ADC转换完成
	temp = ADC_GetConversionValue(ADC1);				// 读取ADC的值
	return (temp);
}

/**********************end_file@*****************************************/


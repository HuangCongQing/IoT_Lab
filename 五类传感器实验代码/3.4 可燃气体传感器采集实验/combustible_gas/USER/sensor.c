/********************************************************************************
* Copyright (c) 2015,�����пأ��������Ƽ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�sensor.c
* ժ    Ҫ����ȡͨ��ֵ��������;
* ��ǰ�汾: V1.2
* ��    �ߣ�UICollege
* �޸�ժҪ: 
********************************************************************************/

#include"main.h"
/**************************************************************************
	������          ��GetInput();
	������� channel: ͨ����;
	�������        ���˿�ֵ��ȡֵ��Χ��0,1��
	����            ����ȡ����������ֵ��
***************************************************************************/
uint8_t GetInput(uint8_t  channel)
{
	return((GPIO_ReadInputDataBit(GPIOB, (1 << channel)) == 1));
}

/**************************************************************************
	������          ��SetOutput();
	������� channel: ͨ����;
	������� value  ��ȡֵ��Χ��0,1��
	����            ���Զ˿���0����1
***************************************************************************/
void SetOutput(uint8_t channel, uint8_t value)
{
	
}

/*****************************************************
*   �������ƣ�SmAdcInit();
*   ��ڲ�����channel ADCͨ����ѡ��
*   ���ڲ������ޣ�
*   ˵��    ������ADC����ʱ�ӣ����ݲɼ�ģʽ��������ADC����ģʽ��
*****************************************************/
void SmAdcInit(uint8_t channel)
{
    ADC_InitTypeDef ADC_InitStruct;
	  
    ADC_DeInit(ADC1);									// ��λADC1
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;     // ADC1�����ڶ���ģʽ
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	// ADC�����Ҷ���
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;    // ��ֹ����ת��
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;// ���������ģ��ת��
    ADC_InitStruct.ADC_NbrOfChannel = channel; 			// ѡ��ͨ����    
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;			// ��ͨ��ģʽ
    ADC_Init(ADC1, &ADC_InitStruct);					// ���ݽṹ��ADC_InitStruct����ADC1
     
    ADC_RegularChannelConfig(ADC1,channel, 1, ADC_SampleTime_71Cycles5);	// ����ADC1��ָ��ͨ����ת��˳��Ͳ���ʱ��
    ADC_Cmd(ADC1,ENABLE);								// ʹ��ADC1
    ADC_ResetCalibration(ADC1);							// ����ADC1��У׼�Ĵ���

    while(ADC_GetResetCalibrationStatus(ADC1)); 		// �ȴ���λУ�����;
    
    ADC_StartCalibration(ADC1);							// ����ADC1��У׼״̬
    while(ADC_GetCalibrationStatus(ADC1));				// �ȴ�ADC1У׼���
            
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);				// ʹ��ADC1�����ת����������
}

/*****************************************************
*   �������ƣ�read_ADC();
*   ��ڲ������ޣ�
*   ���ڲ�����ADC�ɼ�����ֵ��
*   ˵��    ���ɼ���Ӧͨ�������ݣ�ָ��������ͨ����һ�����У�����ʱ��
*****************************************************/
uint16_t read_ADC(uint8_t channel) 
{
	uint16_t temp = 0;
    	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				// ����ADCת��
    while(! ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));		// �ȴ�ADCת�����
	temp = ADC_GetConversionValue(ADC1);				// ��ȡADC��ֵ
	return (temp);
}

/**********************end_file@*****************************************/


#ifndef  __SENSOR_H_
#define  __SENSOR_H_

#include"stm32f10x_conf.h"

#define  	AIR_QUALITY             (0)    //  ��������������  25 03 20 00 00 01
#define  	COMBUSTIBLE_GAS         (0)    //  ��ȼ���崫����  28 03 20 00 00 01
#define   COLOR_IDENTIFICATE      (0)    //  ��ɫʶ�𴫸���  23 03 20 00 00 03
#define   ALCOHOL                 (0)    //  �ƾ�������      27 03 20 00 00 01
#define   CO2                     (0)    //  ������̼������  29 03 20 00 00 01   note
#define   AIR_PRESS               (0)    //  ��ѹ������      26 03 20 00 00 01
#define   PHOTOSENSITIVE          (0)    //  ����������      24 03 20 00 00 01
#define   SOIL_TEMP               (1)    //  �����¶ȴ�����  21 03 20 00 00 02   note 

#define   RELAY                   (0)    //  �̵���ִ����    90 06 22 00 00 01
#define   FAN                     (0)    //  ����ִ����      91 06 22 00 00 01
#define   HIGH_LED                (0)    //  ����LED         92 06 22 00 00 01   92 10 22 00 00 01 02 00 01
#define   HEAT                    (0)    //  ����ģ��        93 06 22 00 00 01
#define   SOUND_LIGHT             (0)    //  ���ⱨ��        94 10 22 00 00 02 04 00 01 00 01
#define   EM_TAP                  (0)    //  ��ŷ�          97 06 22 00 00 01

uint8_t GetInput(uint8_t  channel);
void SetOutput(uint8_t channel, uint8_t value);

void SmAdcInit(uint8_t channel);
uint16_t read_ADC(uint8_t channel);

#endif




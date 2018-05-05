#ifndef  __SENSOR_H_
#define  __SENSOR_H_

#include"stm32f10x_conf.h"

#define  	AIR_QUALITY             (0)    //  空气质量传感器  25 03 20 00 00 01
#define  	COMBUSTIBLE_GAS         (0)    //  可燃气体传感器  28 03 20 00 00 01
#define   COLOR_IDENTIFICATE      (0)    //  颜色识别传感器  23 03 20 00 00 03
#define   ALCOHOL                 (0)    //  酒精传感器      27 03 20 00 00 01
#define   CO2                     (0)    //  二氧化碳传感器  29 03 20 00 00 01   note
#define   AIR_PRESS               (0)    //  气压传感器      26 03 20 00 00 01
#define   PHOTOSENSITIVE          (0)    //  光敏传感器      24 03 20 00 00 01
#define   SOIL_TEMP               (1)    //  土壤温度传感器  21 03 20 00 00 02   note 

#define   RELAY                   (0)    //  继电器执行器    90 06 22 00 00 01
#define   FAN                     (0)    //  风扇执行器      91 06 22 00 00 01
#define   HIGH_LED                (0)    //  高亮LED         92 06 22 00 00 01   92 10 22 00 00 01 02 00 01
#define   HEAT                    (0)    //  加热模块        93 06 22 00 00 01
#define   SOUND_LIGHT             (0)    //  声光报警        94 10 22 00 00 02 04 00 01 00 01
#define   EM_TAP                  (0)    //  电磁阀          97 06 22 00 00 01

uint8_t GetInput(uint8_t  channel);
void SetOutput(uint8_t channel, uint8_t value);

void SmAdcInit(uint8_t channel);
uint16_t read_ADC(uint8_t channel);

#endif




#ifndef  __SENSOR_H_
#define  __SENSOR_H_

#include"stm32f10x_conf.h"

//��ַ2000
#define  	TEMP_HUMI               (1)    //������ʪ�ȴ�����0x20   2000   20 03 20 00 00 02
#define  	ILLUMINATION            (0)    //����ǿ�ȴ�����  0x2c   2000   2c 03 20 00 00 01
#define   ACCELERATE              (0)    //���ٶȴ�����    0x22   2000   22 03 20 00 00 03
#define   ULTRASONIC              (0)    //������������    0X2a   2000   2a 03 20 00 00 01
//��ַ2100
#define  	FLAME                   (0)    //���洫����      0x60   2100   60 03 21 00 00 01
#define   BODY_INFLAME            (0)    //������⴫����  0x62   2100   62 03 21 00 00 01
#define   HALL                    (0)    //����������      0x61   2100   61 03 21 00 00 01
#define   SHAKE                   (0)    //�𶯴�����      0x65   2100   65 03 21 00 00 01
#define   RAIN                    (0)    //��δ�����      0x66   2100   66 03 21 00 00 01
#define   RED_INFLAME             (0)    //���⿪�ش�����  0x63   2100   63 03 21 00 00 01
#define   TOUCH                   (0)    //����������      0x64   2100   64 03 21 00 00 01
//��ַ2200
#define   STEERING                (0)    //���ִ���� M4   0x98   2200   98 06 22 00 00 00  // 2d 5a 87 b4 �Ƕȷֱ�Ϊ45 90 135 180

uint8_t GetInput(uint8_t  channel);
void SetOutput(uint8_t channel, uint8_t value);

#define       GPIO_CLK	    RCC_APB2Periph_GPIOB
#define       GPIO_PIN      GPIO_Pin_10        
#define       GPIO_PORT	    GPIOB

void DHT11_Init(void);
static void SmDHT11IOIn(void);
static void SmDHT11IOOut(void);
void SmDHT11Reset(void);	
uint8_t SmDHT11Check(void);
uint8_t SmDHT11ReadBit(void);
uint8_t SmDHT11ReadByte(void); 
uint8_t SmDHT11ReadData(void);

#endif




#ifndef _HT66_IIC_H
#define _HT66_IIC_H
#include"main.h"
#include"gpio.h"

#define IIC_SCL_PIN GPIOA,Pin_0
#define IIC_SDA_PIN GPIOA,Pin_1

#define SCL _pb1
#define SDA _pb3

void IIC_Init(void);

void IIC_Start(void);
void IIC_Stop(void);
void IIC_Ack(void);
void IIC_NAck(void);
uint8 IIC_WaitAck(void);

void IIC_SendByte(uint8 dat);
uint8 IIC_ReadByte(void);

#endif
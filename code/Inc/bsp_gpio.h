#ifndef _HT66_BSP_GPIO_H
#define _HT66_BSP_GPIO_H
#include"main.h"
#include"gpio.h"

#define int0 _pa1
#define int1 _pa3
#define int2 _pa4
#define int3 _pc7

#define led1 _pc0
#define led2 _pc1

#define led1_on() led1=0
#define led1_off() led1=1

#define led2_on() led2=0
#define led2_off() led2=1

#define GInit() GPIO_Init()

void GPIO_Init(void);

void __attribute((interrupt(0x04))) INT0_ISR(void);
void __attribute((interrupt(0x08))) INT1_ISR(void);
void __attribute((interrupt(0x30))) INT2_ISR(void);
void __attribute((interrupt(0x34))) INT3_ISR(void);

#endif
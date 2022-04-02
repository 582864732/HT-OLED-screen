#ifndef _HT66_GPIO_H
#define _HT66_GPIO_H
#include"main.h"

#define GPIOA 0X01
#define GPIOB 0X02
#define GPIOC 0X04
#define GPIOD 0X08
#define GPIOE 0x10
#define GPIOF 0X20
#define GPIOG 0x40
#define GPIOH 0X80

#define Pin_0 0x01
#define Pin_1 0x02
#define Pin_2 0x04
#define Pin_3 0x08
#define Pin_4 0x10
#define Pin_5 0x20
#define Pin_6 0x40
#define Pin_7 0x80

//Current Set
#define CURRENT_LEVEL0 0
#define CURRENT_LEVEL1 1
#define CURRENT_LEVEL2 2
#define CURRENT_LEVEL3 3

#define PB47_SetCurrent(i) do{if(i<=3&&i>=0){_sledc0&=~0xC0;_sledc0|=i<<6;}}while(0)
#define PB03_SetCurrent(i) do{if(i<=3&&i>=0){_sledc0&=~0x30;_sledc0|=i<<4;}}while(0)
#define PA47_SetCurrent(i) do{if(i<=3&&i>=0){_sledc0&=~0x0C;_sledc0|=i<<2;}}while(0)
#define PA03_SetCurrent(i) do{if(i<=3&&i>=0){_sledc0&=~0x03;_sledc0|=i;}}while(0)

#define PD46_SetCurrent(i) do{if(i<=3&&i>=0){_sledc1&=~0xC0;_sledc0|=i<<6;}}while(0)
#define PD03_SetCurrent(i) do{if(i<=3&&i>=0){_sledc1&=~0x30;_sledc0|=i<<4;}}while(0)

#define PC47_SetCurrent(i) do{if(i<=3&&i>=0){_sledc1&=~0x0C;_sledc0|=i<<2;}}while(0)
#define PC03_SetCurrent(i) do{if(i<=3&&i>=0){_sledc1&=~0x03;_sledc0|=i;}}while(0)

#define PF47_SetCurrent(i) do{if(i<=3&&i>=0){_sledc2&=~0xC0;_sledc0|=i<<6;}}while(0)
#define PF03_SetCurrent(i) do{if(i<=3&&i>=0){_sledc2&=~0x30;_sledc0|=i<<4;}}while(0)
#define PE4_SetCurrent(i) do{if(i<=3&&i>=0){_sledc2&=~0x0C;_sledc0|=i<<2;}}while(0)
#define PE03_SetCurrent(i) do{if(i<=3&&i>=0){_sledc2&=~0x03;_sledc0|=i;}}while(0)

#define PH45_SetCurrent(i) do{if(i<=3&&i>=0){_sledc3&=~0xC0;_sledc0|=i<<6;}}while(0)
#define PH03_SetCurrent(i) do{if(i<=3&&i>=0){_sledc3&=~0x30;_sledc0|=i<<4;}}while(0)
#define PG47_SetCurrent(i) do{if(i<=3&&i>=0){_sledc3&=~0x0C;_sledc0|=i<<2;}}while(0)
#define PG03_SetCurrent(i) do{if(i<=3&&i>=0){_sledc3&=~0x03;_sledc0|=i;}}while(0)

//PE0-PE3 IO output voltage set
#define OUTPUT_SET_VDD 0
#define OUTPUT_SET_VDDIO 1

#define PE03_SetVoltage(i) do{if(i==0||i==1){_pmps1 = i;}}while(0);
//GPIO set type
#define GPIO_OUTPUT 0
#define GPIO_INPUT 1

void GPIO_SetType(uint8 GPIOx,uint8 GPIO_Pin,uint8 type);

//pull up or no pull up
#define GPIO_PULLUP 1
#define GPIO_NOPULLUP 0

void GPIO_SetPullupState(uint8 GPIOx,uint8 GPIO_Pin,uint8 state);

#endif
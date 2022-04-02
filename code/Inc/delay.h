#ifndef _HT66_DELAY_H
#define _HT66_DELAY_H
#include"main.h"

//#define GCC_DELAY_US() 	GCC_DELAY(i);GCC_DELAY(i);GCC_DELAY(i)
/*
#define GCC_DELAY_4400US() GCC_DELAY(12165)
#define GCC_DELAY_540US() GCC_DELAY(1493)
#define GCC_DELAY_5220us() GCC_DELAY(14432)
#define GCC_DELAY_1620US() GCC_DELAY(4479)
*/
#define GCC_DELAY_1US() GCC_DELAY(3)
#define GCC_DELAY_2US() GCC_DELAY(6)
#define GCC_DELAY_5US() GCC_DELAY(14)

inline void delay_ms(uint16 i);

#endif
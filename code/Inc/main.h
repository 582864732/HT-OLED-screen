#ifndef _HT66_MAIN_H
#define _HT66_MAIN_H
#include"HT66F2390.h"
#include"stdlib.h"
#include"string.h"

#define SYSTICK 11059200

#define ENABLE 1
#define DISABLE 0

#define NULL 0

#define OK 0
#define ERROR 1
#define TIME_OUT 2
#define CONNECT_ERROR 3
#define CONNECT_TIMEOUT 4
#define PASSWORD_ERROR 5
#define AP_NOT_FOUND 6

#define toInt(str) atoi(str)

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

uint8* toString(uint8 num);


#endif
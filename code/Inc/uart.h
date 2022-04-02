#ifndef _HT66_UART_H
#define _HT66_UART_H
#include"main.h"

#define UInit() UART_Init() 
#define USendByte(byte) UART_SendByte(byte)
#define USendString(string,length) UART_SendString(string,length)
#define USendNum(num) UART_SendNum(num)

void UART_Init(void);
void UART_SendByte(uint8 byte);
void UART_SendString(uint8 *string,uint32 length);
void UART_SendNum(uint32 num);

void __attribute((interrupt(0x3c))) UART_Receive(void);
#endif
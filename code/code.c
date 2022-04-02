#include "HT66F2390.h"
#include "uart.h"
#include"gpio.h"
#include"bsp_gpio.h"
#include"iic.h"
#include"GUI.h"
#include"bmp.h"

void SysTickInit(void);



void main()
{
	SysTickInit();

	_emi = 1;
	//GPIO_Init();
	UART_Init();
	IIC_Init();
	oled_init();

	GUI_Init();
	oled_show_bmp(50,0,bmp_WIFI_6X8,0);
	oled_show_bmp(40,1,bmp_NO_WIFI_7X8,1);
	while(1){
	}
}

void SysTickInit(void)
{
	_pbs1 = 0xf0;
	_hxtm = 1;
	_hxten = 1;
	while(_hxtf!=1);
	_fhs = 1;
	_hircen = 0;
	
	//Ω˚”√ø¥√≈π∑
	_wdtc = 0b10101000;
}
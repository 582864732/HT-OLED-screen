#include "HT66F2390.h"
#include "uart.h"
#include"gpio.h"
#include"bsp_gpio.h"
#include"iic.h"
#include"GUI.h"
#include"bmp.h"
#include"AT_CMD.h"
#include"EEPROM.h"

void SysTickInit(void);
void TimInit(void);

uint8 receive_flag = 0;

void main()
{
	SysTickInit();

	_emi = 1;
	
	GPIO_Init();
	UART_Init();
	IIC_Init();
	oled_init();
	GUI_Init();
	ESP_Init();
	TimInit();

	delay_ms(10);
	EEPROM_WriteByte(0,128);
	// led1_on();
	uint8 data = 0;
	data =  EEPROM_ReadByte(0);
	oled_show_string(0,0,toString(data),0);
	// if(ESP_SetMode(AT_STATION_MODE)==OK) led1_on();
	// uint8 i = ESP_ConnectWIFI("WIFI","wifiwifi");
	// oled_show_string(0,0,toString(i),0);
	while(1){
	}
}

void TimInit(void)
{
	/*
	bit 7 PTM??????0???
	bit 6-4 ???
	bit 3 ????????0?off
	*/
	_ptm2c0 = 0b00000000;
	/*
	bit 7-6 ????
	bit 5-4 ?????
	bit 3 PIP?????
	bit 2 PTP??????
	bit 1 PTM?????
	bit 0 PTM??????0????P??
	*/
	_ptm2c1 = 0b11000000;

	//10ms
	uint16 comparator_p = 27648;
	_ptm2rpl = comparator_p&0xFF;
	_ptm2rph = comparator_p>>8;

	//?????P??
	_ptm2pe = 1;
	_ptm2pf = 0;
	_mf2f = 0;
	_mf2e = 1;

	_pt2on = 1;
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

void __attribute((interrupt(0x20))) PTM2_ISR(void)
{
	static uint8 mode = 0;
	if(_ptm2pf==1){
		if(int3==0){
			if(mode==0)mode=1;
		}else{
			if(mode==1){
				KeyEvent(BACK);
				mode=0;
			}
		}
		_ptm2pf = 0;
	}
}
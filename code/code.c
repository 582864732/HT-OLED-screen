#include "HT66F2390.h"
#include "uart.h"
#include"gpio.h"
#include"bsp_gpio.h"
#include"iic.h"
#include"GUI.h"
#include"bmp.h"
#include"AT_CMD.h"
#include"EEPROM.h"
#include"delay.h"


ControllerStruct Controller = {21,0,0,0};

void SysTickInit(void);
void TimInit(void);

extern StationTypeStruct StationType;


uint8 AT_Command = 0;
uint8 AT_Result = 0;

extern uint8 connecting_flag ;
extern uint8 tem[14][3];
extern uint8 windspeed[5][6];  
extern uint8 mode[4][8] ;
extern uint8 rx_data[128];

#define showTem(reverse) oled_show_string(40,0,tem[Controller.temperature-17],reverse)
#define showWind(reverse) oled_show_string(56,1,"   ",0);oled_show_string(40,1,windspeed[Controller.windspeed],reverse)
#define showMode(reverse) oled_show_string(64,2,"   ",0);oled_show_string(40,2,mode[Controller.mode],reverse)

void main()
{
	SysTickInit();

	_emi = 1;
	
	GPIO_Init();
	UART_Init();
	IIC_Init();
	oled_init();
	GUI_Init();
	// ESP_Init();
	TimInit();
	oled_clear();
	// KeyEvent(CLICK);
	// GUI_Show();
	// oled_show_string(0,0,"TEM :",0);
	// oled_show_string(0,1,"WIND:",0);
	// oled_show_string(0,2,"MODE:",0);
	// showTem(0);
	// showWind(0);
	// showMode(0);
	ESP_Test();

	while(1){
		led1_toggle();

		delay_ms(1000);
		// led1_toggle();
		// delay_ms(100);
	}
}

void TimInit(void)
{
	//GPIO读取计时器
	_ptm2c0 = 0b00000000;
	_ptm2c1 = 0b11000000;

	//20ms
	uint16 comparator_p = 55296;
	_ptm2rpl = comparator_p&0xFF;
	_ptm2rph = comparator_p>>8;

	_ptm2pe = 1;
	_ptm2pf = 0;
	_mf2f = 0;
	_mf2e = 1;

	_pt2on = 1;

	//OLED绘制计时器
	_ptm3c0 = 0b00100000;
	_ptm3c1 = 0b11000000;

	//刷新频率约3.3Hz
	comparator_p = 151515;
	_ptm3rpl = comparator_p&0xFF;
	_ptm3rph = comparator_p>>8;

	_ptm3pe = 1;
	_ptm3pf = 0;
	_mf4f = 0;
	_mf4e = 1;

	_pt3on = 0;
}

void SysTickInit(void)
{
	_hirc1 = 0;
	_hirc0 = 0;
	_hircen = 1;
	while(_hircf!=1);

	_pbs1 = 0xf0;
	_hxtm = 1;
	_hxten = 1;
	while(_hxtf!=1);
	_fhs = 1;
	//除能看门狗
	_wdtc = 0b10101000;
}

void __attribute((interrupt(0x20))) PTM2_ISR(void)
{
	static uint8 k3_mode = 0;
	static uint8 k2_mode = 0;
	static uint8 k1_mode = 0;
	static uint8 k0_mode = 0;

	if(_ptm2pf==1){
		if(int3==0){
			if(k3_mode<250)
				k3_mode++;
		}else{
			if(k3_mode>100){
				KeyEvent(LONG_BACK);
			}else if(k3_mode!=0){
				KeyEvent(BACK);
			}
			k3_mode=0;
		}
		if(int2==0){
			if(k2_mode<250)
				k2_mode++;
		}else{
			if(k2_mode>100){
				KeyEvent(LONG_UP);
			}else if(k2_mode!=0){
				KeyEvent(UP);
			}
			k2_mode = 0;
		}
		if(int1==0){
			if(k1_mode<250)
				k1_mode++;
		}else{
			if(k1_mode>100){
				KeyEvent(LONG_CLICK);
			}else if(k1_mode!=0){
				KeyEvent(CLICK);
			}
			k1_mode=0;
		}
		if(int0==0){
			if(k0_mode<250)
				k0_mode++;
		}else{
			if(k0_mode>100){
				KeyEvent(LONG_DOWN);
			}else if(k0_mode!=0){
				KeyEvent(DOWN);
			}
			k0_mode = 0;
		}
		_ptm2pf = 0;
	}
}

void __attribute((interrupt(0x38))) PTM3_ISR(void)
{
	if(_ptm3pf){

		_ptm3pf =  0;
	}
}
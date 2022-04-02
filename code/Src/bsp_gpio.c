#include"bsp_gpio.h"
#include"GUI.h"

void GPIO_Init(void)
{
	_pas0=0;
	//int0 int1
	_pac1 = 1;
	_pac3 = 1;
	_int1e = 1;
	_int1f = 0;
	_int0e = 1;
	_int0f = 0;
	//int2
	_pas1&=0xF0;
	_pac4 = 1;
	_int2e = 1;
	_int2f = 0;
	//int3
	_pcs1 = 0;
	_pcc7 = 1;
	_int3e = 1;
	_int3f = 0;
	
	//设置为上升沿中断
	_integ = 0b01010101;
	
	//led1,2
	_pcc0 = 0;
	_pcc1 = 0;
	
	//_iecc = 0b11001010;
}

void __attribute((interrupt(0x04))) INT0_ISR(void)
{
	if(int0 == 0)
		KeyEvent(DOWN);
	_int0f = 0;
}

void __attribute((interrupt(0x08))) INT1_ISR(void)
{
	if(int1==0)
		KeyEvent(CLICK);
	_int1f = 0;
}

void __attribute((interrupt(0x30))) INT2_ISR(void)
{
	if(int2==0)
		KeyEvent(UP);
	_int2f = 0;	
}

void __attribute((interrupt(0x34))) INT3_ISR(void)
{
	if(int3==0)
		KeyEvent(BACK);
	_int3f = 0;
}

#include"bsp_gpio.h"
#include"GUI.h"

void GPIO_Init(void)
{
	_pac1 = 1;
	_pac3 = 1;
	_pac4 = 1;
	_pcc7 = 1;
	
	//led1,2
	_pcc0 = 0;
	_pcc1 = 0;
	
	//_iecc = 0b11001010;
}



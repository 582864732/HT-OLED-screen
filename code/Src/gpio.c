#include"gpio.h"

void GPIO_SetType(uint8 GPIOx,uint8 GPIO_Pin,uint8 type)
{
	if(GPIOx == GPIOA){
		_pac&=~GPIO_Pin;
		if(type)
			_pac|=GPIO_Pin;
	}else if(GPIOx == GPIOB){
		_pbc&=~GPIO_Pin;
		if(type)
			_pbc|=GPIO_Pin;
	}else if(GPIOx == GPIOC){
		_pcc&=~GPIO_Pin;
		if(type)
			_pcc|=GPIO_Pin;
	}else if(GPIOx == GPIOD){
		_pdc&=~GPIO_Pin;
		if(type)
			_pdc|=GPIO_Pin;
	}else if(GPIOx == GPIOE){
		_pec&=~GPIO_Pin;
		if(type)
			_pec|=GPIO_Pin;
	}else if(GPIOx == GPIOF){
		_pfc&=~GPIO_Pin;
		if(type)
			_pfc|=GPIO_Pin;
	}else if(GPIOx == GPIOG){
		_pgc&=~GPIO_Pin;
		if(type)
			_pgc|=GPIO_Pin;
	}else if(GPIOx == GPIOH){
		_phc&=~GPIO_Pin;
		if(type)
			_phc|=GPIO_Pin;
	}
}

void GPIO_SetPullupState(uint8 GPIOx,uint8 GPIO_Pin,uint8 state)
{
	if(GPIOx == GPIOA){
		_papu&=~GPIO_Pin;
		if(state)
			_papu|=GPIO_Pin;
	}else if(GPIOx == GPIOB){
		_pbpu&=~GPIO_Pin;
		if(state)
			_pbpu|=GPIO_Pin;
	}else if(GPIOx == GPIOC){
		_pcpu&=~GPIO_Pin;
		if(state)
			_pcpu|=GPIO_Pin;
	}else if(GPIOx == GPIOD){
		_pdpu&=~GPIO_Pin;
		if(state)
			_pdpu|=GPIO_Pin;
	}else if(GPIOx == GPIOE){
		_pepu&=~GPIO_Pin;
		if(state)
			_pepu|=GPIO_Pin;
	}else if(GPIOx == GPIOF){
		_pfpu&=~GPIO_Pin;
		if(state)
			_pfpu|=GPIO_Pin;
	}else if(GPIOx == GPIOG){
		_pgpu&=~GPIO_Pin;
		if(state)
			_pgpu|=GPIO_Pin;
	}else if(GPIOx == GPIOH){
		_phpu&=~GPIO_Pin;
		if(state)
			_phpu|=GPIO_Pin;
	}
}
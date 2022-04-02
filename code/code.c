#include "HT66F2390.h"
#include "uart.h"
#include"gpio.h"
#include"bsp_gpio.h"
#include"iic.h"
#include"GUI.h"

void SysTickInit(void);

WindowStructure value_window;
TextStructure num_text;
ButtonStructure set_button;

WindowStructure setting_window;
ButtonStructure m_button;
ButtonStructure add_button;

uint8 value = 0;
uint8 a_text[10] = "a=0"; 

void main()
{
	SysTickInit();

	_emi = 1;
	//GPIO_Init();
	UART_Init();
	IIC_Init();
	oled_init();

	GUI_Init();
	
	
	setCurrentWindow(&value_window);
	
	
	num_text.next_text = NULL;
	num_text.reverse = 0;
	num_text.text = a_text;
	num_text.x = 0;
	num_text.y = 0;
	
	value_window.TextList = &num_text;
	
	
	set_button.text = "set";
	set_button.x = 0;
	set_button.y = 1;
	set_button.next_button = NULL;
	
	value_window.ButtonList = &set_button;
	value_window.CurrentButton = &set_button;
	
	
	m_button.text = "a=a-1";
	m_button.x = 0;
	m_button.y = 0;
	
	
	add_button.text = "a=a+1";
	add_button.x = 0;
	add_button.y = 1;
	m_button.next_button = &add_button;
	add_button.next_button = NULL;
	
	setting_window.ButtonList = &m_button;
	setting_window.CurrentButton = &m_button;
	
	GUI_Show();
	

	
	//WindowCallfunction(&value_window,CLICK);
	while(1){
		delay_ms(1000);
		KeyEvent(CLICK);
		GUI_Show();
		
		delay_ms(1000);
		KeyEvent(DOWN);
		GUI_Show();
		
		delay_ms(1000);
		KeyEvent(CLICK);
		GUI_Show();
	}
}

void WindowCallFunction(WindowStructure *window,uint8 event)
{
	if(window==&value_window){
		switch(event){
			case CLICK:
				if(window->CurrentButton!=NULL){
					ButtonCallFunction(window->CurrentButton);
				}
				break;
		}
	}
	return;
}

void reverse(uint8 *temp,uint8 len)
{
	uint8 i = 0;
	uint8 t;
	uint8 half = len/2;
	for(;i<half;i++){
		t = temp[len-i-1];
		temp[len-i-1] = temp[i];
		temp[i] = t;
	}
}

uint8* setText(uint8 t[10],uint8 v)
{
	uint8 i=0;
	t[0] = 'a';
	t[1] = '=';
	uint8 temp[10];
	do{
		t[i+2] = v%10+'0';
		v/=10;
		i++;
	}while(v!=0);
	reverse(t+2,i);
	t[i+2] = 0;
	return t;
}

void ButtonCallFunction(ButtonStructure *button)
{
	if(button == &set_button){
		setCurrentWindow(&setting_window);
	}else if(button == &m_button){
		value--;
		num_text.text = setText(a_text,value);
		setCurrentWindow(&value_window);
		setting_window.CurrentButton = &m_button;
	}else if(button == &add_button){
		value++;
		num_text.text = setText(a_text,value);
		setCurrentWindow(&value_window);
		setting_window.CurrentButton = &m_button;
	}
	return;	
}



void SysTickInit(void)
{
	_pbs1 = 0xf0;
	_hxtm = 1;
	_hxten = 1;
	while(_hxtf!=1);
	_fhs = 1;
	_hircen = 0;
	
	//½ûÓÃ¿´ÃÅ¹·
	_wdtc = 0b10101000;
}
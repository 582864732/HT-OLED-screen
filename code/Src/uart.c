#include"uart.h"
#include"oled.h"
#include"bsp_gpio.h"

uint8 internet_data[128];
uint8 internet_length = 3;
uint8 internet_cmd;

//ֻʹ��UART0��Ϊ���ڣ����ļĴ����ı�����
void UART_Init(void)
{
	//����PA6,PA7Ϊ����
	_pas1 &= 0x0F;
	_pas1 |= 0xF0;
	
	//����RX0����Դ����ΪPA6
	_rx0ps = 0;
	
	/*
	_u0cr1 ��
	bit 7 UARTʹ��λ
	bit 6 ѡ��������λ�� 0:8λ���� 
	bit 5 ��żУ��ʹ��λ
	bit 4 ��żУ��ѡ��λ 0:żУ��
	bit 3ֹͣλ����ѡ�� 0:һλֹͣλ
	bit 2 ��ͣ�ַ��Ϳ���λ 0:������
	bit 1 RX��9λ
	bit 0 TX��9λ
	
	_u0cr2:
	bit 7 UART����ʹ��λ
	bit 6 ����ʹ��λ
	bit 5 �����ʸߵ���ѡ��λ 0:����
	bit 4 ��ַ����ʹ��λ
	bit 3 RX���½��ػ���UART����ʹ��λ
	bit 2 �����ж�ʹ��
	bit 1 �����������ж�ʹ��
	bit 0 ���ͼĴ���Ϊ��ʹ��λ
	
	�����ʼ��㣺
	���٣�
	f/(64(_brg0+1))
	���٣�
	f/(16(_brg0+1))
	*/
	_u0cr1 = 0b10000000;
	_u0cr2 = 0b11001100;
	
	_brg0 = 17; // 11059200/(64*18) = 9600
	
	//��_u0cr1��
	_uarten0 = 1;
	_txen0 = 1;
	_rxen0 = 1;
	
	//�ж�ʹ�ܣ��������жϱ�־λ
	_mf5e = 1;
	_mf5f = 0;
	_ur0f = 0;
	_ur0e = 1;
	_emi = 1;
}

void UART_SendByte(uint8 byte)
{
	_ur0e = 0;
	while(_txif0 == 0);
	_txr_rxr0 = byte;
	_ur0e = 1;
}

void UART_SendStringL(uint8 *string,uint32 length)
{
	uint8 i=0;
	for(;i<length;i++){
		UART_SendByte(string[i]);
	}
}

void UART_SendString(uint8 *string)
{
	uint8 i=0;
	while(string[i]!=0){
		UART_SendByte(string[i++]);
	}
}

void UART_SendNum(uint32 num)
{
	uint8 ch[10];
	uint8 i=9;
	do{
		//UART_SendByte(num%10+0x30);
		ch[i--] = num%10+0x30;
		num=num/10;
	}while(num!=0);
	UART_SendStringL(ch+i+1,9-i);
}

void UART_SendStrings(uint8 **strs,uint8 length)
{
	uint8 i=0;
	for(;i<length;i++){
		UART_SendString(strs[i]);
	}
}


extern uint8 rx_data[128];
extern uint8 counter;
extern uint8 function_receive_flag;
extern uint8 receive_flag;
extern ControllerStruct Controller;
void processData(void)
{
	if(internet_data[0]>2);
		Controller.temperature = internet_data[0]+15;
	if(internet_data[1]<5)
		Controller.windspeed = internet_data[1]&0x07;
	if(internet_data[2]<4)
		Controller.mode = internet_data[2]&0x03;
}

void __attribute((interrupt(0x3c))) UART_Receive(void)
{
	static uint8 sw_mode = 0;
	static uint8 temp = 0;
	GCC_NOP();
	if(_ur0f==1)
	{
		if(_perr0==1||_oerr0==1||_nf0==1||_ferr0==1)
		{
			asm("lmov a,___txr_rxr0");	//read RXR0 register to clear RXIF0 bit
		}else{
			while(_rxif0==0);
			temp = _txr_rxr0;
			if(function_receive_flag==0){
				switch (sw_mode){
				case 0:
					if(temp==0xAA) {
						sw_mode++;
						counter=0;
						receive_flag = 1;
					}
					break;
				case 1:
					if(temp==0xBB) sw_mode++;
					else {
						sw_mode=0;
						receive_flag = 0;
					}
					break;
				case 2:
					if(temp==0xCC){
						sw_mode++;
					}
					else {
						sw_mode=0;
						receive_flag = 0;
					}
					break;
				case 3:
					internet_data[counter] = temp;
					counter++;
					if(counter==internet_length){
						processData();
						receive_flag=0;
						sw_mode = 0;
						counter=0;
					}
					break;
				default:
					sw_mode=0;
					internet_length=0;
					internet_cmd = 0;
					break;
				}
			}else{
				if(counter==128)
				{
					_ur0f = 0;
					return;
				}
				rx_data[counter] = _txr_rxr0;
				counter++;
			}
		}
		temp = 0;
		_ur0f=0;
	}
}
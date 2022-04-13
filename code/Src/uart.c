#include"uart.h"
#include"oled.h"
#include"bsp_gpio.h"

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
	_u0cr2 = 0b11101100;
	
	_brg0 = 5; // 11059200/(64*18) = 9600
	
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
void __attribute((interrupt(0x3c))) UART_Receive(void)
{
	GCC_NOP();
	if(_ur0f==1)
	{
		if(_perr0==1||_oerr0==1||_nf0==1||_ferr0==1)
		{
			asm("lmov a,___txr_rxr0");	//read RXR0 register to clear RXIF0 bit
		}else
		{
			while(_rxif0==0);
			if(function_receive_flag==0&&counter==0) receive_flag = 1;
			if(counter==128)
			{
				uint8 temp = _txr_rxr0;
				_ur0f = 0;
				return;
			}
			rx_data[counter] = _txr_rxr0;
			counter++;
		}
		_ur0f=0;
	}
}
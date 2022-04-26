#include"uart.h"
#include"oled.h"
#include"bsp_gpio.h"

uint8 internet_data[128];
uint8 internet_length = 3;
uint8 internet_cmd;

//只使用UART0作为串口，更改寄存器改变配置
void UART_Init(void)
{
	//设置PA6,PA7为串口
	_pas1 &= 0x0F;
	_pas1 |= 0xF0;
	
	//设置RX0输入源引脚为PA6
	_rx0ps = 0;
	
	/*
	_u0cr1 ：
	bit 7 UART使能位
	bit 6 选择发送数据位数 0:8位发送 
	bit 5 奇偶校验使能位
	bit 4 奇偶校验选择位 0:偶校验
	bit 3停止位长度选择 0:一位停止位
	bit 2 暂停字发送控制位 0:不发送
	bit 1 RX第9位
	bit 0 TX第9位
	
	_u0cr2:
	bit 7 UART发送使能位
	bit 6 接收使能位
	bit 5 波特率高低速选择位 0:低速
	bit 4 地址检验使能位
	bit 3 RX脚下降沿唤醒UART功能使能位
	bit 2 接收中断使能
	bit 1 发送器空闲中断使能
	bit 0 发送寄存器为空使能位
	
	波特率计算：
	低速：
	f/(64(_brg0+1))
	高速：
	f/(16(_brg0+1))
	*/
	_u0cr1 = 0b10000000;
	_u0cr2 = 0b11001100;
	
	_brg0 = 17; // 11059200/(64*18) = 9600
	
	//在_u0cr1中
	_uarten0 = 1;
	_txen0 = 1;
	_rxen0 = 1;
	
	//中断使能，并置零中断标志位
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
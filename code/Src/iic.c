#include"iic.h"
#include"delay.h"
//软件模拟IIC
void IIC_Init(void)
{
	GPIO_SetPullupState(GPIOB,Pin_1|Pin_3,GPIO_NOPULLUP);
	GPIO_SetType(GPIOB,Pin_3|Pin_1,GPIO_OUTPUT);
	_iecc = 0b11001010;//读端口使能
}

void IIC_Start(void)
{
	SDA = 0;
	GCC_DELAY_1US();
	SCL = 0;
	GCC_DELAY_2US();
}

void IIC_Stop(void)
{
	SCL=1;
	GCC_DELAY_1US();
	SDA=1;
	GCC_DELAY_2US();
}

void IIC_Ack(void)
{
	SCL = 0;
	SDA = 0;
	GCC_DELAY_2US();
	SCL = 1;
	GCC_DELAY_2US();
	SCL=0;
	
}


void IIC_NAck(void)
{
	SCL=0;
	SDA = 1;
	GCC_DELAY_2US();
	SCL = 1;
	GCC_DELAY_2US();
	SCL = 0;
}

uint8 IIC_WaitAck(void)
{
	uint8 temp = 0;
	SDA = 1;
	GCC_DELAY_1US();
	SCL = 1;
	GCC_DELAY_2US();
	while(SDA){
		temp++;
		if(temp>200){
			IIC_Stop();
			return 1;
		}
	}
	SCL = 0;
	return 0;
}

void IIC_SendByte(uint8 dat)
{
	uint8 t;
	for(t=0;t<8;t++)
	{
		SCL=0;
		GCC_DELAY_2US();
		SDA = (dat&0x80)>>7;
		dat=dat<<1;
		GCC_DELAY_2US();
		SCL=1;
		GCC_DELAY_2US();
	}
	SCL=0;
	/*
	SCL = 1;
	SDA = 1;
	GCC_DELAY_2US();
	if(0==SDA) ack=1;
	else ack=0;
	SCL = 0;
	return ack;
	*/
}

uint8 IIC_ReadByte(void)
{
	uint8 i,value;
	value = 0;
	SDA=1;
	for(i=0;i<8;i++){
		SCL=0;
		GCC_DELAY_2US();
		SCL=1;
		value<<=1;
		if(SDA){
			value++;
		}
		GCC_DELAY_2US();
	}
	SCL=0;
	return value;
}
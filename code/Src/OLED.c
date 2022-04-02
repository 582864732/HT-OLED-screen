//
// Created by 58286 on 2022/1/21.
//

#include "OLED.h"
#include "iic.h"
#include "gpio.h"

#include "oled.h"
#include "font.h"

#define OLED_ADD 0x78 //设备地址
/*---------------------------------*/

/*---------------------------------*/
static void oled_cmd(uint8_t i2c_cmd) //发送指令
{
  IIC_Start();
  IIC_SendByte(OLED_ADD);
  IIC_WaitAck();
  IIC_SendByte(0X00);
  IIC_WaitAck();
  IIC_SendByte(i2c_cmd);
  IIC_WaitAck();
  IIC_Stop();
}
static void oled_data(uint8_t data) //发送数据
{
  IIC_Start();
  IIC_SendByte(OLED_ADD);
  IIC_WaitAck();
  IIC_SendByte(0X40);
  IIC_WaitAck();
  IIC_SendByte(data);
  IIC_WaitAck();
  IIC_Stop();
}
static void oled_origin(uint8_t x,uint8_t y) //设置起始点位置
{
  oled_cmd(0xb0+y);
  oled_cmd(((x&0xf0)>>4)|0x10);
  oled_cmd((x&0x0f)|0x01);
}

void oled_full(uint8_t data) //全屏填充
{
  uint8_t i,n;
  for(i=0;i<8;i++)
  {
    oled_cmd(0xb0+i);
    oled_cmd(0x00);
    oled_cmd(0x10);
    for(n=0;n<128;n++)
    {
      oled_data(data);
    }
  }
}
void oled_clear() //清屏
{
  oled_full(0x00);
}

void oled_clear_area(uint8 x,uint8 y,uint8 width,uint8 height)
{
	uint8 i=y,n=x;
	uint8 end_n = x+width;
	uint8 end_i = y+height;
	for(;i<end_i;i++){
		oled_origin(i,n);
		for(;n<end_n;n++){
			oled_data(0x00);
		}
	}
}

void oled_init(void) //初始化
{
  //HAL_Delay(100);

  oled_cmd(0xAE);//--display off
  oled_cmd(0x20);//---set low column address
  oled_cmd(0x10);//---set high column address
  oled_cmd(0xb0);//--set start line address
  oled_cmd(0xc8); // contract control
  oled_cmd(0x00);//--128
  oled_cmd(0x10);//set segment remap
  oled_cmd(0x40);//Com scan direction
  oled_cmd(0x81);//--normal / reverse
  oled_cmd(0xff);//--set multiplex ratio(1 to 64)
  oled_cmd(0xa1);//--1/32 duty
  oled_cmd(0xa6);//-set display offset
  oled_cmd(0xa8);//
  oled_cmd(0x3F);//set osc division
  oled_cmd(0xa4);
  oled_cmd(0xd3);//Set Pre-Charge Period
  oled_cmd(0x00);//
  oled_cmd(0xd5);//set com pin configuartion
  oled_cmd(0xf0);//
  oled_cmd(0xd9);//set Vcomh
  oled_cmd(0x22);//
  oled_cmd(0xda);
  oled_cmd(0x12);
  oled_cmd(0xdb);//set charge pump enable
  oled_cmd(0x20);//
  oled_cmd(0x8d);
  oled_cmd(0x14);
  oled_cmd(0xaf);//--turn on oled panel

  oled_full(0x00);
}
/*
static unsigned char getF8X16(uint16 index)
{
	if(index<564){
		if(index<94) return F8X16_1[index];
		else if(index<188) return F8X16_2[index-94];
		else if(index<282) return F8X16_3[index-188];
		else if(index<376) return F8X16_4[index-282];
		else if(index<470) return F8X16_5[index-376];
		else return F8X16_6[index-470];
	}else{
		if(index<658) return F8X16_7[index-564];
		else if(index<752) return F8X16_8[index-658];
		else if(index<846) return F8X16_9[index-752];
		else if(index<940) return F8X16_10[index-846];
		else if(index<1034) return F8X16_11[index-940];
		else return F8X16_12[index-1034];
	}
}
*/

static unsigned char getF6X8(uint8 c,uint8 i)
{
	if(c<21) return F6x8_1[c][i];
	else if(c<42) return F6x8_2[c-21][i];
	else if(c<63) return F6x8_3[c-42][i];
	else if(c<84) return F6x8_4[c-63][i];
	else return F6x8_5[c-84][i];
}


void oled_show_char(uint8_t x,uint8_t y,uint8_t chr) //单字节
{
	unsigned char c=0,i=0;
	c=chr-' ';//得到偏移后的值
	if(x>128-1){x=0;y=y+2;}
	oled_origin(x,y);
	for(i=0;i<6;i++)
	  //oled_data(F6x8[c][i]);
	  oled_data(getF6X8(c,i));
}


void oled_show_string(uint8_t x, uint8_t y, uint8 ch[],uint8 reverse) //输出字符串
{
  uint8_t c = 0,i = 0,j = 0;
  if(reverse){
	  while(ch[j] != '\0')
	  {
	    c = ch[j] - 32;
	    if(x > 126)
	    {
	      x = 0;
	      y++;
	    }
	    oled_origin(x, y);
	    for(i = 0;i < 6; i++)
	      oled_data(~getF6X8(c,i));
	    x += 6;
	    j++;
	  }
  }else{
	   while(ch[j] != '\0')
	  {
	    c = ch[j] - 32;
	    if(x > 126)
	    {
	      x = 0;
	      y++;
	    }
	    oled_origin(x, y);
	    for(i = 0;i < 6; i++)
	      oled_data(getF6X8(c,i));
	    x += 6;
	    j++;
	  }
  }

}

void oled_show_bmp(uint8_t x, uint8_t y,uint8_t *bmp,uint8 reverse)
{
	if(reverse){
		oled_origin(x,y);
		uint8 i=0;
		while(bmp[i]!=0){
			oled_data(~bmp[i]);
			i++;
		}
	}else{
		oled_origin(x,y);
		uint8 i=0;
		while(bmp[i]!=0){
			oled_data(bmp[i]);
			i++;
		}
	}
}
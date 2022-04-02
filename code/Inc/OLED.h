//
// Created by 58286 on 2022/1/21.
//

#ifndef STM32F401_TEST_CORE_INC_OLED_H_
#define STM32F401_TEST_CORE_INC_OLED_H_
#include "main.h"

#define OLED_ADDR 0x78
#define uint8_t uint8



void oled_full(uint8_t data); //ȫ�����
void oled_init(void); //��ʼ��

void oled_clear_area(uint8 x,uint8 y,uint8 width,uint8 height);
void oled_show_char(uint8_t x,uint8_t y,uint8_t chr);//���ֽ�
void oled_show_string(uint8_t x, uint8_t y, uint8 ch[],uint8 reverse); //����ַ���
void oled_show_chinese(uint8_t x,uint8_t y,uint8_t no); //�������
//void oled_show_bmp(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t bmp[]);//���ͼ��
void oled_clear(); //����

#endif //STM32F401_TEST_CORE_INC_OLED_H_

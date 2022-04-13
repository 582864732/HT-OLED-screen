#ifndef _HT66_EEPROM_H
#define _HT66_EEPROM_H
#include"main.h"

uint8 EEPROM_ReadByte(uint16 adress);
void EEPROM_WriteByte(uint16 adress,uint8 data);
uint8 EEPROM_ReadBytes(uint8 *get_data,uint16 adress,uint8 length);
uint8 EEPROM_WriteBytes(uint16 adress,uint8* data,uint8 length);

#endif
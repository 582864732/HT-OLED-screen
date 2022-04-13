#include"EEPROM.h"
#include"bsp_gpio.h"
#include"OLED.h"

uint8 EEPROM_ReadBytes(uint8 *get_data,uint16 adress,uint8 length)
{
    uint8 i=0;
    for(;i<length;i++){
        get_data[i] = EEPROM_ReadByte(adress);
        adress++;
    }
    return OK;
}

uint8 EEPROM_WriteBytes(uint16 adress,uint8* data,uint8 length)
{
    uint8 i=0;
    for(;i<length;i++){
        EEPROM_WriteByte(adress,data[i]);
        adress++;
    }
    return OK;
}

void EEPROM_WriteByte(uint16 adress,uint8 data)
{
    _eeal = adress&0xFF;
    _eeah = (adress>>8)&0x03;

    _eed = data;
    asm("mov a,04h");
    asm("mov [03h],a");
    asm("mov a,01h");
    asm("mov [04h],a");
    asm("clr [10h].0");
    asm("set [02h].3");//[02h]==iar1
    asm("set [02h].2");
    asm("set [10h].0");//emi
    asm("back1:");
    asm("sz [02h].2");
    asm("jmp back1");
    asm("clr [02h]");
    asm("clr [04h]");
}

uint8 EEPROM_ReadByte(uint16 adress)
{
    _eeal = adress&0xFF;
    _eeah = (adress>>8)&0x03;
    asm("mov a,04h");
    asm("mov [03h],a");
    asm("mov a,01h");
    asm("mov [04h],a");
    asm("set [02h].1");
    asm("set [02h].0");
    asm("back2:");
    asm("sz [02h].0");
    asm("jmp back2");
    asm("clr [02h]");
    asm("clr [04h]");
    return _eed;
}
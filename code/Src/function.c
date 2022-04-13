#include"main.h"

uint8* toString(uint8 num)
{
    static uint8 str[4];
    uint8 i = 2;
    do{
        str[i--] = num%10+'0';
        num/=10;
    }while(num!=0);
    str[3] = 0;
    i+=1;
    return str+i;
}
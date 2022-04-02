#include"delay.h"
#include"tim.h"
/*
//error rate: 7.84%
inline void delay_us(uint16 i)
{
}
*/

//error rate: 0.007%
uint16 delay_time_counter = 0;
inline void delay_ms(uint16 i)
{
	for(;i>0;i--){
		GCC_DELAY(2765);
	}	
}
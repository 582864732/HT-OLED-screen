#ifndef _HT66_TIM_H
#define _HT66_TIM_H
#include"main.h"

//a:16-bit p:8-bit
#define STM0 0
#define STM1 1
#define STM2 2
//10-bit
#define PTM0 3
#define PTM1 4
//16-bit
#define PTM2 5
#define PTM3 6

//
uint8 STM_CounterPause(uint8 STMx);
uint8 STM_CounterRun(uint8 STMx);

uint8 STM_CounterOn(uint8 STMx);
uint8 STM_CounterOff(uint8 STMx);

//
#define STM_SYSCLOCK_DEVIDE_BY_4 0
#define STM_SYSCLOCK_DERECT_INPUT 1
#define STM_HIGHT_SPEED_CLOCK_DEVIDE_BY_16 2
#define STM_HIGHT_SPEED_CLOCK_DEVIDE_BY_64 3
#define STM_LOW_SPEED_CLOCK_DERECT_INPUT 4
#define STM_STCK_RISING_EDGE_CLOCK 6
#define STM_STCK_FALLING_EDGE_CLOCK 7

uint8 STM_SetCounterClock(uint8 STMx,uint8 type);

//
#define STM_COMPARE_OUTPUT_MODE 0
#define STM_CAPTURE_INPUT_MODE 1
#define STM_PWM_OUTPUT_MODE 2
#define STM_COUNTER_MODE 3

uint8 STM_SetMode(uint8 STMx,uint8 mode);

//
#define STM_OUTPUT_UNCHANGED 0
#define STM_OUTPUT_HIGH 2
#define STM_OUTPUT_LOW 1
#define STM_OUTPUT_TOGGLE 3

#define STM_PWM_OUTPUT_INVALID 0
#define STM_PWM_OUTPUT_VALID 1
#define STM_PWM_OUTPUT 2
#define STM_SINGLE_PLUSE 3

#define STM_CAPTURE_RISING_EDGE 0
#define STM_CAPTURE_FALLING_EDGE 1
#define STM_CAPTURE_RISING_AND_FALLING_EDGE 2
#define STM_CAPTURE_DISABLE 3

uint8 STM_SetSTP_Function(uint8 STMx,uint8 function);

//
#define STM_COMPARE_OUTPUT_INITIAL_LOW 0
#define STM_COMPARE_OUTPUT_INITIAL_HIGH 1

#define STM_PWM_LOW_ACTIVE 0
#define STM_PWM_HIGH_ACTIVE 1

uint8 STM_SetSTP_OutputControl(uint8 STMx,uint8 state);

//
#define STM_OUPUT_INPHASE 0
#define STM_OUTPUT_ANTIPHASE 1

uint8 STM_SetOutputPolarity(uint8 STMx,uint8 polarity);

//
#define STM_PERIOD_P_DUTY_A 0
#define STM_PERIOD_A_DUTY_P 1

uint8 STM_SetPeriodDutyControl(uint8 STMx,uint8 type);

//CCLR res
#define STM_COUNTER_CLEAR_MATCH_A 1
#define STM_COUNTER_CLEAR_MATCH_P 0
uint8 STM_SetCounterClearCondition(uint8 STMx,uint8 match);

//
#define STM_CAPTURE_TRIGGER_PTP 0
#define STM_CAPTURE_TRIGGER_PTCK 1

uint8 STM_SetCaptureTriggerSource(uint8 STMx,uint8 source);
//comparator A is a 16-bit res
//comparator P is a 8-bit res
uint8 STM_SetComparatorA(uint8 STMx,uint16 data);
uint8 STM_SetComparatorP(uint8 STMx,uint16 data);
uint8 STM_ReadComparatorA(uint8 STMx,uint16 *data);

typedef struct {
	uint8 STMx;
	uint8 clock_source;
	uint8 mode;
	uint8 STP_function;
	uint8 output_control;
	uint8 output_polarity;
	uint8 PWM_period_duty_control;
	uint8 capture_trigger_source;
	uint8 counter_clear_condition;
	uint16 comparator_p;
	uint16 comparator_a;
	uint8 interrupt_p;
	uint8 interrupt_a
}STM_TypedefStructure;

uint8 STM_TypedefInit(STM_TypedefStructure *init_structure);

#endif
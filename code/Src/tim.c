#include"tim.h"
#include"interrupt.h"

uint8 STM_CounterPause(uint8 STMx)
{
	if(STMx == STM0){
		_st0pau = 1;
	}else if(STMx == STM1){
		_st1pau = 1;
	}else if(STMx == STM2){
		_st2pau = 1;
	}else if(STMx == PTM0){
		_pt0pau = 1;
	}else if(STMx == PTM1){
		_pt1pau = 1;
	}else if(STMx == PTM2){
		_pt2pau = 1;
	}else if(STMx == PTM3){
		_pt3pau = 1;
	}

	return OK;
}

uint8 STM_CounterRun(uint8 STMx)
{
	if(STMx == STM0){
		_st0pau = 0;
	}else if(STMx == STM1){
		_st1pau = 0;
	}else if(STMx == STM2){
		_st2pau = 0;
	}else if(STMx == PTM0){
		_pt0pau = 0;
	}else if(STMx == PTM1){
		_pt1pau = 0;
	}else if(STMx == PTM2){
		_pt2pau = 0;
	}else if(STMx == PTM3){
		_pt3pau = 0;
	}
	return OK;
}

uint8 STM_CounterOn(uint8 STMx)
{
	if(STMx == STM0){
		_st0on = 1;
	}else if(STMx == STM1){
		_st1on = 1;
	}else if(STMx == STM2){
		_st2on = 1;
	}else if(STMx == PTM0){
		_pt0on = 1;
	}else if(STMx == PTM1){
		_pt1on = 1;
	}else if(STMx == PTM2){
		_pt2on = 1;
	}else if(STMx == PTM3){
		_pt3on = 1;
	}

	return OK;
}

uint8 STM_CounterOff(uint8 STMx)
{
	if(STMx == STM0){
		_st0on = 0;
	}else if(STMx == STM1){
		_st1on = 0;
	}else if(STMx == STM2){
		_st2on = 0;
	}else if(STMx == PTM0){
		_pt0on = 0;
	}else if(STMx == PTM1){
		_pt1on = 0;
	}else if(STMx == PTM2){
		_pt2on = 0;
	}else if(STMx == PTM3){
		_pt3on = 0;
	}
	return OK;
}

uint8 STM_SetCounterClock(uint8 STMx,uint8 type)
{
	if(type>7) return;
	if(STMx == STM0){
		_stm0c0&=~0x70;
		_stm0c0|=type<<4;
	}else if(STMx == STM1){
		_stm1c0&=~0x70;
		_stm1c0|=type<<4;
	}else if(STMx == STM2){
		_stm2c0&=~0x70;
		_stm2c0|=type<<4;
	}else if(STMx == PTM0){
		_ptm0c0&=~0x70;
		_ptm0c0|=type<<4;
	}else if(STMx == PTM1){
		_ptm1c0&=~0x70;
		_ptm1c0|=type<<4;
	}else if(STMx == PTM2){
		_ptm2c0&=~0x70;
		_ptm2c0|=type<<4;
	}else if(STMx == PTM3){
		_ptm3c0&=~0x70;
		_ptm3c0|=type<<4;
	}
	return OK;
}

uint8 STM_SetMode(uint8 STMx,uint8 mode)
{
	if(mode>3) return ERROR;
	if(STMx == STM0){
		_stm0c1&=~0xC0;
		_stm0c1|=mode<<6;
	}else if(STMx == STM1){
		_stm1c1&=~0xC0;
		_stm1c1|=mode<<6;
	}else if(STMx == STM2){
		_stm2c1&=~0xC0;
		_stm2c1|=mode<<6;
	}else if(STMx == PTM0){
		_ptm0c1&=~0xC0;
		_ptm0c1|=mode<<6;
	}else if(STMx == PTM1){
		_ptm1c1&=~0xC0;
		_ptm1c1|=mode<<6;
	}else if(STMx == PTM2){
		_ptm2c1&=~0xC0;
		_ptm2c1|=mode<<6;
	}else if(STMx == PTM3){
		_ptm3c1&=~0xC0;
		_ptm3c1|=mode<<6;
	}
	return OK;
}

uint8 STM_SetSTP_Function(uint8 STMx,uint8 function)
{
	if(function>3) return ERROR;
	if(STMx == STM0){
		_stm0c1&=~0x30;
		_stm0c1|=function<<4;
	}else if(STMx == STM1){
		_stm1c1&=~0x30;
		_stm1c1|=function<<4;
	}else if(STMx == STM2){
		_stm2c1&=~0x30;
		_stm2c1|=function<<4;
	}else if(STMx == PTM0){
		_ptm0c1&=~0x30;
		_ptm0c1|=function<<4;
	}else if(STMx == PTM1){
		_ptm1c1&=~0x30;
		_ptm1c1|=function<<4;
	}else if(STMx == PTM2){
		_ptm2c1&=~0x30;
		_ptm2c1|=function<<4;
	}else if(STMx == PTM3){
		_ptm3c1&=~0x30;
		_ptm3c1|=function<<4;
	}
	return OK;
}

uint8 STM_SetSTP_OutputControl(uint8 STMx,uint8 state)
{
	if(state>2) return ERROR;
	if(STMx == STM0){
		_stm0c1&=~0x08;
		_stm0c1|=state<<3;
	}else if(STMx == STM1){
		_stm1c1&=~0x08;
		_stm1c1|=state<<3;
	}else if(STMx == STM2){
		_stm2c1&=~0x08;
		_stm2c1|=state<<3;
	}else if(STMx == PTM0){
		_ptm0c1&=~0x08;
		_ptm0c1|=state<<3;
	}else if(STMx == PTM1){
		_ptm1c1&=~0x08;
		_ptm1c1|=state<<3;
	}else if(STMx == PTM2){
		_ptm2c1&=~0x08;
		_ptm2c1|=state<<3;
	}else if(STMx == PTM3){
		_ptm3c1&=~0x08;
		_ptm3c1|=state<<3;
	}
	return OK;
}

uint8 STM_SetOutputPolarity(uint8 STMx,uint8 polarity)
{
	if(polarity>2) return ERROR;
	if(STMx == STM0){
		_st0pol = polarity;
	}else if(STMx == STM1){
		_st1pol = polarity;
	}else if(STMx == STM2){
		_st2pol = polarity;
	}else if(STMx == PTM0){
		_pt0pol = polarity;
	}else if(STMx == PTM1){
		_pt1pol = polarity;
	}else if(STMx == PTM2){
		_pt2pol = polarity;
	}else if(STMx == PTM3){
		_pt3pol = polarity;
	}
	return OK;
}

uint8 STM_SetComparatorA(uint8 STMx,uint16 data)
{
	if(STMx == STM0){
		_stm0al = data&0xFF;
		_stm0ah = data>>8;
	}else if(STMx == STM1){
		_stm1al = data&0xFF;
		_stm1ah = data>>8;
	}else if(STMx == STM2){
		_stm2al = data&0xFF;
		_stm2ah = data>>8;
	}else if(STMx == PTM0){
		if(data>1023) return ERROR;
		_ptm0al = data&0x03;
		_ptm0ah = data>>2;
	}else if(STMx == PTM1){
		if(data>1023) return ERROR;
		_ptm1al = data&0x03;
		_ptm1ah = data>>2;
	}else if(STMx == PTM2){
		_ptm2al = data&0xFF;
		_ptm2ah = data>>8;
	}else if(STMx == PTM3){
		_ptm3al = data&0xFF;
		_ptm3ah = data>>8;
	}
	return OK;
}

//if data=0,comparator set to 65536, otherwise set to 256*data
uint8 STM_SetComparatorP(uint8 STMx,uint16 data)
{
	if(STMx == STM0){
		if(data > 0xFF)return ERROR;
		_stm0rp = data;
	}else if(STMx == STM1){
		if(data > 0xFF)return ERROR;
		_stm1rp = data;
	}else if(STMx == STM2){
		if(data > 0xFF)return ERROR;
		_stm2rp = data;
	}else if(STMx == PTM0){
		if(data>1023) return ERROR;
		_ptm0rpl = data&0x03;
		_ptm0rph = data>>2;
	}else if(STMx == PTM1){
		if(data>1023) return ERROR;
		_ptm1rpl = data&0x03;
		_ptm1rph = data>>2;
	}else if(STMx == PTM2){
		_ptm2rpl = data&0xFF;
		_ptm2rph = data>>8;
	}else if(STMx == PTM3){
		_ptm3rpl = data&0xFF;
		_ptm3rph = data>>8;
	}
	return OK;
}

uint8 STM_SetCounterClearCondition(uint8 STMx,uint8 match)
{
	if(match>2)return ERROR;
	if(STMx == STM0){
		_st0cclr = match;
	}else if(STMx == STM1){
		_st1cclr = match;
	}else if(STMx == STM2){
		_st2cclr = match;
	}else if(STMx == PTM0){
		_pt0cclr = match;
	}else if(STMx == PTM1){
		_pt1cclr = match;
	}else if(STMx == PTM2){
		_pt2cclr = match;
	}else if(STMx == PTM3){
		_pt3cclr = match;
	}
	return OK;
}

uint8 STM_SetPeriodDutyControl(uint8 STMx,uint8 type)
{
	if(type>2)return ERROR;
	if(STMx == STM0){
		_st0dpx = type;
	}else if(STMx == STM1){
		_st1dpx = type;
	}else if(STMx == STM2){
		_st2dpx = type;
	}else return ERROR;
	return OK;
}

uint8 STM_SetCaptureTriggerSource(uint8 STMx,uint8 source)
{
	if(source>2)return ERROR;
	if(STMx == PTM0){
		_pt0capts = source;
	}else if(STMx == PTM1){
		_pt1capts = source;
	}else if(STMx == PTM2){
		_pt2capts = source;
	}else if(STMx == PTM3){
		_pt3capts = source;
	}else return ERROR;
	return OK;
}

uint8 STM_TypedefInit(STM_TypedefStructure *init_structure)
{
	uint8 STMx = init_structure->STMx;
	if(STM_SetCounterClock(STMx,init_structure->clock_source) != OK) return ERROR;
	if(STM_SetMode(STMx,init_structure->mode) != OK)return ERROR;
	if(STM_SetCounterClearCondition(STMx,init_structure->counter_clear_condition) != OK)return ERROR;
	if(STM_SetComparatorA(STMx,init_structure->comparator_a) != OK)return ERROR;
	if(STM_SetComparatorP(STMx,init_structure->comparator_p) != OK)return ERROR;
	if(init_structure->interrupt_a||init_structure->interrupt_p){
		MASTER_INTERRUPT_ENABLE();
		if(STMx == STM0 || STMx == PTM0){
			M_FUNCT0_ENABLE();
			M_FUNCT0_CLEAR_FLAG();
			if(STMx == STM0){
				if(init_structure->interrupt_a){
					STM0_COMPARATOR_A_ENABLE();
					STM0_COMPARATOR_A_CLEAR_FLAG();
				}
				if(init_structure->interrupt_p){
					STM0_COMPARATOR_P_ENABLE();
					STM0_COMPARATOR_P_CLEAR_FLAG();
				}
			}

		}else if(STMx == PTM2){
			M_FUNCT2_ENABLE();
			M_FUNCT2_CLEAR_FLAG();
			if(init_structure->interrupt_a){
				PTM2_COMPARATOR_A_ENABLE();
				PTM2_COMPARATOR_A_CLEAR_FLAG();
			}
			if(init_structure->interrupt_p){
				PTM2_COMPARATOR_P_ENABLE();
				PTM2_COMPARATOR_P_CLEAR_FLAG();
			}
		}
	}
	if(init_structure->mode == STM_COUNTER_MODE) return OK;
	if(STM_SetSTP_Function(STMx,init_structure->STP_function) != OK)return ERROR;
	if(init_structure->mode == STM_PWM_OUTPUT_MODE || init_structure->mode == STM_COMPARE_OUTPUT_MODE){
		if(STM_SetSTP_OutputControl(STMx,init_structure->output_control) != OK)return ERROR;
	}
	if(STM_SetOutputPolarity(STMx,init_structure->output_polarity) !=OK)return ERROR;
	if(init_structure->mode == STM_PWM_OUTPUT_MODE && STMx < PTM0){
		if(STM_SetPeriodDutyControl(STMx,init_structure->PWM_period_duty_control) != OK)return ERROR;
	}
	if(init_structure->mode == STM_CAPTURE_INPUT_MODE && STMx >STM2){
		if(STM_SetCaptureTriggerSource(STMx,init_structure->capture_trigger_source) != OK)return ERROR;
	}
	
	return OK;
}

uint8 STM_ReadComparatorA(uint8 STMx,uint16 *data)
{
	*data = 0;
	if(STMx == STM0){
		*data |= _stm0ah<<8;
		*data |= _stm0al;
	}else if(STMx == STM1){
		*data |= _stm1ah<<8;
		*data |= _stm1al;
	}else if(STMx == STM2){
		*data |= _stm2ah<<8;
		*data |= _stm2al;
	}else if(STMx == PTM0){
		*data |= _ptm0ah<<8;
		*data |= _ptm0al;
	}else if(STMx == PTM1){
		*data |= _ptm1ah<<8;
		*data |= _ptm1al;
	}else if(STMx == PTM2){
		*data |= _ptm2ah<<8;
		*data |= _ptm2al;
	}else if(STMx == PTM3){
		*data |= _ptm3ah<<8;
		*data |= _ptm3al;
	}
	return OK;
}
	
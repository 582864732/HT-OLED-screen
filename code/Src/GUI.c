#include"GUI.h"
#include"bsp_gpio.h"
#include"GUI_logic.h"

WindowStructure *CurrentWindow;
ChangeListStruct ChangeList;


void resetChangeList(void)
{
	ChangeList.num = 0;
	ChangeList.clear = 0;
}

void GUI_Clear(void)
{
	if(ChangeList.clear){
		oled_clear();
	}else{
		uint8 i=0;
		for(;i<ChangeList.num;i++){
			oled_clear_line(ChangeList.x[i],ChangeList.y[i],ChangeList.length[i]);
		}
	}
	resetChangeList();
}

void addLabel(LabelStructure *label)
{
	if(CurrentWindow->TextList==NULL) CurrentWindow->TextList = label;
	else{
		LabelStructure *temp = CurrentWindow->TextList;
		while(temp->next_text!=NULL){
			temp = temp->next_text;	
		}
		temp->next_text = label;
	}
}
extern uint8 controllerWindowState;
void GUI_Show(void)
{
	GUI_Clear();
	// oled_show_string(0,7,toString(controllerWindowState),0);
	LabelStructure *text_temp = CurrentWindow->TextList;
	while(text_temp!=NULL){
		oled_show_string(text_temp->x,text_temp->y,text_temp->text,text_temp->reverse);
		text_temp=text_temp->next_text;
	}
	CurrentWindow->TextList = NULL;

	ButtonStructure *button_temp = CurrentWindow->ButtonList;
	if(CurrentWindow->CurrentButton == NULL)
		CurrentWindow->CurrentButton = CurrentWindow->ButtonList;
	while(button_temp!=NULL){
		if(button_temp == CurrentWindow->CurrentButton){
			oled_show_string(button_temp->x,button_temp->y,button_temp->text,1);
		}else oled_show_string(button_temp->x,button_temp->y,button_temp->text,0);
		button_temp=button_temp->next_button;
	}
	CurrentWindow->ButtonList = NULL;

	CustomizedLayerStructure *cl_temp = CurrentWindow->CL_List;
	while(cl_temp!=NULL){
		CustomizedLayerCallFunction(cl_temp);
		cl_temp = cl_temp->next_customzied_layer;
	}
	CurrentWindow->CL_List = NULL;
	// led1_toggle();
}

void setCurrentWindow(WindowStructure *window)
{
	CurrentWindow = window;
}

void setChangeListClear(void)
{
	ChangeList.clear = 1;
}

void addChangeListDef(uint8 x,uint8 y,uint8 length)
{
	ChangeList.x[ChangeList.num] = x;
	ChangeList.y[ChangeList.num] = y;
	ChangeList.length[ChangeList.num] = length;
	ChangeList.num++;
}


void KeyEvent(uint8 event)
{
	switch(event){
		case UP:
			if(CurrentWindow->ButtonList){
				ButtonStructure *temp = CurrentWindow->ButtonList;
				if(temp->next_button==NULL) break;
				while(temp->next_button!=CurrentWindow->CurrentButton ){
					temp = temp->next_button;
				}
				addChangeListS(temp);
				addChangeListS(temp->next_button);
				CurrentWindow->CurrentButton = temp;
			}else WindowCallback(event);
			break;
		case DOWN:
			if(CurrentWindow->ButtonList==NULL){
				WindowCallback(event);
				break;
			}
			if(CurrentWindow->CurrentButton->next_button!=NULL){
				addChangeListS(CurrentWindow->CurrentButton);
				addChangeListS(CurrentWindow->CurrentButton->next_button);
				CurrentWindow->CurrentButton = CurrentWindow->CurrentButton->next_button;
			}else if(CurrentWindow->CurrentButton != CurrentWindow->ButtonList){
				addChangeListS(CurrentWindow->CurrentButton);
				addChangeListS(CurrentWindow->ButtonList);
				CurrentWindow->CurrentButton = CurrentWindow->ButtonList;
			}else break;
			break;
		case CLICK:
			if(CurrentWindow->CurrentButton!=NULL){
				ButtonCallFunction(CurrentWindow->CurrentButton);
			}else {
				WindowCallback(event);
				// static uint8 a =0;
				// if(a==1){
				// 	oled_show_string(0,0,"c",0);
				// 	a=0;
				// }else if(a==0){
				// 	oled_show_string(0,0,"a",0);
				// 	a=1;
				// }
				// addChangeList(0,0,1);
			}
			break;
		case BACK:
			WindowCallback(event);
			break;
		default:break;
	}
	// led2_toggle();
}

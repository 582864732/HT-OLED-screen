#include"GUI.h"

WindowStructure *CurrentWindow;

inline void GUI_Init(void)
{
	CurrentWindow->TextList = NULL;
	CurrentWindow->ButtonList = NULL;
	CurrentWindow->CL_List = NULL;
	CurrentWindow->CurrentButton = NULL;
}

void GUI_Show(void)
{
	static uint8 min_x,min_y,max_x,max_y;
	oled_clear_area(0,0,40,2);
	//oled_full(0);
	TextStructure *text_temp = CurrentWindow->TextList;
	while(text_temp!=NULL){
		if(text_temp->y<min_y) min_y = text_temp->y;
		oled_show_string(text_temp->x,text_temp->y,text_temp->text,text_temp->reverse);
		text_temp=text_temp->next_text;
	}
	ButtonStructure *button_temp = CurrentWindow->ButtonList;
	if(CurrentWindow->CurrentButton == NULL) 
		CurrentWindow->CurrentButton = CurrentWindow->ButtonList;
	while(button_temp!=NULL){
		if(button_temp == CurrentWindow->CurrentButton){
			oled_show_string(button_temp->x,button_temp->y,button_temp->text,1);
		}else oled_show_string(button_temp->x,button_temp->y,button_temp->text,0);
		button_temp=button_temp->next_button;
	}
	CustomizedLayerStructure *cl_temp = CurrentWindow->CL_List;
	while(cl_temp!=NULL){
		CustomizedLayerCallFunction(cl_temp);
		cl_temp = cl_temp->next_customzied_layer;
	}
}

void setCurrentWindow(WindowStructure *window)
{
	CurrentWindow = window;
}



void KeyEvent(uint8 event)
{
	switch(event){
		case UP:
			if(CurrentWindow->ButtonList){
				ButtonStructure *temp = CurrentWindow->ButtonList;
				while(temp->next_button!=CurrentWindow->CurrentButton){
					temp = temp->next_button;
				}
				CurrentWindow->CurrentButton = temp;
			}
			break;
		case DOWN:
			if(CurrentWindow->CurrentButton->next_button!=NULL)
				CurrentWindow->CurrentButton = CurrentWindow->CurrentButton->next_button;
			else CurrentWindow->CurrentButton = CurrentWindow->ButtonList;
			break;
		case CLICK:
			if(CurrentWindow->CurrentButton!=NULL){
				ButtonCallFunction(CurrentWindow->CurrentButton);
				break;
			}
		case BACK:
			WindowCallFunction(CurrentWindow,event);
			break;
		default:break;
	}
}



void CustomizedLayerCallFunction(CustomizedLayerStructure *cl)
{
	return;
}
#ifndef _HT66_GUI_H
#define _HT66_GUI_H
#include"OLED.h"

#define UP 0
#define DOWN 1
#define CLICK 2
#define BACK 3
#define LONG_UP 4
#define LONG_DOWN 5
#define LONG_CLICK 6
#define LONG_BACK 7

#define CHANGELIST_LENGTH 10
//以OLED显示的逻辑，分辨率为128x8

typedef struct LabelStructure{
	uint8 x;
	uint8 y;
	uint8* text;
	uint8 reverse;
 	struct LabelStructure *next_text;
}LabelStructure;


typedef struct ButtonStructure{
	uint8 x;
	uint8 y;
	uint8* text;
	struct ButtonStructure *next_button;
}ButtonStructure;

typedef struct CustomizedLayerStructure{
	uint8 x;
	uint8 y;
	uint8 width;
	uint8 height;
	struct CustomizedLayerStructure *next_customzied_layer;
}CustomizedLayerStructure;

typedef struct WindowStructure{
	LabelStructure *TextList;
	ButtonStructure *ButtonList;
	CustomizedLayerStructure *CL_List;
	ButtonStructure *CurrentButton;
}WindowStructure;

typedef struct ChangeListStruct{
	uint8 x[CHANGELIST_LENGTH];
	uint8 y[CHANGELIST_LENGTH];
	uint8 length[CHANGELIST_LENGTH];
	uint8 num;
	uint8 clear;
}ChangeListStruct;

inline void GUI_Init(void);
void GUI_Show(void);
void GUI_Clear(void);

void setChangeListClear(void);
void resetChangeList(void);
// inline void addChangeList(uint8 x,uint8 y,uint8 length);
void addChangeListDef(uint8 x,uint8 y,uint8 length);
void setCurrentWindow(WindowStructure *window);

void addLabel(LabelStructure *label);

#define addChangeList(x0,y0,length0) 	ChangeList.x[ChangeList.num] = x0;\
										ChangeList.y[ChangeList.num] = y0;\
										ChangeList.length[ChangeList.num] = length0;\
										ChangeList.num++;


#define addChangeListS(controls) addChangeListDef(((controls)->x),((controls)->y),(strlen((controls)->text)))


void KeyEvent(uint8 event);


#endif
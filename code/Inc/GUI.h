#ifndef _HT66_GUI_H
#define _HT66_GUI_H
#include"OLED.h"

#define UP 0
#define DOWN 1
#define CLICK 2
#define BACK 3

//以OLED显示的逻辑，分辨率为128x8

typedef struct LabelStructure{
	uint8* text;
	uint8 reverse;
	uint8 x;
	uint8 y;
 	struct LabelStructure *next_text;
}LabelStructure;

typedef struct ButtonStructure{
	uint8* text;
	uint8 x;
	uint8 y;
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

inline void GUI_Init(void);
void GUI_Show(void);

void setCurrentWindow(WindowStructure *window);

void WindowCallfunction(WindowStructure *window, uint8 event);
void ButtonCallFunction(ButtonStructure *button);
void CustomizedLayerCallFunction(CustomizedLayerStructure *cl);
void KeyEvent(uint8 event);


#endif
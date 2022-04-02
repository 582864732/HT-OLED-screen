#ifndef _HT66_GUI_H
#define _HT66_GUI_H
#include"OLED.h"

#define UP 0
#define DOWN 1
#define CLICK 2
#define BACK 3

typedef struct TextStructure{
	uint8* text;
	uint8 reverse;
	uint8 x;
	uint8 y;
 	struct TextStructure *next_text;
}TextStructure;

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
	TextStructure *TextList;
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
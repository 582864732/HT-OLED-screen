#ifndef _HT66_GUI_LOGIC_H
#define _HT66_GUI_LOGIC_H
#include"GUI.h"


void WindowCallback(uint8 event);
void ButtonCallFunction(ButtonStructure *button);
void CustomizedLayerCallFunction(CustomizedLayerStructure *cl);

void mainSettingFormInit(void);
void WIFI_SettingFormInit(void);

#endif
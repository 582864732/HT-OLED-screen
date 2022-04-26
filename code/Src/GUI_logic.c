#include"GUI.h"
#include"GUI_Logic.h"
#include"AT_CMD.h"
#include"bsp_gpio.h"
#include"delay.h"
#include"uart.h"

extern ESP_StateStruct ESP_State;
extern uint8 AT_Command;
extern WindowStructure *CurrentWindow;
extern ChangeListStruct ChangeList;

WindowStructure textwin;

//controller form
WindowStructure ControllerWindow;

//main form
WindowStructure MainSettingWindow;

ButtonStructure WIFI_Setting_Button;

//WIFI form
WindowStructure WIFI_SettingWindow;

LabelStructure WIFI_Label;

ButtonStructure WorkAsAP_OrStationButton;
ButtonStructure ConnectOrDisconnectButton;

extern ControllerStruct Controller;
uint8 tem[14][3] = {"17","18","19","20","21","22","23","24","25","26","27","28","29","30"};
uint8 windspeed[5][6] = {"fixed","high","mid","low","auto"};
uint8 mode[4][8] = {"cryogen","dehum","auto","heating"};

#define setPTM3P(value) _ptm3rpl = value&0xFF;_ptm3rph=(value>>8);

uint8 connecting_flag = 0;

//controller form
WindowStructure ControllerWindow;

LabelStructure temperatureLabel;
LabelStructure windspeedLabel;
LabelStructure modeLabel;
LabelStructure label1;
LabelStructure label2;
LabelStructure label3;

#define showTem(reverse) oled_show_string(40,0,tem[Controller.temperature-17],reverse)
#define showWind(reverse) oled_show_string(56,1,"   ",0);oled_show_string(40,1,windspeed[Controller.windspeed],reverse)
#define showMode(reverse) oled_show_string(64,2,"   ",0);oled_show_string(40,2,mode[Controller.mode],reverse)

void textwindInit(void)
{
    textwin.ButtonList = NULL;
    textwin.CL_List = NULL;
    textwin.CurrentButton = NULL;
    textwin.TextList = NULL;
}

uint8 controllerWindowState = 0;
void controllerFormInit(void)
{
    label1.x = 0;
    label1.y = 0;
    label1.text = "TEM:";
    label1.reverse = 0;
    label1.next_text = &label2;

    label2.x = 0;
    label2.y = 1;
    label2.text = "WIND:";
    label2.reverse = 0;
    label2.next_text = &label3;

    label3.x = 0;
    label3.y = 2;
    label3.text = "MODE:";
    label3.reverse = 0;
    label3.next_text = &temperatureLabel;

    Controller.temperature = 21;
    Controller.mode = 0;
    Controller.windspeed = 1;


    temperatureLabel.x = 40;
    temperatureLabel.y = 0;
    temperatureLabel.text = tem[Controller.temperature-17];
    temperatureLabel.reverse = 0;
    temperatureLabel.next_text = &windspeedLabel;

    windspeedLabel.x = 40;
    windspeedLabel.y = 1;
    windspeedLabel.text = windspeed[Controller.windspeed];
    windspeedLabel.reverse = 0;
    windspeedLabel.next_text = &modeLabel;

    modeLabel.x = 40;
    modeLabel.y = 2;
    modeLabel.text = mode[Controller.mode];
    modeLabel.reverse = 0;
    modeLabel.next_text = NULL;

    ControllerWindow.TextList = &label1;
    ControllerWindow.ButtonList = NULL;
    ControllerWindow.CL_List = NULL;
    ControllerWindow.CurrentButton = NULL;
}

void mainSettingFormInit(void)
{
    WIFI_Setting_Button.x = 0;
    WIFI_Setting_Button.y = 0;
    WIFI_Setting_Button.text = "WIFI Setting";
    WIFI_Setting_Button.next_button = NULL;

    MainSettingWindow.ButtonList = &WIFI_Setting_Button;
    MainSettingWindow.CL_List = NULL;
    MainSettingWindow.CurrentButton = &WIFI_Setting_Button;
    MainSettingWindow.TextList = NULL;
}

void WIFI_SettingButtonCallback(void){
    CurrentWindow = &WIFI_SettingWindow;
    WIFI_SettingWindow.CurrentButton = &WorkAsAP_OrStationButton;
    addChangeListS(&WIFI_Setting_Button);
}

void WIFI_SettingFormInit(void)
{
    WIFI_Label.x = 0;
    WIFI_Label.y = 0;
    WIFI_Label.text = "Station";
    WIFI_Label.reverse = 0;
    WIFI_Label.next_text = NULL;

    WorkAsAP_OrStationButton.x = 0;
    WorkAsAP_OrStationButton.y = 1;
    WorkAsAP_OrStationButton.text = "Work As AP";   
    WorkAsAP_OrStationButton.next_button = &ConnectOrDisconnectButton;

    ConnectOrDisconnectButton.x = 0;
    ConnectOrDisconnectButton.y = 2;
    ConnectOrDisconnectButton.text = "Connect to WIFI";
    ConnectOrDisconnectButton.next_button = NULL;

    WIFI_SettingWindow.ButtonList = &WorkAsAP_OrStationButton;
    WIFI_SettingWindow.CL_List = NULL;
    WIFI_SettingWindow.CurrentButton = &WorkAsAP_OrStationButton;
    WIFI_SettingWindow.TextList = &WIFI_Label;
}

void  WorkAsAP_OrStationButtonCallback(void)
{
    // CurrentWindow = &WIFI_SettingWindow;
    // led2_on();
    if(ESP_State.current_mode == AT_STATION_MODE){
        WorkAsAP_OrStationButton.text="Work As Station";
        WIFI_Label.text = "Station";
        ESP_State.current_mode = AT_SOFTAP_MODE;
        
    }else if(ESP_State.current_mode == AT_SOFTAP_MODE){
        WorkAsAP_OrStationButton.text="Work As AP";
        ESP_State.current_mode = AT_STATION_MODE;
        WIFI_Label.text = "AP";
    }
    addChangeListS(&WorkAsAP_OrStationButton);
    addChangeListS(&WIFI_Label);
}

void ConnectOrDisconnectButtonCallback(void)
{
    if(ESP_State.is_wifi_connected==0){
        addChangeListS(&ConnectOrDisconnectButton);
        addChangeListS(&WIFI_Label);
        addChangeListS(&WorkAsAP_OrStationButton);
        GUI_Clear();
        oled_show_string(24,4,"connecting",0);
        connecting_flag = 1;
        setPTM3P(357142);
        _pt3on = 1;
        uint8 state = ESP_ConnectWIFI();
        _pt3on = 0;
        oled_clear_line(0,4,16);
        if(state==OK) oled_show_string(0,4,"connected",0);
        else oled_show_string(0,4,"connect error",0);
        delay_ms(2000);
        oled_clear_line(0,4,16);
        connecting_flag = 0;
    }else{
        addChangeListS(&ConnectOrDisconnectButton);
        ConnectOrDisconnectButton.text = "Connect WIFI";
    }
}

void ButtonCallFunction(ButtonStructure *button)
{
	if(CurrentWindow==&MainSettingWindow){
        if(button == &WIFI_Setting_Button );
            WIFI_SettingButtonCallback();
    }else if(CurrentWindow==&WIFI_SettingWindow){
        if(button == &WorkAsAP_OrStationButton)
            WorkAsAP_OrStationButtonCallback();
        else if(button == &ConnectOrDisconnectButton)
            ConnectOrDisconnectButtonCallback();
    }
}

void packData(uint8 *data){
	data[0] = Controller.temperature-15;
	data[1] = Controller.windspeed&0x07;
	data[2] = Controller.mode&0x03;
}

uint8 data[3];

void WindowCallback(uint8 event)
{
	if(CurrentWindow == &WIFI_SettingWindow){
        if(event==BACK){
            CurrentWindow = &MainSettingWindow;
        }
    }else if(CurrentWindow == &ControllerWindow){
        if(event==CLICK){
            if(controllerWindowState==0){
                controllerWindowState++;
                oled_show_string(40,0,tem[Controller.temperature-17],1);
            }else{
                switch(controllerWindowState){
                    case 1:
                        showWind(1);
                        showTem(0);
                        // oled_show_string(40,0,)
                        // temperatureLabel.reverse = 0;
                        // windspeedLabel.reverse = 1;
                        // addLabel(&temperatureLabel);
                        // addLabel(&windspeedLabel);
                        // addChangeList(temperatureLabel.x,temperatureLabel.y,strlen(temperatureLabel.text));
                        // addChangeList(windspeedLabel.x,windspeedLabel.y,strlen(windspeedLabel.text));
                        break;
                    case 2:
                        showMode(1);
                        showWind(0);
                        // windspeedLabel.reverse = 0;
                        // modeLabel.reverse = 1;
                        // addLabel(&modeLabel);
                        // addLabel(&windspeedLabel);
                        // addChangeList(windspeedLabel.x,windspeedLabel.y,strlen(windspeedLabel.text));
                        // addChangeList(modeLabel.x,modeLabel.y,strlen(modeLabel.text));
                        break;
                    case 3:
                        showTem(1);
                        showMode(0);
                        // modeLabel.reverse = 0;
                        // temperatureLabel.reverse = 1;
                        // addLabel(&temperatureLabel);
                        // addLabel(&modeLabel);
                        // addChangeList(modeLabel.x,modeLabel.y,strlen(modeLabel.text));
                        // addChangeList(temperatureLabel.x,temperatureLabel.y,strlen(temperatureLabel.text));
                        break;
                    default:
                        break;
                }
                controllerWindowState++;
                if(controllerWindowState==4) controllerWindowState = 1;
            }
        }else if(event==BACK){
            if(controllerWindowState){
                LabelStructure *temp;
                switch(controllerWindowState){
                    case 1:
                        showTem(0);
                        break;
                    case 2:
                        showWind(0);
                        break;
                    case 3:
                        showMode(0);
                        break;
                    default:
                        break;
                }
                // packData(data);
                // ESP_Send(data,3);
                controllerWindowState = 0;
                UART_SendString("AT+CIPSEND=6\r\n");
                AT_ReceiveOnce(100);
                UART_SendByte(0xAA);
                UART_SendByte(0xBB);
                UART_SendByte(0xCC);
                UART_SendByte(Controller.temperature-15);
                UART_SendByte(Controller.windspeed);
                UART_SendByte(Controller.mode);
                AT_ReceiveOnce(100);
            }
        }else if(event==UP){
            if(controllerWindowState==1){
                // led2_toggle();
                Controller.temperature++;
                if(Controller.temperature>30)
                    Controller.temperature = 30;
                else
                    showTem(1);
            }else if(controllerWindowState==2){
                Controller.windspeed++;
                if(Controller.windspeed==5){
                    Controller.windspeed = 0;
                }
                showWind(1);
                
            }else if(controllerWindowState==3){
                Controller.mode++;
                if(Controller.mode==4){
                    Controller.mode = 0;
                }
                showMode(1);
            }
        }else if(event == DOWN){
            if(controllerWindowState==1){
                if(Controller.temperature>17){
                    Controller.temperature--;
                    showTem(1);
                    // temperatureLabel.text = toString(Controller.temperature);
                    // addLabel(&temperatureLabel);
                    // addChangeList(temperatureLabel.x,temperatureLabel.y,strlen(temperatureLabel.text));
                }
            }else if(controllerWindowState==2){
                // if(Controller.windspeed!=0){
                //     Controller.windspeed--;
                //     // windspeedLabel.text = windspeed[Controller.windspeed];
                //     // addLabel(&windspeed);
                //     // addChangeList(windspeedLabel.x,windspeedLabel.y,strlen(windspeedLabel.text));
                // }
                if(Controller.windspeed==0){
                    Controller.windspeed=4;
                }else Controller.mode--;
                showWind(1);
            }else if(controllerWindowState==3){
                // if(Controller.mode!=0){
                //     Controller.mode--;
                //     modeLabel.text = mode[Controller.mode];
                //     addLabel(&modeLabel);
                //     addChangeList(modeLabel.x,modeLabel.y,strlen(modeLabel.text));
                // }
                if(Controller.mode==0){
                    Controller.mode=3;
                }else Controller.mode--;
                showMode(1);
            }
        }
    }else if(CurrentWindow == &textwin){
        if(event == CLICK){
            // oled_show_string(0,0,"click",0);
            // led2_toggle();
        }
    }
}

void CustomizedLayerCallFunction(CustomizedLayerStructure *cl)
{
	
}

inline void GUI_Init(void)
{
	CurrentWindow->TextList = NULL;
	CurrentWindow->ButtonList = NULL;
	CurrentWindow->CL_List = NULL;
	CurrentWindow->CurrentButton = NULL;

    // setCurrentWindow(&textwin);
	setCurrentWindow(&ControllerWindow);
	mainSettingFormInit();
	WIFI_SettingFormInit();
    controllerFormInit();
    textwindInit();
    // connectingFormInit();
}
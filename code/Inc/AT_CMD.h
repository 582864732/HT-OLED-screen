#ifndef _HT66_AT_CMD_H
#define _HT66_AT_CMD_H
#include"main.h"

#define AT_STATION_MODE 1
#define AT_SOFTAP_MODE 2
#define AT_SOFTAP_STATION_MODE 3

#define AT_CONNECT_WIFI 0
#define AT_DISCONNECT_WIFI 1

typedef struct StationType
{
    /* data */
    uint8 ssid[32];
    uint8 password[32];
    uint8 ip[12];
}StationTypeStruct;

typedef struct ESP_State
{
    /* data */
    uint8 current_mode;
    uint8 is_wifi_connected;
}ESP_StateStruct;

typedef struct ESP_Client
{
    uint8 connect_port;
    uint8 connect_ip[16];
}ESP_ClientStruct;

typedef struct ControllerStruct
{
    uint8 temperature;
    uint8 windspeed;
    uint8 mode;
}ControllerStructure;


uint8 ESP_SetMode(uint8 mode);

void ESP_Init(void);
uint8 ESP_ConnectWIFI();
uint8 ESP_Disconnect(void);
uint8 ESP_SetupServer(void);
uint8 ESP_ConnectServer(void);
uint8 ESP_Compare(uint8* str,uint8 *offset);
uint8 AT_Receive(uint16 wait);
uint8 AT_ReceiveOnce(uint16 wait);
uint8 ESP_Send(uint8*data,uint8 length);
void ESP_Test(void);

void __attribute((interrupt(0x20))) PTM2_ISR(void);

#endif
#ifndef _HT66_AT_CMD_H
#define _HT66_AT_CMD_H
#include"main.h"

#define AT_STATION_MODE 1
#define AT_SOFTAP_MODE 2
#define AT_SOFTAP_STATION_MODE 3

// struct{
//     uint8 work_mode;
//     uint8 server_port[5];
//     uint8 staion_ip[16];
//     uint8 AP_ip[16];
//     uint8 wifi_ssid[50];
//     uint8 wifi_password[50];
//     uint8 AP_ssid[50];
//     uint8 AP_password[50];
// }AT_State;

uint8 ESP_SetMode(uint8 mode);

void ESP_Init(void);
uint8 ESP_ConnectWIFI(uint8 *ssid,uint8 *password);
uint8 ESP_Disconnect(void);
uint8 ESP_SetupServer(void);

uint8 AT_Receive(uint16 wait);
uint8 AT_ReceiveOnce(uint16 wait);

void __attribute((interrupt(0x20))) PTM2_ISR(void);

#endif
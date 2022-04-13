#include"AT_CMD.h"
#include"uart.h"
#include"bsp_gpio.h"
#include"oled.h"
#include"delay.h"
#include"string.h"

#define AT_SEND(string) UART_SendString(string)
#define AT_END() UART_SendString("\r\n")

uint8 rx_data[128];
uint8 counter = 0;
uint8 function_receive_flag = 0;

#define rx_dataCompare(str,offset) (strncmp(rx_data+offset,str,strlen(str))==0)
#define GotoNext(i) while(rx_data[i]==0x0D||rx_data[i]==0x0A) i++;
// extern uint8 rx_data;
// extern uint8 counter;
void ESP_Init(void)
{
	// strcpy(AT_State.wifi_ssid,"WIFI");
	// strcpy(AT_State.wifi_password,"wifiwifi");
	// AT_State.server_port = 333;
	// AT_State.work_mode = AT_STATION_MODE;

	AT_SEND("ATE0");
	AT_END();
	delay_ms(10);
	AT_SEND("AT+CWMODE_CUR=1");
	AT_END();
	delay_ms(10);
	AT_SEND("AT_RESET");
	AT_END();
	delay_ms(100);
}

uint8 ESP_Disconnect(void)
{
	AT_SEND("AT+CWQAP");
	AT_END();
	delay_ms(10);
	return OK;
}

uint8 ESP_SetMode(uint8 mode)
{
	switch(mode){
		case AT_STATION_MODE:AT_SEND("AT+CWMODE=1");break;
		case AT_SOFTAP_MODE:AT_SEND("AT+CWMODE=2");break;
		case AT_SOFTAP_STATION_MODE:AT_SEND("AT+CWMODE=3");break;
		default:break;
	}
	AT_END();
	AT_ReceiveOnce(10);
	uint8 i=0;
	GotoNext(i);
	if(rx_dataCompare("OK",i)) return OK;
	else return ERROR;
}

uint8 ESP_SetupServer(void)
{
	AT_SEND("CWMODE=2");
	AT_END();
	AT_SEND("AT+CIPMUX=1");
	AT_END();
	AT_SEND("AT+CIPSERVER=1,333");
	AT_END();
}

uint8 ESP_ConnectWIFI(uint8 *ssid,uint8 *password)
{
	ESP_Disconnect();
	uint8 str[50] = "AT+CWJAP_CUR=\"";
	strcat(str,ssid);
	strcat(str,"\",\"");
	strcat(str,password);
	strcat(str,"\"");
	AT_SEND(str);
	AT_END();
	if(AT_ReceiveOnce(10)==OK){
		oled_show_string(0,0,rx_data,0);
		return ERROR;
	}
	if(AT_Receive(10000)==TIME_OUT) return TIME_OUT;
	uint8 i=0;
	GotoNext(i);
	if(strncmp(&rx_data[i],"WIFI CONNECTED",14)==0) return OK;
	else return CONNECT_ERROR;
}

uint8 AT_ReceiveOnce(uint16 wait)
{
	function_receive_flag = 1;
	counter = 0;
	//RX_ISR_ENABLE();
	uint16 temp = 0;
	while (counter==0){
		temp++;
		if(temp==wait) {
			rx_data[0] = 0;
			return TIME_OUT;
		}
		delay_ms(1);
	}
	delay_ms(100);
	// delay_ms(wait);
	// RX_ISR_DISABLE();
	if(counter==0) rx_data[0] = 0;
	else rx_data[--counter] = 0;
	counter = 0;
	function_receive_flag = 0;
	return OK;
}

uint8 AT_Receive(uint16 wait)
{
	function_receive_flag = 1;
	counter = 0;
	delay_ms(wait);
	if(counter==0) rx_data[0] = 0;
	else rx_data[--counter] = 0;
	counter = 0;
	function_receive_flag = 0;
	return OK;
}

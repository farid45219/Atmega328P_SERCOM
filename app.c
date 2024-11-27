

#include <avr/io.h>
#include "timebase.h"
#include "sercom.h"
#include "uart.h"
#include "app.h"




void App_Setup(void){
  
  
  UART_Init(57600);
  UART_Tx_Text_NL("SERCOM Started");
  
  
}


void App_Main_Loop(void){
  
  if(SERCOM_Cmd_Frame_Get()){
    SERCOM_Extract_Data();
	SERCOM_Cmd_Ack_Output();
	SERCOM_Execute_Operation();
	SERCOM_Final_Output();
  }
  
  
}


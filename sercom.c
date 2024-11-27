

#include <avr/io.h>
#include "sercom.h"
#include "uart.h"

enum{
  WRITE_OP = 0,
  READ_OP  = 1
};

typedef struct sercom_t{
  uint8_t   Packet[20];
  uint8_t   ReqOperation;
  uint8_t   RegAddr;
  uint8_t   Data;
  uint8_t   Error;
}sercom_t;

sercom_t SERCOM;


void SERCOM_Flush_Packet(void){
  for(uint8_t i = 0; i < 20; i++){
    SERCOM.Packet[i] = 0;
  }
}

uint8_t SERCOM_Char_To_Hex(uint8_t val){
  uint8_t hex_val = 0;
  if( (val >= 48) && (val <= 57) ){
    hex_val = val-48;
  }
  else if( (val >= 65) && (val <= 70) ){
    hex_val = val-55;
  }
  else if( (val >= 97) && (val <= 102) ){
    hex_val = val-87;
  }
  else{
    hex_val = 0;
	SERCOM.Error |= 0x10;
  }
  return hex_val;
}
  
uint8_t SERCOM_Cmd_Frame_Get(void){
  uint8_t len = 0;
  if(UART_Data_Available()){
    UART_Data_Copy_Buf(SERCOM.Packet);
	len = UART_Data_Len_Get();
	UART_RX_Packet_Read_Complete();
  }
  return len;
}


void SERCOM_Extract_Data(void){
  SERCOM.Error = 0;
  if((SERCOM.Packet[0] == 'W') || (SERCOM.Packet[0] == 'w')){
    SERCOM.ReqOperation = WRITE_OP;
  }
  else if((SERCOM.Packet[0] == 'R') || (SERCOM.Packet[0] == 'r')){
    SERCOM.ReqOperation = READ_OP;
  }
  else{
    SERCOM.Error |= 0x01;
  }
  
  if( (SERCOM.Error == 0x00) && (SERCOM.Packet[1] != ',') ){
    SERCOM.Error |= 0x02;
  }
  
  if(SERCOM.Error == 0x00){
    SERCOM.RegAddr   = SERCOM_Char_To_Hex(SERCOM.Packet[2]);
	SERCOM.RegAddr <<= 4;
	SERCOM.RegAddr  |= SERCOM_Char_To_Hex(SERCOM.Packet[3]);
  }
  
  if( (SERCOM.Error == 0x00) && (SERCOM.Packet[4] != ',') ){
    SERCOM.Error |= 0x03;
  }
  
  if(SERCOM.Error == 0x00){
    SERCOM.Data   = SERCOM_Char_To_Hex(SERCOM.Packet[5]);
	SERCOM.Data <<= 4;
	SERCOM.Data  |= SERCOM_Char_To_Hex(SERCOM.Packet[6]);
  }
}

void SERCOM_Cmd_Ack_Output(void){
  if(SERCOM.Error == 0x00){
    if(SERCOM.ReqOperation == WRITE_OP){
	  UART_Tx_Parameter_Hex_SP("Write", SERCOM.RegAddr);
	  UART_Tx_Parameter_Hex_NL(" -> ", SERCOM.Data);
	}
	else if(SERCOM.ReqOperation == READ_OP){
	  SERCOM.Data = SERCOM_Read_Reg(SERCOM.RegAddr);
	  UART_Tx_Parameter_Hex_SP("Read", SERCOM.RegAddr);
	  UART_Tx_Parameter_Hex_NL(" <- ", SERCOM.Data);
	}
  }
}


void SERCOM_Write_Reg(uint8_t addr, uint8_t data){
  (*(volatile uint8_t*)(addr)) = data;
}

uint8_t SERCOM_Read_Reg(uint8_t addr){
  return (*(volatile uint8_t*)(addr));
}


void SERCOM_Execute_Operation(void){
  if(SERCOM.Error == 0x00){
    if(SERCOM.ReqOperation == WRITE_OP){
      SERCOM_Write_Reg(SERCOM.RegAddr, SERCOM.Data);
	  if(SERCOM_Read_Reg(SERCOM.RegAddr) != SERCOM.Data){
	    SERCOM.Error |= 0x20;
	  }
	}
	else if(SERCOM.ReqOperation == READ_OP){
	  SERCOM.Data = SERCOM_Read_Reg(SERCOM.RegAddr);
	}
  }
}
  
void SERCOM_Final_Output(void){
  if(SERCOM.Error == 0x00){
    UART_Tx_Text_NL("Operation Successful");
	UART_Tx_NL();
  }
  else{
    UART_Tx_Parameter_Hex_NL("Operation Failed with Error Code", SERCOM.Error);
	UART_Tx_NL();
  }
}
  
  
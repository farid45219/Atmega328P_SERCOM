/* 
 * File:   uart.h
 * Author: MD. Faridul Islam
 * Atmega328P UART Library
 * Created on October 30, 2022, 19:00
 */



#define  UART_DOUBLE_SPEED
#define  UART_ENABLE_TX    
#define  UART_ENABLE_RX    
#define  UART_ENABLE_RX_INT

#define  UART_BUFFER_SIZE            64U
#define  UART_RX_PCKT_CMPLT_DELAY    50U



//#define  UART_CRC_ENABLE     //Uncomment if packet validation by CRC is needed
//#define  UART_CRC_CVTE     //Uncomment if CRC is by CVTE Protocol
#define  UART_CRC_XMODEM     //Uncomment if CRC is by X-MODEM Protocol



void     UART_Struct_Init(void);
void     UART_RX_Packet_Struct_Init(void);

void     UART_Config_GPIO(void);
void     UART_Config_Clock(void);
void     UART_Config_BAUD_Rate(uint32_t baud_rate);
void     UART_Config_Tx(void);
void     UART_Config_Rx(void);
void     UART_Config_Rx_Interrupt(void);
void     UART_Tx_Byte(uint8_t val);
uint8_t  UART_Rx_Byte(void);


void     UART_Timer_Struct_Init(void);
void     UART_Timer_Init(void);
void     UART_Timer_Enable(void);
void     UART_Timer_Disable(void);
uint8_t  UART_Timer_Get_Status(void);
uint16_t UART_Timer_Get_Val(void);
void     UART_Timer_Value_Reset(void);


void     UART_Tx_Buf(uint8_t *data, uint8_t len);


void     UART_Tx_NL(void);
void     UART_Tx_SP(void);
void     UART_Tx_CM(void);


void     UART_Tx_Text(char *str);
void     UART_Tx_Text_NL(char *str);
void     UART_Tx_Text_SP(char *str);
void     UART_Tx_Text_CM(char *str);


void     UART_Determine_Digit_Numbers(uint32_t num);
void     UART_Tx_Number_Digits(void);
void     UART_Tx_Number(int32_t num);
void     UART_Tx_Number_Hex(uint32_t val);
void     UART_Tx_Number_Bin(uint32_t val);


void     UART_Tx_Number_NL(int32_t num);
void     UART_Tx_Number_SP(int32_t num);
void     UART_Tx_Number_CM(int32_t num);


void     UART_Tx_Number_Hex_NL(int32_t num);
void     UART_Tx_Number_Hex_SP(int32_t num);
void     UART_Tx_Number_Hex_CM(int32_t num);


void     UART_Tx_Number_Bin_NL(int32_t num);
void     UART_Tx_Number_Bin_SP(int32_t num);
void     UART_Tx_Number_Bin_CM(int32_t num);


void     UART_Tx_Parameter_NL(char *name, int32_t num);
void     UART_Tx_Parameter_SP(char *name, int32_t num);
void     UART_Tx_Parameter_CM(char *name, int32_t num);


void     UART_Tx_Parameter_Hex_NL(char *name, int32_t num);
void     UART_Tx_Parameter_Hex_SP(char *name, int32_t num);
void     UART_Tx_Parameter_Hex_CM(char *name, int32_t num);


void     UART_Tx_Parameter_Bin_NL(char *name, int32_t num);
void     UART_Tx_Parameter_Bin_SP(char *name, int32_t num);
void     UART_Tx_Parameter_Bin_CM(char *name, int32_t num);

//Receiver Functions
void     UART_Buf_Flush(void);
uint8_t  UART_Buf_Get(uint16_t index);
uint8_t  UART_Buf_Get_Index(void);


//UART Data Functions
uint8_t  UART_Data_Available(void);
uint8_t  UART_Data_Len_Get(void);

uint16_t UART_Data_Calculated_CRC_Get(void);
uint16_t UART_Data_Received_CRC_Get(void);
uint8_t  UART_Data_CRC_Status_Get(void);
uint8_t  UART_Data_Read_Complete_Status(void);

void     UART_Data_Clear_Available_Flag(void);
void     UART_Data_Clear_Read_Complete_Flag(void);

void     UART_Data_Copy_Buf(uint8_t *buf);
void     UART_Data_Print_Buf(void);

uint8_t  UART_Error_Code_Get(void);
void     UART_Error_Code_Clear(void);

void     UART_ISR_Handler(void);
void     UART_Timer_ISR_Handler(void);


uint16_t UART_CRC_Calculate_Byte(uint16_t crc, uint8_t data);
uint16_t UART_CRC_Calculate_Block(uint8_t *buf, uint8_t len);

void     UART_RX_Packet_CRC_Check(void);
void     UART_RX_Packet_Read_Complete(void);

void     UART_Init(uint32_t baud);



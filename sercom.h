

void    SERCOM_Flush_Packet(void);
uint8_t SERCOM_Char_To_Hex(uint8_t val);
uint8_t SERCOM_Cmd_Frame_Get(void);
void    SERCOM_Extract_Data(void);
void    SERCOM_Cmd_Ack_Output(void);
void    SERCOM_Write_Reg(uint8_t addr, uint8_t data);
uint8_t SERCOM_Read_Reg(uint8_t addr);
void    SERCOM_Execute_Operation(void);
void    SERCOM_Final_Output(void);


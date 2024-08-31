#ifndef __MYI2C_H
#define __MYI2C_H

void MyI2C_Init(void);
void My_I2C_Start(void);
void My_I2C_Stop(void);
void My_I2C_SendByte(uint8_t Byte);
uint8_t My_I2C_ReceiveByte(void);
void My_I2C_SendAck(uint8_t AckBit);
uint8_t My_I2C_ReceiveAck(void);

#endif

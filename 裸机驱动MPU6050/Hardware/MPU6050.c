#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU6050_Reg.h"				//附加的寄存器地址

#define MPU6050_ADDRESS 0xD0

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)							//写入指定位置
{
	My_I2C_Start();
	My_I2C_SendByte(MPU6050_ADDRESS);
	My_I2C_ReceiveAck();
	My_I2C_SendByte(RegAddress);
	My_I2C_ReceiveAck();
	My_I2C_SendByte(Data);
	My_I2C_ReceiveAck();
	My_I2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)										//读取指定位置
{
	uint8_t Data;

	My_I2C_Start();
	My_I2C_SendByte(MPU6050_ADDRESS);
	My_I2C_ReceiveAck();
	My_I2C_SendByte(RegAddress);
	My_I2C_ReceiveAck();

	My_I2C_Start();
	My_I2C_SendByte(MPU6050_ADDRESS | 0x01);
	My_I2C_ReceiveAck();
	Data = My_I2C_ReceiveByte();
	My_I2C_SendAck(1);
	My_I2C_Stop();
	return Data;
}

void MPU6050_Init(void)															//MPU6050初始化
{
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);		//或者0x00
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);		//角加速度，选择了最大量程，2000
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);	//加速度，选择了最大量程，16g
}

void MPU6050_GetData(int16_t *Accx,int16_t *Accy,int16_t *Accz,				
					int16_t *Gyrox,int16_t *Gyroy,int16_t *Gyroz)				//数据读取
{
	uint16_t DataH,DataL;
	//接下来是六个数据的读取，每个数据分两部分，高八位和低八位，组成16位的最终数据

	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*Accx = (DataH<<8) | DataL;

	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*Accy = (DataH<<8) | DataL;

	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*Accz = (DataH<<8) | DataL;

	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*Gyrox = (DataH<<8) | DataL;

	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*Gyroy = (DataH<<8) | DataL;

	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*Gyroz = (DataH<<8) | DataL;
}

uint8_t MPU6050_GetID(void)														//获取芯片ID
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

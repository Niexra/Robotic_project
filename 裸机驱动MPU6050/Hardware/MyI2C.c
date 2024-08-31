#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void MyI2C_W_SCL(uint8_t BitValue)		//控制SCL线
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitValue)		//控制SDA线
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}
uint8_t MyI2C_R_SDA(void)				//读取SDA线
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}
void MyI2C_Init(void)					//初始化部分
{
 //开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		//必须是推挽输出，不然
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;  //没有硬性要求
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//置高电平
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);
}
void My_I2C_Start(void)					//起始条件
{
	//先后顺序不能换
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);

	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}
void My_I2C_Stop(void)					//终止条件
{
	MyI2C_W_SDA(0);

	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}
void My_I2C_SendByte(uint8_t Byte)		//发送字节
{
	uint8_t i;

	for(i = 0;i < 8;i++)
	{
     //>>是向右移位，例如1000>>1 = 0100
		MyI2C_W_SDA(Byte & (0x80 >> i));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}
uint8_t My_I2C_ReceiveByte(void)		//接收字节
{
	uint8_t Byte = 0x00;
	uint8_t i = 0;
	MyI2C_W_SDA(1);
	for(i = 0;i < 8;i++)
	{
		MyI2C_W_SCL(1);
		if(MyI2C_R_SDA() == 1)
		{
         //|=是与等，先与后等，为了获取接收到的1
			Byte |= (0x80 >> i);
		}
		MyI2C_W_SCL(0);
	}
	return Byte;
}
void My_I2C_SendAck(uint8_t AckBit)		//应答
{

		MyI2C_W_SDA(AckBit);
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
}
uint8_t My_I2C_ReceiveAck(void)			//接收应答
{
	uint8_t AckByte;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckByte = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckByte;
}

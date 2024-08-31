#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "Servo.h"

float Pitch,Roll,Yaw;								//俯仰角默认跟中值一样，翻滚角，偏航角
int16_t ax,ay,az,gx,gy,gz;							//加速度，陀螺仪角速度

u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);

int main(void)
{
	OLED_Init();
	Servo_Init();
	MPU6050_Init();
	MPU6050_DMP_Init();
	
	OLED_ShowString(1,1,"2023090908004");
	
	while (1)
	{
		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);				//读取姿态信息(其中偏航角有飘移是正常现象)
		MPU_Get_Gyroscope(&gx,&gy,&gz);
		MPU_Get_Accelerometer(&ax,&ay,&az);


		//前面获取的加速度这里就不显示了，主要显示的是角度
		OLED_ShowString(2,1,"Pitch:");
		OLED_ShowString(3,1,"Roll:");
		OLED_ShowString(4,1,"Yaw:");
		OLED_ShowSignedNum(2, 8, Pitch, 5);
		OLED_ShowSignedNum(3, 8, Roll, 5);
		OLED_ShowSignedNum(4, 8, Yaw, 5);
		
		if(Yaw <= 90 && Yaw >= -90)
		{
			Servo_SetAngle(Yaw);
		}
		else if(Yaw < -90)
		{
			Servo_SetAngle(Yaw + 180);
		}
		else
		{
			Servo_SetAngle(Yaw - 180);
		}
		
	}
}

#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "Servo.h"

float Pitch,Roll,Yaw;								//������Ĭ�ϸ���ֵһ���������ǣ�ƫ����
int16_t ax,ay,az,gx,gy,gz;							//���ٶȣ������ǽ��ٶ�

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
		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);				//��ȡ��̬��Ϣ(����ƫ������Ʈ������������)
		MPU_Get_Gyroscope(&gx,&gy,&gz);
		MPU_Get_Accelerometer(&ax,&ay,&az);


		//ǰ���ȡ�ļ��ٶ�����Ͳ���ʾ�ˣ���Ҫ��ʾ���ǽǶ�
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

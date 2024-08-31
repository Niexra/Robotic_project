#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"

float Angle = 0;

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Servo_Init();			//PWM初始化
	
	OLED_ShowString(1,1,"Angle:");
	
	Servo_SetAngle(90);
	
	while (1)
	{
		while(Angle < 90)
		{
			Servo_SetAngle(Angle);
			if((int)Angle%10 == 0)
			{
				OLED_ShowNum(1,7,Angle,3);
			}

			Angle += 1;
			Delay_ms(10);
		}
		while(Angle > 0)
		{
			Servo_SetAngle(Angle);
			if((int)Angle%10 == 0)
			{
				OLED_ShowNum(1,7,Angle,3);
			}
			Angle -= 1;
			Delay_ms(10);
		}
	}
}


#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Timer.h" 
#include "Motor.h"

extern float DistanceValue[5];   //超声波测距结果

int main(void)
{		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 //串口初始化为115200
	
	TIM5_Cap_Init(0xffff,72-1);  //捕获定时器初始化
	Ultrasonic_Trigger_TIM3_Init(25000-1,720-1);//超声波触发定时器初始化
	Ultrasonic_EchoPin_Init();  //超声波，触发引脚初始化
	
	Motor_CtrlPin_Init();  //电机控制端口初始化
	while(1)
	{
//		Ultrasonic_Echo_Trigger(Ultrasonic_1);
//		delay_ms(2);
//		Ultrasonic_Echo_Trigger(Ultrasonic_2);
//		delay_ms(2);
//		Ultrasonic_Echo_Trigger(Ultrasonic_3);
//		delay_ms(2);
//		Ultrasonic_Echo_Trigger(Ultrasonic_4);
//		delay_ms(2);
		printf("Distance:%.2f  ,%.2f  ,%.2f  ,%.2f  \r\n",DistanceValue[1],DistanceValue[2],DistanceValue[3],DistanceValue[4]);
		delay_ms(500);
	}	 
} 


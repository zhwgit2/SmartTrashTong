#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Timer.h" 
#include "Motor.h"

extern float DistanceValue[5];   //�����������

int main(void)
{		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	
	TIM5_Cap_Init(0xffff,72-1);  //����ʱ����ʼ��
	Ultrasonic_Trigger_TIM3_Init(25000-1,720-1);//������������ʱ����ʼ��
	Ultrasonic_EchoPin_Init();  //���������������ų�ʼ��
	
	Motor_CtrlPin_Init();  //������ƶ˿ڳ�ʼ��
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


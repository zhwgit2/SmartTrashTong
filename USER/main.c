#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Timer.h" 
#include "Motor.h"
#include "Display.h"

extern float DistanceValue[5];   //�����������
extern u8 ScanInfoBuf[5];
extern u8 ScanFinishFlag;

int main(void)
{		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	Display_Uart3_init(115200);
	Scan_Uart2_Init(9600);
	
	
	TIM4_Cap_Init(0xffff,72-1);  //����ʱ����ʼ��
	Ultrasonic_Trigger_TIM3_Init(25000-1,720-1);//������������ʱ����ʼ��
	Ultrasonic_EchoPin_Init();  //���������������ų�ʼ��
	printf("Info:%d ,%d ,%d ,%d\r\n",ScanInfoBuf[0],ScanInfoBuf[1],ScanInfoBuf[2],ScanInfoBuf[3]);
	Motor_CtrlPin_Init();  //������ƶ˿ڳ�ʼ��
	while(1)
	{
		if(ScanFinishFlag)
		{
			//Send_To_Display_Comd(ScanInfoBuf,sizeof(ScanInfoBuf));
			printf("Info:%d ,%d ,%d ,%d\r\n",ScanInfoBuf[0],ScanInfoBuf[1],ScanInfoBuf[2],ScanInfoBuf[3]);
			Display_Scan_Info(ScanInfoBuf[0],ScanInfoBuf[1],ScanInfoBuf[2],ScanInfoBuf[3]);
			ScanFinishFlag=0;
		}
		//printf("Distance:%.2f  ,%.2f  ,%.2f  ,%.2f  \r\n",DistanceValue[1],DistanceValue[2],DistanceValue[3],DistanceValue[4]);
		//delay_ms(500);
	}	 
} 


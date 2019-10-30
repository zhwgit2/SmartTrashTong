#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Timer.h" 
#include "Motor.h"
#include "Display.h"

extern u8 ScanInfoBuf[5];
extern u8 ScanFinishFlag;

u8 ClassInfoBuff[6][10]={0};  //�༶��Ϣ���飬����60��ѧ�࣬Ĭ�������꼶��ÿ���꼶ʮ����ѧ��

/**************�����߼�*****************
��̬ʱ����ʾ����ʾ����༶��Ϣ������
���˵���ʱ���������������ȴ�ɨ��ǹ����
ɨ��ɹ����Զ��򿪶�Ӧ����Ͱ���ӣ�����ʾ��ǰѡ������Ͱ����ͣ��Ӧ����Ͱ�������
�ȴ����ߺ��Զ��ر�����Ͱ��������������ʾ����Ͱ�������������ݵ���Ļ��
�ȴ���һ������
***************************************/

u8 TrashCount = 0;
u8 TrashType = 0;
int main(void)
{		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	Display_Uart3_init(115200);   //��ʾ�����ڳ�ʼ��
	Scan_Uart2_Init(9600);        //ɨ��ǹ���ڳ�ʼ��
	
	
	TIM4_Cap_Init(0xffff,72-1);  //����ʱ����ʼ��
	Ultrasonic_Trigger_TIM3_Init(25000-1,720-1);//������������ʱ����ʼ��
	Ultrasonic_EchoPin_Init();  //���������������ų�ʼ��
	Motor_CtrlPin_Init();  //������ƶ˿ڳ�ʼ��
	Voice_CtrlPin_Init();  //����ģ��˿ڳ�ʼ��
	People_Test_Init();    //������ģ��˿ڳ�ʼ��
	
	while(1) 
	{
		if(StatusCtrl == 1)  //�����Ӧģ�鴥��״̬ 1
		{
			Voice_Play_Task(00001);  //������������--��ɨ��
			StatusCtrl = 100;   //״̬��ת������̬���ȴ��ɹ�ɨ��
		}else if(StatusCtrl == 2)
		{
			switch(TrashType)
			{
				case 1:Motor_Ctrl_Task(Motor_1,Open);;break;
				case 2:Motor_Ctrl_Task(Motor_2,Open);;break;
				case 3:Motor_Ctrl_Task(Motor_3,Open);;break;
				case 4:Motor_Ctrl_Task(Motor_4,Open);;break;
			}
			delay_ms(500);         //�����ת��������Ͱ����
			Motor_Stop_Task();     //�����ѿ����ȴ�������
			StatusCtrl = 3;   //״̬��ת��״̬3
			delay_ms(1000);
		}else if(StatusCtrl == 3)
		{
			delay_ms(1000);
			switch(TrashType)
			{
				case 1:Motor_Ctrl_Task(Motor_1,Close);;break;
				case 2:Motor_Ctrl_Task(Motor_2,Close);;break;
				case 3:Motor_Ctrl_Task(Motor_3,Close);;break;
				case 4:Motor_Ctrl_Task(Motor_4,Close);;break;
			}
			delay_ms(500);         //�����ת���ر�����Ͱ����
			Motor_Stop_Task();
			Voice_Play_Task(00011);  //������������--��лʹ�ã�
			StatusCtrl = 0;
		}else 
		{
			Display_Capacity_Info(CapacityValue);  //����̬��ʾ������Ϣ
			delay_ms(1000);
			Display_Capacity_Info(CapacityValue);  
			delay_ms(1000);
			Display_Capacity_Info(CapacityValue);
			delay_ms(1000);
		}
		
			
		if(ScanFinishFlag)    //ɨ��ɹ�
		{
			//printf("Info:%d ,%d ,%d ,%d\r\n",ScanInfoBuf[0],ScanInfoBuf[1],ScanInfoBuf[2],ScanInfoBuf[3]); //��ӡɨ����Ϣ
			TrashType = ScanInfoBuf[3] - 0x30;  //ɨ����Ϣ�е��������
			if(CapacityValue[TrashType]>=100)   //�жϵ�ǰ����Ͱ�Ƿ���ʣ������
				Voice_Play_Task(00006 + TrashType);  //������������--����Ͱ����
			else
				Voice_Play_Task(00001 + TrashType);  //������������--ĳ����Ͱ�Ѵ�
			ClassInfoBuff[ScanInfoBuf[0]-0x30][ScanInfoBuf[1]-0x30]++; //��Ӧ�༶������������1
			Display_Scan_Info(ScanInfoBuf[0],ScanInfoBuf[1],ScanInfoBuf[2],ScanInfoBuf[3],TrashCount,ClassInfoBuff[ScanInfoBuf[0]-0x30][ScanInfoBuf[1]-0x30]);  //��Ļ��ʾ��������Ϣ
			TrashCount++;   //��¼�������༶�ĸ���
			ScanFinishFlag=0;  //��������ɨ��
			StatusCtrl = 2;   //�л���״̬2
		}
		//printf("Distance:%.2f  ,%.2f  ,%.2f  ,%.2f  \r\n",DistanceValue[1],DistanceValue[2],DistanceValue[3],DistanceValue[4]);
	}	 
} 


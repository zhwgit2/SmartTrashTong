#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Timer.h" 
#include "Motor.h"
#include "Display.h"
extern u8 Lock;
extern u8 ScanInfoBuf[5];
extern u8 ScanFinishFlag;
extern float DistanceValue[5];
u8 ClassInfoBuff[6][10]={0};  //�༶��Ϣ���飬����60��ѧ�࣬Ĭ�������꼶��ÿ���꼶ʮ����ѧ��

/**************�����߼�*****************
��̬ʱ����ʾ����ʾ����༶��Ϣ������
���˵���ʱ���������������ȴ�ɨ��ǹ����
ɨ��ɹ����Զ��򿪶�Ӧ����Ͱ���ӣ�����ʾ��ǰѡ������Ͱ����ͣ��Ӧ����Ͱ�������
�ȴ����ߺ��Զ��ر�����Ͱ��������������ʾ����Ͱ�������������ݵ���Ļ��
�ȴ���һ������
***************************************/
							 // EE   B1   10   00   00   00   01   31   C4   EA   BC   B6   31   B0   E0   FF   FC   FF   FF 
//u8 ClassBuf[]= {0xEE,0xB1,0x10,0x00,0x00,0x00,0x01,0x31,0xC4,0xEA,0xBC,0xB6,0x31,0xB0,0xE0,0xFF,0xFC,0xFF,0xFF};  //һ�꼶һ��

#define  DEBUG
void Delay_s(u8 Ns);
u8 TrashCount = 0;
u8 TrashType = 0;
int main(void)
{		
	u8 ScanLock=0;
	u8 CtrlTestFlag=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	Display_Uart3_init(115200);   //��ʾ�����ڳ�ʼ��
	Scan_Uart2_Init(9600);        //ɨ��ǹ���ڳ�ʼ��
	
	
	TIM4_Cap_Init(0xffff,72-1);  //����ʱ����ʼ��
	Ultrasonic_Trigger_TIM3_Init(50000-1,720-1);//������������ʱ����ʼ��
	Ultrasonic_EchoPin_Init();  //���������������ų�ʼ��
	Motor_CtrlPin_Init();  //������ƶ˿ڳ�ʼ��
	Voice_CtrlPin_Init();  //����ģ��˿ڳ�ʼ��
	People_Test_Init();    //������ģ��˿ڳ�ʼ��
	
	
//	Send_To_Display_Comd(ClassBuf,sizeof(ClassBuf));
//	Display_Capacity_Info(CapacityValue); 
//	ScanFinishFlag = 1;
	#ifdef   DEBUG
//		Voice_Play_Task(00001);
//		Voice_Play_Task(00002);
//		Voice_Play_Task(00003);
//		Voice_Play_Task(00004);
//		Voice_Play_Task(00005);
//		Voice_Play_Task(00006);
//		Voice_Play_Task(00007);
//		Voice_Play_Task(8);
//		Voice_Play_Task(9);
//		Voice_Play_Task(10);
//		Voice_Play_Task(11);
		
//		Motor_Ctrl_Task(Motor_1,Open);
//		Delay_s(9);
//		Motor_Stop_Task();
//		
//		Motor_Ctrl_Task(Motor_1,Close);
//		Delay_s(7);
//		Motor_Stop_Task();


//		Motor_Ctrl_Task(Motor_2,Open);
//		Delay_s(9);
//		Motor_Stop_Task();
		
//		Motor_Ctrl_Task(Motor_2,Close);
//		Delay_s(7);
//		Motor_Stop_Task();


//		Motor_Ctrl_Task(Motor_3,Open);
//		Delay_s(9);
//		Motor_Stop_Task();
		
//		Motor_Ctrl_Task(Motor_3,Close);
//		Delay_s(7);
//		Motor_Stop_Task();
//		
		
		
		
//		Motor_Ctrl_Task(Motor_4,Open);
//		Delay_s(9);
//		Motor_Stop_Task();
		
//		Motor_Ctrl_Task(Motor_4,Close);
//		Delay_s(7);
//		Motor_Stop_Task();
		

		
	#endif
	
	while(1) 
	{
		//Send_To_Display_Comd(ClassBuf,sizeof(ClassBuf));
		if(StatusCtrl == 1)  //�����Ӧģ�鴥��״̬ 1
		{
			Voice_Play_Task(00001);  //������������--��ɨ��
			StatusCtrl = 100;   //״̬��ת������̬���ȴ��ɹ�ɨ��
			EXTI->IMR &= ~(EXTI_Line6);  //��ʱ�����ⲿ�ж�
		}else if(StatusCtrl == 2)
		{
			switch(TrashType) //�����ת��������Ͱ����
			{
				case 1:Motor_Ctrl_Task(Motor_1,Open);Delay_s(2);;break;
				case 2:Motor_Ctrl_Task(Motor_2,Open);Delay_s(2);;break;
				case 3:Motor_Ctrl_Task(Motor_3,Open);Delay_s(2);;break;
				case 4:Motor_Ctrl_Task(Motor_4,Open);Delay_s(2);;break;
			}
			Motor_Stop_Task();     //�����ѿ����ȴ�������
			StatusCtrl = 3;   //״̬��ת��״̬3
			Delay_s(10);
			Voice_Play_Task(11);  //������������--��лʹ�ã�
		}else if(StatusCtrl == 3)
		{			
			switch(TrashType)   //�����ת���ر�����Ͱ����
			{
				case 1:Motor_Ctrl_Task(Motor_1,Close);Delay_s(2); ;break;
				case 2:Motor_Ctrl_Task(Motor_2,Close);Delay_s(2); ;break;
				case 3:Motor_Ctrl_Task(Motor_3,Close);Delay_s(2); ;break;
				case 4:Motor_Ctrl_Task(Motor_4,Close);Delay_s(2); ;break;
			}      
			Motor_Stop_Task();
			StatusCtrl = 0;   //״̬���л����ʼ״̬
			Lock = 0;    //�������ȴ���һ�μ������
			ScanLock = 0;//���ɨ��������ȴ���һ��ɨ��
			EXTI->IMR |= (EXTI_Line6);   //�ָ��ⲿ�ж�
			CtrlTestFlag = 0;
		}else if(StatusCtrl == 0)
		{		
			delay_ms(1000);
			CtrlTestFlag++;
			if(CtrlTestFlag > 40)
				CtrlTestFlag = 40;	
			else
				Display_Capacity_Info(CapacityValue);  //����̬��ʾ������Ϣ
			//printf("Distance:%d  ,%d  ,%d  ,%d  \r\n",CapacityValue[1],CapacityValue[2],CapacityValue[3],CapacityValue[4]);
			//printf("Distance:%.2f  ,%.2f  ,%.2f  ,%.2f  \r\n",DistanceValue[1],DistanceValue[2],DistanceValue[3],DistanceValue[4]);
		}
		
		if(!ScanLock)	
		{
			if(ScanFinishFlag)    //ɨ��ɹ�
			{
				printf("Info:%d ,%d ,%d ,%d\r\n",ScanInfoBuf[0],ScanInfoBuf[1],ScanInfoBuf[2],ScanInfoBuf[3]); //��ӡɨ����Ϣ
				TrashType = ScanInfoBuf[2] - 0x30;  //ɨ����Ϣ�е��������
				if(CapacityValue[TrashType] < 5)   //�жϵ�ǰ����Ͱ�Ƿ���ʣ������
					Voice_Play_Task(00006 + TrashType);  //������������--����Ͱ����
				else
					Voice_Play_Task(00001 + TrashType);  //������������--ĳ����Ͱ�Ѵ�
				ClassInfoBuff[ScanInfoBuf[0]-0x30][ScanInfoBuf[1]-0x30]++; //��Ӧ�༶������������1
				Display_Scan_Info(ScanInfoBuf[0],ScanInfoBuf[1],ScanInfoBuf[2],ScanInfoBuf[3],TrashCount,ClassInfoBuff[ScanInfoBuf[0]-0x30][ScanInfoBuf[1]-0x30]);  //��Ļ��ʾ��������Ϣ
				TrashCount++;   //��¼�������༶�ĸ���
				ScanFinishFlag=0;  //��������ɨ��
				StatusCtrl = 2;   //�л���״̬2
				ScanLock = 1;     //ɨ��ɹ������
			}
		}
	}	 
} 


void Delay_s(u8 Ns)
{
	while(Ns--)
		delay_ms(1000);
}





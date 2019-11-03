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
u8 ClassInfoBuff[6][10]={0};  //班级信息数组，开辟60教学班，默认六个年级，每个年级十个教学班

/**************程序逻辑*****************
静态时，显示屏显示标语，班级信息等内容
有人到达时，播报语音，并等待扫码枪工作
扫码成功后，自动打开对应垃圾桶盖子，并显示当前选中垃圾桶，暂停对应垃圾桶容量检测
等待人走后，自动关闭垃圾桶，播报语音，显示垃圾桶余量，更新数据到屏幕上
等待下一次来人
***************************************/
							 // EE   B1   10   00   00   00   01   31   C4   EA   BC   B6   31   B0   E0   FF   FC   FF   FF 
//u8 ClassBuf[]= {0xEE,0xB1,0x10,0x00,0x00,0x00,0x01,0x31,0xC4,0xEA,0xBC,0xB6,0x31,0xB0,0xE0,0xFF,0xFC,0xFF,0xFF};  //一年级一班

#define  DEBUG
void Delay_s(u8 Ns);
u8 TrashCount = 0;
u8 TrashType = 0;
int main(void)
{		
	u8 ScanLock=0;
	u8 CtrlTestFlag=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 //串口初始化为115200
	Display_Uart3_init(115200);   //显示屏串口初始化
	Scan_Uart2_Init(9600);        //扫码枪串口初始化
	
	
	TIM4_Cap_Init(0xffff,72-1);  //捕获定时器初始化
	Ultrasonic_Trigger_TIM3_Init(50000-1,720-1);//超声波触发定时器初始化
	Ultrasonic_EchoPin_Init();  //超声波，触发引脚初始化
	Motor_CtrlPin_Init();  //电机控制端口初始化
	Voice_CtrlPin_Init();  //语音模块端口初始化
	People_Test_Init();    //人体检测模块端口初始化
	
	
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
		if(StatusCtrl == 1)  //人体感应模块触发状态 1
		{
			Voice_Play_Task(00001);  //开启语音播报--请扫码
			StatusCtrl = 100;   //状态跳转至空闲态，等待成功扫码
			EXTI->IMR &= ~(EXTI_Line6);  //暂时挂起外部中断
		}else if(StatusCtrl == 2)
		{
			switch(TrashType) //电机正转，打开垃圾桶盖子
			{
				case 1:Motor_Ctrl_Task(Motor_1,Open);Delay_s(2);;break;
				case 2:Motor_Ctrl_Task(Motor_2,Open);Delay_s(2);;break;
				case 3:Motor_Ctrl_Task(Motor_3,Open);Delay_s(2);;break;
				case 4:Motor_Ctrl_Task(Motor_4,Open);Delay_s(2);;break;
			}
			Motor_Stop_Task();     //盖子已开，等待丢垃圾
			StatusCtrl = 3;   //状态跳转至状态3
			Delay_s(10);
			Voice_Play_Task(11);  //开启语音播报--感谢使用！
		}else if(StatusCtrl == 3)
		{			
			switch(TrashType)   //电机反转，关闭垃圾桶盖子
			{
				case 1:Motor_Ctrl_Task(Motor_1,Close);Delay_s(2); ;break;
				case 2:Motor_Ctrl_Task(Motor_2,Close);Delay_s(2); ;break;
				case 3:Motor_Ctrl_Task(Motor_3,Close);Delay_s(2); ;break;
				case 4:Motor_Ctrl_Task(Motor_4,Close);Delay_s(2); ;break;
			}      
			Motor_Stop_Task();
			StatusCtrl = 0;   //状态机切换会初始状态
			Lock = 0;    //解锁，等待下一次检测行人
			ScanLock = 0;//解除扫码加锁，等待下一次扫码
			EXTI->IMR |= (EXTI_Line6);   //恢复外部中断
			CtrlTestFlag = 0;
		}else if(StatusCtrl == 0)
		{		
			delay_ms(1000);
			CtrlTestFlag++;
			if(CtrlTestFlag > 40)
				CtrlTestFlag = 40;	
			else
				Display_Capacity_Info(CapacityValue);  //空闲态显示容量信息
			//printf("Distance:%d  ,%d  ,%d  ,%d  \r\n",CapacityValue[1],CapacityValue[2],CapacityValue[3],CapacityValue[4]);
			//printf("Distance:%.2f  ,%.2f  ,%.2f  ,%.2f  \r\n",DistanceValue[1],DistanceValue[2],DistanceValue[3],DistanceValue[4]);
		}
		
		if(!ScanLock)	
		{
			if(ScanFinishFlag)    //扫码成功
			{
				printf("Info:%d ,%d ,%d ,%d\r\n",ScanInfoBuf[0],ScanInfoBuf[1],ScanInfoBuf[2],ScanInfoBuf[3]); //打印扫码信息
				TrashType = ScanInfoBuf[2] - 0x30;  //扫码信息中的垃圾类别
				if(CapacityValue[TrashType] < 5)   //判断当前垃圾桶是否有剩余容量
					Voice_Play_Task(00006 + TrashType);  //开启语音播报--垃圾桶已满
				else
					Voice_Play_Task(00001 + TrashType);  //开启语音播报--某垃圾桶已打开
				ClassInfoBuff[ScanInfoBuf[0]-0x30][ScanInfoBuf[1]-0x30]++; //对应班级倒垃圾次数加1
				Display_Scan_Info(ScanInfoBuf[0],ScanInfoBuf[1],ScanInfoBuf[2],ScanInfoBuf[3],TrashCount,ClassInfoBuff[ScanInfoBuf[0]-0x30][ScanInfoBuf[1]-0x30]);  //屏幕显示倒垃圾信息
				TrashCount++;   //记录倒垃圾班级的个数
				ScanFinishFlag=0;  //结束本次扫码
				StatusCtrl = 2;   //切换到状态2
				ScanLock = 1;     //扫码成功后加锁
			}
		}
	}	 
} 


void Delay_s(u8 Ns)
{
	while(Ns--)
		delay_ms(1000);
}





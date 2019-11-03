#include "Motor.h"

/*电机控制*/
/*语音播报控制任务*/

void  Motor_CtrlPin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOG, ENABLE);  //使能GPIOA时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //PA0 输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_Port1, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //PA0 输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_Port2, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9|GPIO_Pin_13|GPIO_Pin_11;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //PA0 输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_Port3, &GPIO_InitStructure);
	
	Motor1_IN1_L();
	Motor1_IN2_L();
	
	Motor2_IN1_L();
	Motor2_IN2_L();
	
	Motor3_IN1_L();
	Motor3_IN2_L();
	
	Motor4_IN1_L();
	Motor4_IN2_L();
}

void  Motor_Ctrl_Task(u8 Motor_N,u8 dir)
{
	switch(Motor_N)
	{
		case Motor_1:{
										if(dir)
										{
											Motor1_IN1_H();
											Motor1_IN2_L();
										}
										else
										{
											Motor1_IN1_L();
											Motor1_IN2_H();
										}
									};break;
		case Motor_2:{
										if(dir)
										{
											Motor2_IN1_L();
											Motor2_IN2_H();									
										}
										else
										{
											Motor2_IN1_H();
											Motor2_IN2_L();
										}
									};break;
		case Motor_3:{
										if(dir)
										{
											Motor3_IN1_H();
											Motor3_IN2_L();
										}
										else
										{
											Motor3_IN1_L();
											Motor3_IN2_H();
										}
									};break;
		case Motor_4:{
										if(dir)
										{
											Motor4_IN1_H();
											Motor4_IN2_L();
										}
										else
										{
											Motor4_IN1_L();
											Motor4_IN2_H();
										}
									};break;
	}
}

void  Motor_Stop_Task(void)
{
	Motor1_IN1_L();
	Motor1_IN2_L();
	
	Motor2_IN1_L();
	Motor2_IN2_L();
	
	Motor3_IN1_L();
	Motor3_IN2_L();
	
	Motor4_IN1_L();
	Motor4_IN2_L();
}

void  Voice_CtrlPin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //使能GPIOA时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
	                               GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //PA0 输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_Write(GPIOD, 0x00ff);     //初始化引脚完成，全部置高为空闲态
}

void  Voice_Play_Task(u8 MusicN)  
{
	u8 PortValue = MusicN ^ 0xff;
	GPIO_Write(GPIOD, PortValue); //触发对应语音
	delay_ms(50);
	GPIO_Write(GPIOD, 0x00ff);   //恢复空闲态
}



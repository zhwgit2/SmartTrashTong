#include "Timer.h"
#include "Display.h"

/*超声波模块驱动程序,人体检测传感器*/

void People_Test_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO, ENABLE);  //使能GPIOA时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource6);

	EXTI_InitStructure.EXTI_Line=EXTI_Line6;	//KEY2
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键WK_UP所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); 
}


void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(Exist_People == 1)	 	 //WK_UP按键
	{				 
		StatusCtrl=0;
	}
	EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE0上的中断标志位  
}

TIM_ICInitTypeDef  TIM4_ICInitStructure;

void TIM4_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能TIM5时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOA时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);						 //PA0 下拉
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);

	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM5输入捕获参数
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	TIM_ITConfig(TIM4,TIM_IT_CC1,ENABLE);
	
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	TIM_ITConfig(TIM4,TIM_IT_CC2,ENABLE);
	
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	TIM_ITConfig(TIM4,TIM_IT_CC3,ENABLE);
	
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	TIM_ITConfig(TIM4,TIM_IT_CC4,ENABLE);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	

	TIM_Cmd(TIM4,ENABLE ); 	//使能定时器5
   


}

//定时器5中断服务程序	 
u8 OverflowNum=0;
u8  TIM4CaptureChannlStatus[5]={0};	//输入捕获各通道状态	  	    				
u16	TIM4CaptureValue[5];  	  //输入捕获值
float DistanceValue[5]={0.0}; //测距值
u8 CapacityValue[5];
void TIM4_IRQHandler(void)
{ 
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//产生了更新中断
	{
		
	}
	if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET) //Channl_1 capture high or low level
	{
		if(TIM4CaptureChannlStatus[1]&0x40)     //Channl_1 capture low level success,and capture finshed!
		{
			TIM4CaptureValue[1]=TIM_GetCapture1(TIM4);
			TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising);
			TIM4CaptureChannlStatus[1]=0;
			DistanceValue[1]=TIM4CaptureValue[1]*34.0/2000.0;
			CapacityValue[1]=(u8)(DistanceValue[1]/CapacityFullValue);
			TIM4CaptureValue[1]=0;
		}
		else   //Channl_1 capture high level success
		{
			TIM_SetCounter(TIM4,0);
			TIM4CaptureChannlStatus[1]=0;
			TIM4CaptureChannlStatus[1]|=0x40;	
			TIM4CaptureValue[1]=0;			
			TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);
		}
	}
	
	if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET) //Channl_1 capture high or low level
	{
		if(TIM4CaptureChannlStatus[2]&0x40)     //Channl_1 capture low level success,and capture finshed!
		{
			TIM4CaptureValue[2]=TIM_GetCapture2(TIM4);
			TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Rising);
			TIM4CaptureChannlStatus[2]=0;
			DistanceValue[2]=TIM4CaptureValue[2]*34.0/2000.0;
			CapacityValue[2]=(u8)(DistanceValue[2]/CapacityFullValue);
			TIM4CaptureValue[2]=0;
		}
		else   //Channl_1 capture high level success
		{
			TIM_SetCounter(TIM4,0);
			TIM4CaptureChannlStatus[2]=0;
			TIM4CaptureChannlStatus[2]|=0x40;	
			TIM4CaptureValue[2]=0;			
			TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Falling);
		}
	}
	
	if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET) //Channl_1 capture high or low level
	{
		if(TIM4CaptureChannlStatus[3]&0x40)     //Channl_1 capture low level success,and capture finshed!
		{
			TIM4CaptureValue[3]=TIM_GetCapture3(TIM4);
			TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Rising);
			TIM4CaptureChannlStatus[3]=0;
			DistanceValue[3]=TIM4CaptureValue[3]*34.0/2000.0;
			CapacityValue[3]=(u8)(DistanceValue[3]/CapacityFullValue);
			TIM4CaptureValue[3]=0;
		}
		else   //Channl_1 capture high level success
		{
			TIM_SetCounter(TIM4,0);
			TIM4CaptureChannlStatus[3]=0;
			TIM4CaptureChannlStatus[3]|=0x40;	
			TIM4CaptureValue[3]=0;			
			TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling);
		}
	}
	
	if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET) //Channl_1 capture high or low level
	{
		if(TIM4CaptureChannlStatus[4]&0x40)     //Channl_1 capture low level success,and capture finshed!
		{
			TIM4CaptureValue[4]=TIM_GetCapture4(TIM4);
			TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising);
			TIM4CaptureChannlStatus[4]=0;
			DistanceValue[4]=TIM4CaptureValue[4]*34.0/2000.0;
			CapacityValue[4]=(u8)(DistanceValue[4]/CapacityFullValue);
			TIM4CaptureValue[4]=0;
		}
		else   //Channl_1 capture high level success
		{
			TIM_SetCounter(TIM4,0);
			TIM4CaptureChannlStatus[4]=0;
			TIM4CaptureChannlStatus[4]|=0x40;	
			TIM4CaptureValue[4]=0;			
			TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);
		}
	}
	
  TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //清除中断标志位
 
}

void Ultrasonic_EchoPin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIOA时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //PA0 输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOC,GPIO_Pin_0);						 //PA0 下拉
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}

void Ultrasonic_Trigger_TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx		
}

void Ultrasonic_Echo_Trigger(u8 Ultrasonic_Num)
{
	GPIO_SetBits(GPIOC,Ultrasonic_Num);
	delay_us(30);
	GPIO_ResetBits(GPIOC,Ultrasonic_Num);
}

void TIM3_IRQHandler(void)   //TIM3中断
{
	static int num=0;
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		switch(num%4)
		{
			case 0:Ultrasonic_Echo_Trigger(Ultrasonic_1);break;
			case 1:Ultrasonic_Echo_Trigger(Ultrasonic_2);break;
			case 2:Ultrasonic_Echo_Trigger(Ultrasonic_3);break;
			case 3:Ultrasonic_Echo_Trigger(Ultrasonic_4);break;
		}
		num++;
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
}









#include "Timer.h"
#include "Display.h"

/*������ģ����������,�����⴫����*/

void People_Test_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIOAʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ���� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource6);

	EXTI_InitStructure.EXTI_Line=EXTI_Line6;	//KEY2
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 
}


void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);//����
	if(Exist_People == 1)	 	 //WK_UP����
	{				 
		StatusCtrl=0;
	}
	EXTI_ClearITPendingBit(EXTI_Line6); //���LINE0�ϵ��жϱ�־λ  
}

TIM_ICInitTypeDef  TIM4_ICInitStructure;

void TIM4_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM5ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOAʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);						 //PA0 ����
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);

	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM5���벶�����
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	TIM_ITConfig(TIM4,TIM_IT_CC1,ENABLE);
	
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	TIM_ITConfig(TIM4,TIM_IT_CC2,ENABLE);
	
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	TIM_ITConfig(TIM4,TIM_IT_CC3,ENABLE);
	
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	TIM_ITConfig(TIM4,TIM_IT_CC4,ENABLE);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//��������ж� ,����CC1IE�����ж�	

	TIM_Cmd(TIM4,ENABLE ); 	//ʹ�ܶ�ʱ��5
   


}

//��ʱ��5�жϷ������	 
u8 OverflowNum=0;
u8  TIM4CaptureChannlStatus[5]={0};	//���벶���ͨ��״̬	  	    				
u16	TIM4CaptureValue[5];  	  //���벶��ֵ
float DistanceValue[5]={0.0}; //���ֵ
u8 CapacityValue[5];
void TIM4_IRQHandler(void)
{ 
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//�����˸����ж�
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
	
  TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //����жϱ�־λ
 
}

void Ultrasonic_EchoPin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIOAʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //PA0 ���� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOC,GPIO_Pin_0);						 //PA0 ����
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}

void Ultrasonic_Trigger_TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx		
}

void Ultrasonic_Echo_Trigger(u8 Ultrasonic_Num)
{
	GPIO_SetBits(GPIOC,Ultrasonic_Num);
	delay_us(30);
	GPIO_ResetBits(GPIOC,Ultrasonic_Num);
}

void TIM3_IRQHandler(void)   //TIM3�ж�
{
	static int num=0;
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
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
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
}









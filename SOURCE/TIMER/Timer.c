#include "Timer.h"


 
TIM_ICInitTypeDef  TIM5_ICInitStructure;

void TIM5_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 ����
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);

	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_CC1,ENABLE);
	
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_CC2,ENABLE);
	
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_CC3,ENABLE);
	
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_ITConfig(TIM5,TIM_IT_CC4,ENABLE);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 

	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);//��������ж� ,����CC1IE�����ж�	

	TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
   


}

//��ʱ��5�жϷ������	 
u8 OverflowNum=0;
u8  TIM5CaptureChannlStatus[5]={0};	//���벶���ͨ��״̬	  	    				
u16	TIM5CaptureValue[5];  	  //���벶��ֵ
float DistanceValue[5]={0.0}; //���ֵ
void TIM5_IRQHandler(void)
{ 
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//�����˸����ж�
	{
		
	}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET) //Channl_1 capture high or low level
	{
		if(TIM5CaptureChannlStatus[1]&0x40)     //Channl_1 capture low level success,and capture finshed!
		{
			TIM5CaptureValue[1]=TIM_GetCapture1(TIM5);
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);
			TIM5CaptureChannlStatus[1]=0;
			DistanceValue[1]=TIM5CaptureValue[1]*340.0/2.0;
			TIM5CaptureValue[1]=0;
		}
		else   //Channl_1 capture high level success
		{
			TIM_SetCounter(TIM5,0);
			TIM5CaptureChannlStatus[1]=0;
			TIM5CaptureChannlStatus[1]|=0x40;	
			TIM5CaptureValue[1]=0;			
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);
		}
	}
	
	if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET) //Channl_1 capture high or low level
	{
		if(TIM5CaptureChannlStatus[2]&0x40)     //Channl_1 capture low level success,and capture finshed!
		{
			TIM5CaptureValue[2]=TIM_GetCapture1(TIM5);
			TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising);
			TIM5CaptureChannlStatus[2]=0;
			DistanceValue[2]=TIM5CaptureValue[2]*340.0/2.0;
			TIM5CaptureValue[2]=0;
		}
		else   //Channl_1 capture high level success
		{
			TIM_SetCounter(TIM5,0);
			TIM5CaptureChannlStatus[2]=0;
			TIM5CaptureChannlStatus[2]|=0x40;	
			TIM5CaptureValue[2]=0;			
			TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling);
		}
	}
	
	if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET) //Channl_1 capture high or low level
	{
		if(TIM5CaptureChannlStatus[3]&0x40)     //Channl_1 capture low level success,and capture finshed!
		{
			TIM5CaptureValue[3]=TIM_GetCapture1(TIM5);
			TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising);
			TIM5CaptureChannlStatus[3]=0;
			DistanceValue[3]=TIM5CaptureValue[3]*340.0/2.0;
			TIM5CaptureValue[3]=0;
		}
		else   //Channl_1 capture high level success
		{
			TIM_SetCounter(TIM5,0);
			TIM5CaptureChannlStatus[3]=0;
			TIM5CaptureChannlStatus[3]|=0x40;	
			TIM5CaptureValue[3]=0;			
			TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Falling);
		}
	}
	
	if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET) //Channl_1 capture high or low level
	{
		if(TIM5CaptureChannlStatus[4]&0x40)     //Channl_1 capture low level success,and capture finshed!
		{
			TIM5CaptureValue[4]=TIM_GetCapture1(TIM5);
			TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Rising);
			TIM5CaptureChannlStatus[4]=0;
			DistanceValue[4]=TIM5CaptureValue[4]*340.0/2.0;
			TIM5CaptureValue[4]=0;
		}
		else   //Channl_1 capture high level success
		{
			TIM_SetCounter(TIM5,0);
			TIM5CaptureChannlStatus[4]=0;
			TIM5CaptureChannlStatus[4]|=0x40;	
			TIM5CaptureValue[3]=0;			
			TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Falling);
		}
	}
	
  TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //����жϱ�־λ
 
}





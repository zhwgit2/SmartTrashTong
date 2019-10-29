#include "Display.h"

u8 ScanInfoBuf[5]={0};
u8 DisClassBuf[]= {0xEE,0xB1,0x10,0x00,0x00,0x00,0x01,0x31,0xC4,0xEA,0xBC,0xB6,0x31,0xB0,0xE0,0xFF,0xFC,0xFF,0xFF};  //һ�꼶һ��
u8 DisTimeBuf[] = {0xEE,0xB1,0x10,0x00,0x00,0x00,0x01,0xD0,0xC7,0xC6,0xDA,0x31,0xFF,0xFC,0xFF,0xFF };  //����һ
u8 DisKeHuiShou[]={0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xBF ,0xC9 ,0xBB ,0xD8 ,0xCA ,0xD5 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF };
u8 DisChuYu[]=    {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xB3 ,0xF8 ,0xD3 ,0xE0 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF };
u8 DisYouHai[]=   {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xD3 ,0xD0 ,0xBA ,0xA6 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF };
u8 DisQiTa[]=     {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xC6 ,0xE4 ,0xCB ,0xFB ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF };


void Scan_Uart2_Init(u32 bound)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
	
  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);  
}

u8 num = 0;
u8 ScanFinishFlag = 0;
void USART2_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	if (USART_GetFlagStatus(USART2,USART_FLAG_RXNE)!=RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		Res = USART_ReceiveData(USART2);	//��ȡ���յ�������
		
		if(Res != '\n')
		{
			ScanInfoBuf[num++] = Res;
		}
		else
		{
			ScanFinishFlag = 1;
			num = 0;
		}
	} 
}

void Display_Uart3_init(u32 bound)
{
		//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA.9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA.9
	
  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART3, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART3, ENABLE);  
}

void USART3_IRQHandler(void)                	//����1�жϷ������
{
	//u8 Res;
	if (USART_GetFlagStatus(USART3,USART_FLAG_RXNE)!=RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		//Res = USART_ReceiveData(USART3);	//��ȡ���յ�������
	} 
}

u8 Display_Scan_Info(u8 ji, u8 ban, u8 time, u8 lei)
{
	DisClassBuf[7] = ji ;
	DisClassBuf[12] = ban ;
	DisTimeBuf[11] = time ;
	Send_To_Display_Comd(DisClassBuf,sizeof(DisClassBuf));
//	Send_To_Display_Comd(DisTimeBuf);
//	switch(lei)
//	{
//		case 1:Send_To_Display_Comd(DisKeHuiShou);break;
//		case 2:Send_To_Display_Comd(DisChuYu);break;
//		case 3:Send_To_Display_Comd(DisYouHai);break;
//		case 4:Send_To_Display_Comd(DisQiTa);break;
//	}
	return 1;
}

u8 Send_To_Display_Comd(u8 *p, u8 length)
{
	int i=0;
	printf("Length:%d\r\n",length);
	while(i < length)
	{
		USART_SendData(USART3,p[i]);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		i++;
	}
	printf("Num:%d\r\n",i);
	return 1;
}

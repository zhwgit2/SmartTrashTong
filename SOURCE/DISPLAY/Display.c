#include "Display.h"
#include "Timer.h"

u8 ScanInfoBuf[5]={0};
u8 DisClassBuf[]= {0xEE,0xB1,0x10,0x00,0x00,0x00,0x01,0x31,0xC4,0xEA,0xBC,0xB6,0x31,0xB0,0xE0,0xFF,0xFC,0xFF,0xFF};  //һ�꼶һ��
u8 DisTimeBuf[] = {0xEE,0xB1,0x10,0x00,0x00,0x00,0x01,0xD0,0xC7,0xC6,0xDA,0x31,0xFF,0xFC,0xFF,0xFF };  //����һ
u8 Capacity[]   = {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0x38 ,0x30 ,0x25 ,0xFF ,0xFC ,0xFF ,0xFF };//80%
u8 NumRecord[] =  {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0x30 ,0xFF ,0xFC ,0xFF ,0xFF }; //1.2.3
u8 DisKeHuiShou[]={0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xBF ,0xC9 ,0xBB ,0xD8 ,0xCA ,0xD5 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF };//�ɻ���
u8 DisChuYu[]=    {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xB3 ,0xF8 ,0xD3 ,0xE0 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF }; //����
u8 DisYouHai[]=   {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xD3 ,0xD0 ,0xBA ,0xA6 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF }; //�к�
u8 DisQiTa[]=     {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xC6 ,0xE4 ,0xCB ,0xFB ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF }; //����
u8 NowType[] ={0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xB5 ,0xB1 ,0xC7 ,0xB0 ,0xD1 ,0xA1 ,0xD6 ,0xD0 ,0xA3 ,0xBA, 0xFF ,0xFC ,0xFF ,0xFF };//��ǰѡ��
u8 OverFlow[]={0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xD2 ,0xD1 ,0xC2 ,0xFA ,0xFF ,0xFC ,0xFF ,0xFF }; //����
u8 Waitting[]={0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xB5 ,0xC8 ,0xB4 ,0xFD ,0xD6 ,0xD0 ,0xFF ,0xFC ,0xFF ,0xFF };  //�ȴ���
u8 DeleteAll[] = {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xFF ,0xFC ,0xFF ,0xFF };

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
u8 StatusCtrl=0;
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
			//StatusCtrl = 2;
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

void Display_Scan_Info(u8 ji, u8 ban, u8 time, u8 lei, u8 count, u8 recordnum)
{
	DisClassBuf[6] = (count * 4)%20 + 1;  //���ÿؼ�ID
	DisClassBuf[7] = ji ;                 //���ð༶��Ϣ
	DisClassBuf[12] = ban ;
	Send_To_Display_Comd(DisClassBuf,sizeof(DisClassBuf));  //��ʾ�༶��Ϣ
	
	DisTimeBuf[6] = (count * 4)%20 + 3;  //���ÿؼ�ID
	DisTimeBuf[11] = time ;              //����ʱ��
	Send_To_Display_Comd(DisTimeBuf,sizeof(DisTimeBuf));    //��ʾʱ����Ϣ
	
	switch(lei-0x30)   //��ʾ��������
	{
		case 1:DisKeHuiShou[6] = (count * 4)%20 + 2;Send_To_Display_Comd(DisKeHuiShou, sizeof(DisKeHuiShou));CapacityValue[1]=110;break;
		case 2:DisChuYu[6] = (count * 4)%20 + 2;	  Send_To_Display_Comd(DisChuYu, sizeof(DisChuYu));        CapacityValue[2]=110;break;
		case 3:DisYouHai[6] = (count * 4)%20 + 2;	  Send_To_Display_Comd(DisYouHai, sizeof(DisYouHai));      CapacityValue[3]=110;break;
		case 4:DisQiTa[6] = (count * 4)%20 + 2;     Send_To_Display_Comd(DisQiTa, sizeof(DisQiTa));          CapacityValue[4]=110;break;
	}

	Display_Capacity_Info(CapacityValue);  //��ʾ��ǰ������Ϣ���򿪵�����Ͱ����ʵ��������ʾ�ȴ���
	
	NumRecord[6] = (count * 4)%20 + 4;    //�޸Ŀؼ�ID
	NumRecord[7] = recordnum + 0x30;      //���õ���������
	Send_To_Display_Comd(NumRecord, sizeof(NumRecord));  //��ʾ����������
	
	NowType[6] = 21;   //�޸Ŀؼ�ID
	Send_To_Display_Comd(NowType, sizeof(NowType));  //��ʾ��ǰѡ��
	
	switch(lei - 0x30)   //��ʾ��ǰѡ����������
	{
		case 1:DisKeHuiShou[6] = 22;Send_To_Display_Comd(DisKeHuiShou, sizeof(DisKeHuiShou));break;
		case 2:DisChuYu[6] = 22;	  Send_To_Display_Comd(DisChuYu, sizeof(DisChuYu));        break;
		case 3:DisYouHai[6] = 22;	 	Send_To_Display_Comd(DisYouHai, sizeof(DisYouHai));      break;
		case 4:DisQiTa[6] = 22;     Send_To_Display_Comd(DisQiTa, sizeof(DisQiTa));          break;
	}
}

void Display_Capacity_Info(u8 *Capacity_p)   //��ʾ������Ϣ
{	
	if (Capacity_p[1] >= 100)  
	{
		Waitting[6] = 23;    //�޸��ı���ID
		Send_To_Display_Comd(Waitting, sizeof(Waitting)); //��ʾ���ȴ��С�
	}
	else if(Capacity_p[1] < 5)
	{
		OverFlow[6] = 23;    //�޸��ı���ID
		Send_To_Display_Comd(OverFlow, sizeof(OverFlow)); //��ʾ��������
	}else
	{
		Capacity[6] = 23;   //�޸��ı���ID
		Capacity[7] = Capacity_p[1]/10 + 0x30;   //�޸�����ֵ��λ
		Capacity[8] = Capacity_p[1]%10 + 0x30;   //�޸�����ֵ��λ
		Send_To_Display_Comd(Capacity, sizeof(Capacity));  //��ʾ����
	}
	
	
	
	if (Capacity_p[2] >= 100)  
	{
		Waitting[6] = 24;    //�޸��ı���ID
		Send_To_Display_Comd(Waitting, sizeof(Waitting)); //��ʾ��������
	}else if(Capacity_p[2] < 5)
	{
		OverFlow[6] = 24;    //�޸��ı���ID
		Send_To_Display_Comd(OverFlow, sizeof(OverFlow)); //��ʾ��������
	}else
	{
		Capacity[6] = 24;   //�޸��ı���ID
		Capacity[7] = Capacity_p[2]/10 + 0x30;   //�޸�����ֵ��λ
		Capacity[8] = Capacity_p[2]%10 + 0x30;   //�޸�����ֵ��λ
		Send_To_Display_Comd(Capacity, sizeof(Capacity));  //��ʾ����
	}
	
	
	
	if (Capacity_p[3] >= 100)  
	{
		OverFlow[6] = 25;    //�޸��ı���ID
		Send_To_Display_Comd(Waitting, sizeof(Waitting)); //��ʾ��������
	}else if(Capacity_p[3] < 5)
	{
		Waitting[6] = 25;    //�޸��ı���ID
		Send_To_Display_Comd(OverFlow, sizeof(OverFlow)); //��ʾ��������
	}else
	{
		Capacity[6] = 25;   //�޸��ı���ID
		Capacity[7] = Capacity_p[3]/10 + 0x30;   //�޸�����ֵ��λ
		Capacity[8] = Capacity_p[3]%10 + 0x30;   //�޸�����ֵ��λ
		Send_To_Display_Comd(Capacity, sizeof(Capacity));  //��ʾ����
	}
	
	
	
	if (Capacity_p[4] >= 100)  
	{
		Waitting[6] = 26;    //�޸��ı���ID
		Send_To_Display_Comd(Waitting, sizeof(Waitting)); //��ʾ��������
	}else if(Capacity_p[4] < 5)
	{
		OverFlow[6] = 26;    //�޸��ı���ID
		Send_To_Display_Comd(OverFlow, sizeof(OverFlow)); //��ʾ��������
	}else
	{
		Capacity[6] = 26;   //�޸��ı���ID
		Capacity[7] = Capacity_p[4]/10 + 0x30;   //�޸�����ֵ��λ
		Capacity[8] = Capacity_p[4]%10 + 0x30;   //�޸�����ֵ��λ
		Send_To_Display_Comd(Capacity, sizeof(Capacity));  //��ʾ����
	}
	
	DeleteAll[6] = 21;
	Send_To_Display_Comd(DeleteAll, sizeof(DeleteAll));
	DeleteAll[6] = 22;
	Send_To_Display_Comd(DeleteAll, sizeof(DeleteAll));
}

u8 Send_To_Display_Comd(u8 *p, u8 length)
{
	u8 i=0;
	//printf("Length:%d\r\n",length);
	while(i < length)
	{
		USART_SendData(USART3,p[i]);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1,p[i]);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		i++;
	}
	//printf("Num:%d\r\n",i);
	return 1;
}



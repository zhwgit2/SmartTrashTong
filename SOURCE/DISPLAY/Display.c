#include "Display.h"

u8 ScanInfoBuf[5]={0};
u8 DisClassBuf[]= {0xEE,0xB1,0x10,0x00,0x00,0x00,0x01,0x31,0xC4,0xEA,0xBC,0xB6,0x31,0xB0,0xE0,0xFF,0xFC,0xFF,0xFF};  //一年级一班
u8 DisTimeBuf[] = {0xEE,0xB1,0x10,0x00,0x00,0x00,0x01,0xD0,0xC7,0xC6,0xDA,0x31,0xFF,0xFC,0xFF,0xFF };  //星期一
u8 DisKeHuiShou[]={0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xBF ,0xC9 ,0xBB ,0xD8 ,0xCA ,0xD5 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF };
u8 DisChuYu[]=    {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xB3 ,0xF8 ,0xD3 ,0xE0 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF };
u8 DisYouHai[]=   {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xD3 ,0xD0 ,0xBA ,0xA6 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF };
u8 DisQiTa[]=     {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xC6 ,0xE4 ,0xCB ,0xFB ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF };


void Scan_Uart2_Init(u32 bound)
{
	//GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	//使能USART1，GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
	
  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);  
}

u8 num = 0;
u8 ScanFinishFlag = 0;
void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	if (USART_GetFlagStatus(USART2,USART_FLAG_RXNE)!=RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		Res = USART_ReceiveData(USART2);	//读取接收到的数据
		
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
		//GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//使能USART1，GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA.9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA.9
	
  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);  
}

void USART3_IRQHandler(void)                	//串口1中断服务程序
{
	//u8 Res;
	if (USART_GetFlagStatus(USART3,USART_FLAG_RXNE)!=RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		//Res = USART_ReceiveData(USART3);	//读取接收到的数据
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

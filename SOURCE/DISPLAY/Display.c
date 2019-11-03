#include "Display.h"
#include "Timer.h"

u8 ScanInfoBuf[5]={0};
u8 DisClassBuf[]= {0xEE,0xB1,0x10,0x00,0x00,0x00,0x01,0x31,0xC4,0xEA,0xBC,0xB6,0x31,0xB0,0xE0,0xFF,0xFC,0xFF,0xFF};  //一年级一班
u8 DisTimeBuf[] = {0xEE,0xB1,0x10,0x00,0x00,0x00,0x01,0xD0,0xC7,0xC6,0xDA,0x31,0xFF,0xFC,0xFF,0xFF };  //星期一
u8 Capacity[]   = {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0x38 ,0x30 ,0x25 ,0xFF ,0xFC ,0xFF ,0xFF };//80%
u8 NumRecord[] =  {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0x30 ,0xFF ,0xFC ,0xFF ,0xFF }; //1.2.3
u8 DisKeHuiShou[]={0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xBF ,0xC9 ,0xBB ,0xD8 ,0xCA ,0xD5 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF };//可回收
u8 DisChuYu[]=    {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xB3 ,0xF8 ,0xD3 ,0xE0 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF }; //厨余
u8 DisYouHai[]=   {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xD3 ,0xD0 ,0xBA ,0xA6 ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF }; //有害
u8 DisQiTa[]=     {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xC6 ,0xE4 ,0xCB ,0xFB ,0xC0 ,0xAC ,0xBB ,0xF8 ,0xFF ,0xFC ,0xFF ,0xFF }; //其他
u8 NowType[] ={0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xB5 ,0xB1 ,0xC7 ,0xB0 ,0xD1 ,0xA1 ,0xD6 ,0xD0 ,0xA3 ,0xBA, 0xFF ,0xFC ,0xFF ,0xFF };//当前选中
u8 OverFlow[]={0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xD2 ,0xD1 ,0xC2 ,0xFA ,0xFF ,0xFC ,0xFF ,0xFF }; //已满
u8 Waitting[]={0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xB5 ,0xC8 ,0xB4 ,0xFD ,0xD6 ,0xD0 ,0xFF ,0xFC ,0xFF ,0xFF };  //等待中
u8 DeleteAll[] = {0xEE ,0xB1 ,0x10 ,0x00 ,0x00 ,0x00 ,0x01 ,0xFF ,0xFC ,0xFF ,0xFF };

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
u8 StatusCtrl=0;
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
			//StatusCtrl = 2;
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

void Display_Scan_Info(u8 ji, u8 ban, u8 time, u8 lei, u8 count, u8 recordnum)
{
	DisClassBuf[6] = (count * 4)%20 + 1;  //设置控件ID
	DisClassBuf[7] = ji ;                 //设置班级信息
	DisClassBuf[12] = ban ;
	Send_To_Display_Comd(DisClassBuf,sizeof(DisClassBuf));  //显示班级信息
	
	DisTimeBuf[6] = (count * 4)%20 + 3;  //设置控件ID
	DisTimeBuf[11] = time ;              //设置时间
	Send_To_Display_Comd(DisTimeBuf,sizeof(DisTimeBuf));    //显示时间信息
	
	switch(lei-0x30)   //显示垃圾类型
	{
		case 1:DisKeHuiShou[6] = (count * 4)%20 + 2;Send_To_Display_Comd(DisKeHuiShou, sizeof(DisKeHuiShou));CapacityValue[1]=110;break;
		case 2:DisChuYu[6] = (count * 4)%20 + 2;	  Send_To_Display_Comd(DisChuYu, sizeof(DisChuYu));        CapacityValue[2]=110;break;
		case 3:DisYouHai[6] = (count * 4)%20 + 2;	  Send_To_Display_Comd(DisYouHai, sizeof(DisYouHai));      CapacityValue[3]=110;break;
		case 4:DisQiTa[6] = (count * 4)%20 + 2;     Send_To_Display_Comd(DisQiTa, sizeof(DisQiTa));          CapacityValue[4]=110;break;
	}

	Display_Capacity_Info(CapacityValue);  //显示当前容量信息，打开的垃圾桶不现实容量，显示等待中
	
	NumRecord[6] = (count * 4)%20 + 4;    //修改控件ID
	NumRecord[7] = recordnum + 0x30;      //设置倒垃圾次数
	Send_To_Display_Comd(NumRecord, sizeof(NumRecord));  //显示倒垃圾次数
	
	NowType[6] = 21;   //修改控件ID
	Send_To_Display_Comd(NowType, sizeof(NowType));  //显示当前选中
	
	switch(lei - 0x30)   //显示当前选中垃圾类型
	{
		case 1:DisKeHuiShou[6] = 22;Send_To_Display_Comd(DisKeHuiShou, sizeof(DisKeHuiShou));break;
		case 2:DisChuYu[6] = 22;	  Send_To_Display_Comd(DisChuYu, sizeof(DisChuYu));        break;
		case 3:DisYouHai[6] = 22;	 	Send_To_Display_Comd(DisYouHai, sizeof(DisYouHai));      break;
		case 4:DisQiTa[6] = 22;     Send_To_Display_Comd(DisQiTa, sizeof(DisQiTa));          break;
	}
}

void Display_Capacity_Info(u8 *Capacity_p)   //显示容量信息
{	
	if (Capacity_p[1] >= 100)  
	{
		Waitting[6] = 23;    //修改文本框ID
		Send_To_Display_Comd(Waitting, sizeof(Waitting)); //显示“等待中”
	}
	else if(Capacity_p[1] < 5)
	{
		OverFlow[6] = 23;    //修改文本框ID
		Send_To_Display_Comd(OverFlow, sizeof(OverFlow)); //显示“已满”
	}else
	{
		Capacity[6] = 23;   //修改文本框ID
		Capacity[7] = Capacity_p[1]/10 + 0x30;   //修改容量值高位
		Capacity[8] = Capacity_p[1]%10 + 0x30;   //修改容量值低位
		Send_To_Display_Comd(Capacity, sizeof(Capacity));  //显示容量
	}
	
	
	
	if (Capacity_p[2] >= 100)  
	{
		Waitting[6] = 24;    //修改文本框ID
		Send_To_Display_Comd(Waitting, sizeof(Waitting)); //显示“已满”
	}else if(Capacity_p[2] < 5)
	{
		OverFlow[6] = 24;    //修改文本框ID
		Send_To_Display_Comd(OverFlow, sizeof(OverFlow)); //显示“已满”
	}else
	{
		Capacity[6] = 24;   //修改文本框ID
		Capacity[7] = Capacity_p[2]/10 + 0x30;   //修改容量值高位
		Capacity[8] = Capacity_p[2]%10 + 0x30;   //修改容量值低位
		Send_To_Display_Comd(Capacity, sizeof(Capacity));  //显示容量
	}
	
	
	
	if (Capacity_p[3] >= 100)  
	{
		OverFlow[6] = 25;    //修改文本框ID
		Send_To_Display_Comd(Waitting, sizeof(Waitting)); //显示“已满”
	}else if(Capacity_p[3] < 5)
	{
		Waitting[6] = 25;    //修改文本框ID
		Send_To_Display_Comd(OverFlow, sizeof(OverFlow)); //显示“已满”
	}else
	{
		Capacity[6] = 25;   //修改文本框ID
		Capacity[7] = Capacity_p[3]/10 + 0x30;   //修改容量值高位
		Capacity[8] = Capacity_p[3]%10 + 0x30;   //修改容量值低位
		Send_To_Display_Comd(Capacity, sizeof(Capacity));  //显示容量
	}
	
	
	
	if (Capacity_p[4] >= 100)  
	{
		Waitting[6] = 26;    //修改文本框ID
		Send_To_Display_Comd(Waitting, sizeof(Waitting)); //显示“已满”
	}else if(Capacity_p[4] < 5)
	{
		OverFlow[6] = 26;    //修改文本框ID
		Send_To_Display_Comd(OverFlow, sizeof(OverFlow)); //显示“已满”
	}else
	{
		Capacity[6] = 26;   //修改文本框ID
		Capacity[7] = Capacity_p[4]/10 + 0x30;   //修改容量值高位
		Capacity[8] = Capacity_p[4]%10 + 0x30;   //修改容量值低位
		Send_To_Display_Comd(Capacity, sizeof(Capacity));  //显示容量
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



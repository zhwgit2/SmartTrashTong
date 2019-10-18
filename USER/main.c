#include "sys.h"
#include "delay.h"
#include "usart.h"
 

int main(void)
 {		
 	u8 t=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 //串口初始化为115200
  while(1)
	{
		printf("t:%d\r\n",t);
		delay_ms(500);
		t++;
	}	 
} 


#include "sys.h"
#include "delay.h"
#include "usart.h"
 

int main(void)
 {		
 	u8 t=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
  while(1)
	{
		printf("t:%d\r\n",t);
		delay_ms(500);
		t++;
	}	 
} 


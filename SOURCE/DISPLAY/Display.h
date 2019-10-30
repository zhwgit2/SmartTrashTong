#ifndef  _DISPLAY_H
#define  _DISPLAY_H 

#include "sys.h"
#include "delay.h"
#include "usart.h"

extern u8 StatusCtrl;
	
void Scan_Uart2_Init(u32 bound);
void Display_Uart3_init(u32 bound);
void Display_Scan_Info(u8 ji, u8 ban, u8 time, u8 lei, u8 num, u8 recordnum);
void Display_Capacity_Info(u8 *Capacity);
u8 Send_To_Display_Comd(u8 *p, u8 length);



#endif




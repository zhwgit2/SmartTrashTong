#ifndef  _TIMER_H
#define  _TIMER_H 

#include "sys.h"
#include "delay.h"
#include "usart.h"

#define  Ultrasonic_1  0x01
#define  Ultrasonic_2  0x02
#define  Ultrasonic_3  0x04
#define  Ultrasonic_4  0x08



void TIM4_Cap_Init(u16 arr,u16 psc);
void Ultrasonic_EchoPin_Init(void);
void Ultrasonic_Trigger_TIM3_Init(u16 arr,u16 psc);
void Ultrasonic_Echo_Trigger(u8 Ultrasonic_Num);

#endif




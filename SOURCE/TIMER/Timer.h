#ifndef  _TIMER_H
#define  _TIMER_H 

#include "sys.h"
#include "delay.h"
#include "usart.h"

#define  Ultrasonic_1  0x01
#define  Ultrasonic_2  0x02
#define  Ultrasonic_3  0x04
#define  Ultrasonic_4  0x08

#define  CapacityFullValue  80    //垃圾桶总容量，高度：10cm

#define  Exist_People   GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_6)


extern u8 CapacityValue[5];   //容量测量结果

void People_Test_Init(void);
void TIM4_Cap_Init(u16 arr,u16 psc);
void Ultrasonic_EchoPin_Init(void);
void Ultrasonic_Trigger_TIM3_Init(u16 arr,u16 psc);
void Ultrasonic_Echo_Trigger(u8 Ultrasonic_Num);

#endif




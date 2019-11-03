#ifndef  _TIMER_H
#define  _TIMER_H 

#include "sys.h"
#include "delay.h"
#include "usart.h"

#define  Ultrasonic_1  GPIO_Pin_0
#define  Ultrasonic_2  GPIO_Pin_1
#define  Ultrasonic_3  GPIO_Pin_2
#define  Ultrasonic_4  GPIO_Pin_3

#define  CapacityFullValue  50    //垃圾桶总容量，高度：10cm

#define  Exist_People   GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_6)


extern u8 CapacityValue[5];   //容量测量结果

void People_Test_Init(void);
void TIM4_Cap_Init(u16 arr,u16 psc);
void Ultrasonic_EchoPin_Init(void);
void Ultrasonic_Trigger_TIM3_Init(u16 arr,u16 psc);
void Ultrasonic_Echo_Trigger(uint16_t Ultrasonic_Num);

#endif




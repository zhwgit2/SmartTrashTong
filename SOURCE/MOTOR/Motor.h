#ifndef  _MOTOR_H
#define  _MOTOR_H 

#include "sys.h"
#include "delay.h"

#define  Motor_Port1  GPIOE
#define  Motor_Port2  GPIOG

#define  Motor_1  0x01
#define  Motor_2  0x02
#define  Motor_3  0x03
#define  Motor_4  0x04

#define  Forward  0x01
#define  Reverse  0x00

#define  Motor1_IN1_H()  GPIO_SetBits(GPIOF,GPIO_Pin_0); 
#define  Motor1_IN1_L()  GPIO_ResetBits(GPIOF,GPIO_Pin_0);
#define  Motor1_IN2_H()  GPIO_SetBits(GPIOF,GPIO_Pin_1); 
#define  Motor1_IN2_L()  GPIO_ResetBits(GPIOF,GPIO_Pin_1);

#define  Motor2_IN1_H()  GPIO_SetBits(GPIOF,GPIO_Pin_2); 
#define  Motor2_IN1_L()  GPIO_ResetBits(GPIOF,GPIO_Pin_2);
#define  Motor2_IN2_H()  GPIO_SetBits(GPIOF,GPIO_Pin_3); 
#define  Motor2_IN2_L()  GPIO_ResetBits(GPIOF,GPIO_Pin_3);

#define  Motor3_IN1_H()  GPIO_SetBits(GPIOF,GPIO_Pin_4); 
#define  Motor3_IN1_L()  GPIO_ResetBits(GPIOF,GPIO_Pin_4);
#define  Motor3_IN2_H()  GPIO_SetBits(GPIOF,GPIO_Pin_5); 
#define  Motor3_IN2_L()  GPIO_ResetBits(GPIOF,GPIO_Pin_5);

#define  Motor4_IN1_H()  GPIO_SetBits(GPIOF,GPIO_Pin_6); 
#define  Motor4_IN1_L()  GPIO_ResetBits(GPIOF,GPIO_Pin_6);
#define  Motor4_IN2_H()  GPIO_SetBits(GPIOF,GPIO_Pin_7); 
#define  Motor4_IN2_L()  GPIO_ResetBits(GPIOF,GPIO_Pin_7);

void  Motor_CtrlPin_Init(void);
void  Motor_Ctrl_Task(u8 Motor_N,u8 dir);
void  Motor_Stop_Task(void);



#endif




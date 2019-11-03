#ifndef  _MOTOR_H
#define  _MOTOR_H 

#include "sys.h"
#include "delay.h"

#define  Motor_Port1  GPIOE
#define  Motor_Port2  GPIOG
#define  Motor_Port3  GPIOD

#define  Motor_1  0x01
#define  Motor_2  0x02
#define  Motor_3  0x03
#define  Motor_4  0x04

#define  Forward  0x01
#define  Reverse  0x00

#define  Open   0x00
#define  Close  0x01

#define  Motor1_IN1_H()  GPIO_SetBits(Motor_Port2,GPIO_Pin_13); 
#define  Motor1_IN1_L()  GPIO_ResetBits(Motor_Port2,GPIO_Pin_13);
#define  Motor1_IN2_H()  GPIO_SetBits(Motor_Port1,GPIO_Pin_0); 
#define  Motor1_IN2_L()  GPIO_ResetBits(Motor_Port1,GPIO_Pin_0);

#define  Motor2_IN1_H()  GPIO_SetBits(Motor_Port2,GPIO_Pin_14); 
#define  Motor2_IN1_L()  GPIO_ResetBits(Motor_Port2,GPIO_Pin_14);
#define  Motor2_IN2_H()  GPIO_SetBits(Motor_Port2,GPIO_Pin_12); 
#define  Motor2_IN2_L()  GPIO_ResetBits(Motor_Port2,GPIO_Pin_12);

#define  Motor3_IN1_H()  GPIO_SetBits(Motor_Port1,GPIO_Pin_11); 
#define  Motor3_IN1_L()  GPIO_ResetBits(Motor_Port1,GPIO_Pin_11);
#define  Motor3_IN2_H()  GPIO_SetBits(Motor_Port1,GPIO_Pin_13); 
#define  Motor3_IN2_L()  GPIO_ResetBits(Motor_Port1,GPIO_Pin_13);

#define  Motor4_IN1_H()  GPIO_SetBits(Motor_Port1,GPIO_Pin_8); 
#define  Motor4_IN1_L()  GPIO_ResetBits(Motor_Port1,GPIO_Pin_8);
#define  Motor4_IN2_H()  GPIO_SetBits(Motor_Port1,GPIO_Pin_9); 
#define  Motor4_IN2_L()  GPIO_ResetBits(Motor_Port1,GPIO_Pin_9);

void  Motor_CtrlPin_Init(void);
void  Motor_Ctrl_Task(u8 Motor_N,u8 dir);
void  Motor_Stop_Task(void);

/***********������������*****************
00001����ӭʹ��������������ϵͳ����ʹ��ɨ��ǹɨ�롣
00002��ɨ��ɹ����ɻ�������Ͱ�Ѵ򿪡�
00003��ɨ��ɹ�����������Ͱ�Ѵ򿪡�
00004��ɨ��ɹ����к�����Ͱ�Ѵ򿪡�
00005��ɨ��ɹ�����������Ͱ�Ѵ򿪡�
00006��ɨ��ʧ�ܡ�������ɨ�롣
00007���ɻ�������Ͱ��������೵���ڻ��ٸ�����
00008����������Ͱ��������೵���ڻ��ٸ�����
00009���к�����Ͱ��������೵���ڻ��ٸ�����
00010����������Ͱ��������೵���ڻ��ٸ�����
00011���������࣬�������𡣸�л����ʹ�ã�
****************************************/
void  Voice_CtrlPin_Init(void);
void  Voice_Play_Task(u8 MusicN);

#endif




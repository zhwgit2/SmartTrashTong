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

/***********语音播报内容*****************
00001：欢迎使用智能垃圾分类系统。请使用扫码枪扫码。
00002：扫码成功。可回收垃圾桶已打开。
00003：扫码成功。厨余垃圾桶已打开。
00004：扫码成功。有害垃圾桶已打开。
00005：扫码成功。其他垃圾桶已打开。
00006：扫码失败。请重新扫码。
00007：可回收垃圾桶已满，清洁车正在火速赶来！
00008：厨余垃圾桶已满，清洁车正在火速赶来！
00009：有害垃圾桶已满，清洁车正在火速赶来！
00010：其他垃圾桶已满，清洁车正在火速赶来！
00011：垃圾分类，从我做起。感谢您的使用！
****************************************/
void  Voice_CtrlPin_Init(void);
void  Voice_Play_Task(u8 MusicN);

#endif




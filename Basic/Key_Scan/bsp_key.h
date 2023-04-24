#ifndef __KEY_H
#define	__KEY_H


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include <stdio.h>
//  引脚定义
#define   Key_IO_1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)  //编码器下边开关
#define   Key_IO_2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) //点动开关 


 /** 按键按下标置宏
	*  按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
	*  若按键按下为低电平，把宏设置成KEY_ON=0 ，KEY_OFF=1 即可
	*/
#define KEY_ON	1
#define KEY_OFF	0

void Key_GPIO_Config(void);
void bsp_key_Scan(void);


#endif /* __KEY_H */


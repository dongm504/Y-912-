/**
  ******************************************************************************
  * @file stm8s_user.c
  * @brief This file contains all the functions for the GPIO peripheral.
  * @author STMicroelectronics - MCD Application Team
  * @version V1.1.1
  * @date 18/08/2014
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
	* <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"  //NVIC
#include <stdio.h>
#include "bsp_usart.h"
#include "bsp_key.h"
//#include "bsp_adc.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* Exported bit ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/*****************************************************************************/
 void delay_ms1(u8 i)
{
   while(i--);
}

/***************************************************************************** 
 * 函数名：NVIC_Configuration
 * 描述  ：配置RTC秒中断的主中断优先级为1，次优先级为0
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void IT_NVIC_Config(void)
{
	//NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Configure one bit for preemption priority */
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* Enable the RTC Interrupt */
	//NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	/*
  系统初始化后，系统默认的系统初始化函数SystemInit函数里面已经初始化APB1的时钟分频为2
	分频，APB1时钟分频数为1的时候，TIM2-7时钟为APB1的时钟，如果APB1的分频数不为1的时候
	TIM2-7的时钟频率2倍
              Tout = ((arr+1)(psc+1))/Tclk
	 Tout : 为定时器溢出时间
   Tclk : 为定时器的输入时钟频率
*/
//使能总中断    													
   // NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
//使能TM2中断
   // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//先占优先级为0级
   // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//从优先级为3级
   // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//IRQ通道使能
   // NVIC_Init(&NVIC_InitStructure);
}
//------------------------------------------------------------------------------------------------------------------------------
void 	Bsp_GPIO_Init(void)										//系统初始化
{
//------------------------------------------------------------------------------------------ 
//  NVIC_InitTypeDef NVIC_InitStructure;    
//  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
/*定义GPIO_InitTypeDef结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |RCC_APB2Periph_AFIO, ENABLE);//  使能IO口时钟
//IO初始化    
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_5|GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
		 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
//-----------------------------------------------------------------------------------------		
   	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_2|GPIO_Pin_11;  // 设置PC8 PC7 PC6 PC3为上拉输入
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9;   // 设置PB0 PB6 PB7为上拉输入
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	  // 设置PA0 PA1为上拉输入
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
//--------------------------------------------------------------------------------
/************************************************************************
//定时器初始化  D
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);    	 
//使能TM2寄存器
     TIM_TimeBaseStructure.TIM_Prescaler= (72);	     
//定时器预分频72M/72
     TIM_DeInit(TIM2);
     TIM_TimeBaseStructure.TIM_Period=(10);  
//自动装载寄存器赋，溢出时间1000*72/72M
     TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;    
//采样分频
     TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
//向上计数模式
     TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//
     IT_NVIC_Config( );

     TIM_ClearFlag(TIM2, TIM_FLAG_Update);		                                        
     TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
     TIM_Cmd(TIM2, ENABLE);	
 		 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*???????*/    

}
/******************* (C) COPYRIGHT 2014  *****END OF FILE****/
void 	System_Init( void )
{
     Bsp_GPIO_Init( );		
     USART1_Init( );
}	


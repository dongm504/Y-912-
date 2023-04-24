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
 * ��������NVIC_Configuration
 * ����  ������RTC���жϵ����ж����ȼ�Ϊ1�������ȼ�Ϊ0
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
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
  ϵͳ��ʼ����ϵͳĬ�ϵ�ϵͳ��ʼ������SystemInit���������Ѿ���ʼ��APB1��ʱ�ӷ�ƵΪ2
	��Ƶ��APB1ʱ�ӷ�Ƶ��Ϊ1��ʱ��TIM2-7ʱ��ΪAPB1��ʱ�ӣ����APB1�ķ�Ƶ����Ϊ1��ʱ��
	TIM2-7��ʱ��Ƶ��2��
              Tout = ((arr+1)(psc+1))/Tclk
	 Tout : Ϊ��ʱ�����ʱ��
   Tclk : Ϊ��ʱ��������ʱ��Ƶ��
*/
//ʹ�����ж�    													
   // NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
//ʹ��TM2�ж�
   // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//��ռ���ȼ�Ϊ0��
   // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//�����ȼ�Ϊ3��
   // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//IRQͨ��ʹ��
   // NVIC_Init(&NVIC_InitStructure);
}
//------------------------------------------------------------------------------------------------------------------------------
void 	Bsp_GPIO_Init(void)										//ϵͳ��ʼ��
{
//------------------------------------------------------------------------------------------ 
//  NVIC_InitTypeDef NVIC_InitStructure;    
//  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
/*����GPIO_InitTypeDef�ṹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |RCC_APB2Periph_AFIO, ENABLE);//  ʹ��IO��ʱ��
//IO��ʼ��    
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
   	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_2|GPIO_Pin_11;  // ����PC8 PC7 PC6 PC3Ϊ��������
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9;   // ����PB0 PB6 PB7Ϊ��������
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	  // ����PA0 PA1Ϊ��������
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
//--------------------------------------------------------------------------------
/************************************************************************
//��ʱ����ʼ��  D
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);    	 
//ʹ��TM2�Ĵ���
     TIM_TimeBaseStructure.TIM_Prescaler= (72);	     
//��ʱ��Ԥ��Ƶ72M/72
     TIM_DeInit(TIM2);
     TIM_TimeBaseStructure.TIM_Period=(10);  
//�Զ�װ�ؼĴ����������ʱ��1000*72/72M
     TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;    
//������Ƶ
     TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
//���ϼ���ģʽ
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


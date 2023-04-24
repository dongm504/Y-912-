
 /******************************************************************************
  * @file    stm32_user.h
  * @author  Chris
  * @version V3.5.0
  * @date    2015-10-30
  * @brief   This file contains all the functions prototypes for the GPIO 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_USER_H
#define __STM32_USER_H

/* Includes ------------------------------------------------------------------*/
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "timers.h"
/*开发硬件头文件*/
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_key.h"
/* Exported variables ------------------------------------------------------- */
	
//----------------------------------------------------------------------------/
typedef union 
{
  struct
  {
    unsigned char high,low;
  }part;
  unsigned int two_bytes;
}Int_char;
//-------------------------------------
typedef union
{
	struct
	{
		unsigned char b0:1;
		unsigned char b1:1;
		unsigned char b2:1;
		unsigned char b3:1;
		unsigned char b4:1;
		unsigned char b5:1;
		unsigned char b6:1;
		unsigned char b7:1;
	}bits;
	unsigned char allbits;
}BitType;
//-----------------------------------------------------------------------------^|^/
extern  BitType       TimerBit ;
extern  BitType       flag1;
extern  BitType       flag2; 
extern  BitType       flag3; 
extern  u8            udISR_Key_Mode;
extern  u8            udISR_Key_Speed;
//--------------------------------------------------------------------------------
#define  fISR_Key_up                       flag1.bits.b0
#define  fISR_Key_Level                    flag1.bits.b1
#define  fISR_Key_Power                    flag1.bits.b2
#define  fISR_Key_Pulse                    flag1.bits.b3
#define  fISR_Key_Start                    flag1.bits.b4
#define  fISR_Key_Mode                     flag1.bits.b5
/* DEFINE USER ---------------------------------------------------------------^^*/
#define  fISR_Timer_1ms                    TimerBit.bits.b0
#define  fISR_Timer_10ms                   TimerBit.bits.b1
#define  fISR_Timer_100ms                  TimerBit.bits.b2
#define  fISR_Timer_250ms                  TimerBit.bits.b3
#define  fISR_Timer_500ms                  TimerBit.bits.b4
#define  fISR_Timer_base                   TimerBit.bits.b5
#define  fISR_Timer_1Sec                   TimerBit.bits.b6
#define  fISR_Timer_Led1250ms              TimerBit.bits.b7
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
//------------------------------------------------------------------------------
//Flash 操作寄存器。
#define  STARTADDR   0x08010000                          //STM32F103要存储的开始地址
//-------------------------------------------------------------------------------
/* DEFINE USER ---------------------------------------------------------------^^*/
//马达控制IO
#define   Syn_IO_1          GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)//交流同步信号控制IO
#define   RL_IO1_Clr()      GPIO_ResetBits(GPIOB,GPIO_Pin_5)        //可控硅控制IO
#define   RL_IO1_Set()      GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define   Motor_IO1_Clr()   GPIO_ResetBits(GPIOC,GPIO_Pin_12)        //继电器控制IO
#define   Motor_IO1_Set()   GPIO_SetBits(GPIOC,GPIO_Pin_12)  
//**********************************************************************************
#define   Hz50_IO_Clr()     GPIO_ResetBits(GPIOA,GPIO_Pin_4)//50Hz型号输出
#define   Hz50_IO_Set()     GPIO_SetBits(GPIOA,GPIO_Pin_4)
//------------------------------------------------------------------------------------
//LED控制IO
#define   LED_IO_Dir1_Clr()    GPIO_ResetBits(GPIOC,GPIO_Pin_3)        //LED驱动IO
#define   LED_IO_Dir1_Set()    GPIO_SetBits(GPIOC,GPIO_Pin_3)
#define   Sck_IO_Clr()         GPIO_ResetBits(GPIOB,GPIO_Pin_11)        //595驱动IO
#define   Sck_IO_Set()         GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define   Pck_IO_Clr()         GPIO_ResetBits(GPIOB,GPIO_Pin_10)        //595驱动IO
#define   Pck_IO_Set()         GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define   Data_IO_Clr()        GPIO_ResetBits(GPIOB,GPIO_Pin_1)        //595驱动IO
#define   Data_IO_Set()        GPIO_SetBits(GPIOB,GPIO_Pin_1)
//------------------------------------------------------------------------------------
#define   Key_IO              GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)  //
#define   Out_IO_1            GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)  //
#define   Out_IO_2            GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)  // 
#define   Sw_IO_1             GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) //检测开关1
#define   Sw_IO_2             GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) //检测开关2
#define   Ks_IO_2             GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)  //编码器开关1
#define   Ks_IO_1             GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)  //编码器开关2
/* Exported macros --------------------------------------------------------------*/
//消息队列
extern  QueueHandle_t  Led_Message_Queue;
extern  QueueHandle_t  oLed_Message_Queue;
//二值信号量
extern  SemaphoreHandle_t Led_BinarySem_Handle;
extern  SemaphoreHandle_t oLed_BinarySem_Handle;
extern  SemaphoreHandle_t Start_BinarySem_Handle;
//计数器信号量
extern  SemaphoreHandle_t CountSem_Handle;
/*-----------------------------------------------------------------------------*/

/* Exported macros --------------------------------------------------------------*/
/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define  ON   0
#define  OFF  1
#define PRINTF 
/* 带参宏，可以像内联函数一样使用 */

/* Private macros ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
//函数声明
void  System_Init(void);
void  USART1_Init(void);	
void  bsp_key(void);   
void  bsp_led(void);  
void  bsp_motor(void);   
void  System_Led_AllOpen(void);
void  CodingsWitchPolling(void);
void  bsp_oled(void);
#endif  /* __STM32_USER_H */

/******************* (C) COPYRIGHT 2014  *****END OF FILE****/

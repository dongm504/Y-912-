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
#include "stm32_user.h"
/* Private typedef -----------------------------------------------------------*/
//---------------------------------------------------------------------------
u8   SW_shadow;//按键扫描寄存器
//---------------------------------------------------------------------------
u8   key_cnt_number;//连续计数
//---------------------------------------------------------------------------
u8   key_cnt_timer; //操作计时 
//----------------------------------------------------------------------------
BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为 pdPASS */		
//---------------------------------------------------------------------------
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/                       
/* Exported variables ------------------------------------------------------- */

/* Exported bit ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
/*
;------------------------------------------------------------------------------
客户： 厦门优尔智能科技有限公司
;------------------------------------------------------------------------------
产品： 高端封口机
;------------------------------------------------------------------------------						
功能说明： 检测交流信号
;------------------------------------------------------------------------------
主要功能：
;------------------------------------------------------------------------------*/
void Switch_Add(void)
{  
   if(fISR_Key_Mode)
   {	   
      ++udISR_Key_Speed; 
      if(udISR_Key_Speed > 6)
         udISR_Key_Speed = 6;
      printf("当前速度是%d\r\n",udISR_Key_Speed);
   }
    else
   { 
      ++udISR_Key_Mode;
      if(udISR_Key_Mode > 8)
          udISR_Key_Mode = 8;
	   printf("当前模式是%d\r\n",udISR_Key_Mode);
   }
//----------------------------------------------------------------------------
     xReturn = xSemaphoreGive(Led_BinarySem_Handle);  
	 if(pdPASS == xReturn)
	{ 
	   #ifdef PRINTF 
		  printf("消息 Led_BinarySem_Handle 发送成功!\n\n");	
	  #endif 	 
   }	
	 xReturn = xSemaphoreGive(oLed_BinarySem_Handle);  
	 if(pdPASS == xReturn)
	{ 
		#ifdef PRINTF 
		  printf("消息 oLcd_BinarySem_Handle 发送成功!\n\n");	
 	   #endif 	 
   }	
}
//----------------------------------------------------------------------------
void Switch_Sub(void)
{
   if(fISR_Key_Mode)
   {	   
      --udISR_Key_Speed; 
      if(0 == udISR_Key_Speed)
         udISR_Key_Speed = 1;
      printf("当前速度是%d\r\n",udISR_Key_Speed);
   }
    else
   { 
	    --udISR_Key_Mode;
      if(0 == udISR_Key_Mode)
          udISR_Key_Mode = 1;
	   printf("当前模式是%d\r\n",udISR_Key_Mode);
   }	
//------------------------------------------------------------------------   
    xReturn = xSemaphoreGive(Led_BinarySem_Handle);  
	if(pdPASS == xReturn)
   { 
	   #ifdef PRINTF 
		  printf("消息 Led_BinarySem_Handle 发送成功!\n\n");	
	  #endif 	 
   }	
	xReturn = xSemaphoreGive(oLed_BinarySem_Handle);  
	if(pdPASS == xReturn)
   { 
		#ifdef PRINTF 
		  printf("消息 oLcd_BinarySem_Handle 发送成功!\n\n");	
	   #endif 	 
   }		
}
//----------------------------------------------------------------------------
void CodingsWitchPolling(void)//编码开关处理
{//扫描时间1ms
      unsigned char temp;
//--------------------------------------------------------------------------//      
	  temp = 0;
	//读取编码开关的数据
	  if(Ks_IO_1 == 1)  temp |= 0x10;
		 else  temp &= 0xef;
	  if(Ks_IO_2 == 1)  temp |= 0x20;
		 else  temp &= 0xdf; 
//--------------------------------------------------------------------------//		 	 
         if(temp == 0x30)   
        {
            SW_shadow = 0x80;//两通道都浮空 重新开始检查按键
            key_cnt_number = 0;//复位延迟时间
        }
//-------------------------------------------------------------------------//				
		 if(temp == 0x00)
        {
            SW_shadow = 0x40;//两通道都浮空 重新开始检查按键
            key_cnt_number = 0;//复位延迟时间
        }
//-------------------------------------------------------------------------//			
         if((SW_shadow&0x80)&&(key_cnt_timer == 25))
        {
             if(key_cnt_number < 15) key_cnt_number++;                                                    
             if(((temp&0x20) != 0)&&(key_cnt_number > 2))
            {//B通道未接通 A->B顺序 减操作
                SW_shadow=0;//复位按键检测 但key_cnt_number继续累计
                key_cnt_number = 0;    
							  key_cnt_timer = 0;
             //  if(key_cnt_number<=3)DIS_SET_Data-=4; //如果转的快，数据变化的快
                Switch_Add( );      //编码器值加   	
                					
            }
//-------------------------------------------------------------------------------------------
             if(((temp&0x10) != 0)&&(key_cnt_number > 2))
            {//A通道未接通 B->A顺序 加操作
                SW_shadow = 0;//复位按键检测 但key_cnt_number继续累计
                key_cnt_number = 0;    
				key_cnt_timer = 0;      
             // if(key_cnt_number<=3)DIS_SET_Data+=4; //如果转的快，数据变化的快
                Switch_Sub( ); 		            			
            }                   
        }
//---------------------------------------------------------------------------------------
			if((SW_shadow&0x40)&&(key_cnt_timer == 25))
        {
             if(key_cnt_number < 15) key_cnt_number++;                                   
             if(((temp&0x10)!= 0)&&(key_cnt_number > 2))
            {//B通道未接通 A->B顺序 减操作
                SW_shadow=0;//复位按键检测 但key_cnt_number继续累计
                key_cnt_number = 0;
                key_cnt_timer = 0;      
             //  if(key_cnt_number<=3)DIS_SET_Data-=4; //如果转的快，数据变化的快
                Switch_Add( ); 							
           }
//-------------------------------------------------------------------------------------------
           if(((temp&0x20)!= 0)&&(key_cnt_number > 2))
          {//A通道未接通 B->A顺序 加操作
                SW_shadow = 0;//复位按键检测 但key_cnt_number继续累计
                key_cnt_number = 0;  
                key_cnt_timer = 0;          
           // if(key_cnt_number<=3)DIS_SET_Data+=4; //如果转的快，数据变化的快
                Switch_Sub( );					
           }            
        }			
         key_cnt_timer++;
         if(key_cnt_timer >= 25)
        {//50ms
           key_cnt_timer = 25;
        ///每50ms复位一次计时。保证不会超过50       
        }
//---------------------------------------------------------------------------- 
//功能选择 

//--------------------------------------------------------------------------------  
}

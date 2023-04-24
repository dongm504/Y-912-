/**
  ******************************************************************************
  * @file    Key_Scan().c
  * @author  fire
  * @version V1.0
  * @date    2021-09-14
  * @brief     
  ******************************************************************************
  * @attention
  *
  * 
  * 
  * 
  ******************************************************************************
  */
/* include -------------------------------------------------------------------*/
#include "stm32_user.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/                       
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

u8   Key_buf;
u8   Key_Data ;
u8   Key_Filter;  
u8   ReadData;
u8   Trg;
u8   Cont; 
BitType     flag1;
u8   udISR_Key_Mode;
u8   udISR_Key_Speed;
/* Exported bit ------------------------------------------------------------*/
#define   Value_1             ((u8)4)
#define   Value_2             ((u8)3)
#define   Value_3             ((u8)2)
#define   Value_4             ((u8)1)
#define   Value_Pulse         ((u8)0xfd)
#define   Value_Key_up        ((u8)0xff)
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/  
/******************************************************************************/
/***********************************************************************
  * @ 函数名  ： bsp_key
  * @ 功能说明： 按键扫描程序
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  **********************************************************************/
void bsp_key(void)   
{   
	  BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为 pdPASS */		
 	    Key_Data = 0; 	
      if(!Key_IO) 	 
        Key_Data = 1;		
      if(!Out_IO_1)
	    Key_Data = 4; 	 	 
      if(!Out_IO_2)
        Key_Data = 3;	  
//----------------------------------------------------------------------------		
      if( Key_Data != Key_buf )		    
	  {
	     Key_buf = Key_Data;
	     Key_Filter = 0; 
	  }
//------------------------------------------------------------------------------
	    if( ++Key_Filter >= 5 )	         
	  {
	      Key_Filter = 0;
	      ReadData   =	Key_Data^0xFF;
	      Trg		 =	ReadData&( ReadData^Cont );
	      Cont	     =	ReadData; 
//------------------------------------------------------------------------------
//开机键		  
		   if((Value_2 == Trg)&&(!fISR_Key_up))
		  {
			   fISR_Key_up = 1;
			   if(fISR_Key_Power)
			  {
				#ifdef PRINTF
			     printf("产品关机\r\n");
				#endif 
				 fISR_Key_Power = 0;
                 fISR_Key_Start = 0;
                 fISR_Key_Mode  = 0;					  
			  }	 
			   else
		      {
				#ifdef PRINTF
				  printf("产品开机\r\n");
				#endif  	
				 fISR_Key_Power = 1;
				 fISR_Key_Mode  = 0;
              	 udISR_Key_Mode = 1;
                 udISR_Key_Speed = 1;				  
		      }	 
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
//------------------------------------------------------------------------------
//选择键		  
          if((Value_1 == Trg)&&(!fISR_Key_up))
		 {
			  fISR_Key_up = 1;          						 
		      if(fISR_Key_Power&&(!fISR_Key_Start))
			 {
			     if(fISR_Key_Mode)
				{//进入自动模式
                     fISR_Key_Mode  = 0;
					 #ifdef PRINTF
				  	   printf("进入自动模式\r\n");
					 #endif   			  		    
                } 
                 else
			    {//进入模式选择
					 fISR_Key_Mode   = 1;
					 #ifdef PRINTF
					   printf("进入手动模式\r\n");
					 #endif  
				}
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
		 }	    			 
//-------------------------------------------------------------------------	
//工作键		 
		 if((Value_4 == Trg)&&(!fISR_Key_up))
		{
		     fISR_Key_up = 1;  
			 if(fISR_Key_Power)
		    {
			   if(fISR_Key_Start)
			   {//模式停止工作
			      fISR_Key_Start = 0;
				  #ifdef PRINTF
				     printf("停止搅拌\n");
				  #endif	   
			   }	   
			   else
			   {//模式开始工作
				  fISR_Key_Start = 1;
				  #ifdef PRINTF	 
			         printf("开始搅拌\n");
				   #endif	 	 	
			   }	   
			}	
		}						
//------------------------------------------------------------------------------	
//按键松开		 
		  if(Cont == Value_Key_up)
		 {
    	      fISR_Key_up  = 0;			
         }		 
	  }	
}
/*********************************************END OF FILE**********************/

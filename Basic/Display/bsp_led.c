/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************/
                                                                                
#include "stm32_user.h"  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/             
/* Exported variables ------------------------------------------------------- */                 
/* Exported bit ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
/*Defined------------------------------------------------------------------*/                      
u8   udISR_Led_Data;  
/* Exported bit ------------------------------------------------------------*/
  


 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
//控制595------------------------------------------------------------------------  
void HC595_WR(unsigned char dta)
{
    u8 i;
	for(i = 0;i<8;i++)
   {
       Sck_IO_Clr();
	   if(dta&0x80) 
          Data_IO_Set() ; 
	   else
	      Data_IO_Clr() ; 
	   dta<<=1; 
	   Sck_IO_Set();      
   }
}
//-----------------------------------------------------------------------------
void HC595_Over(void)
{
	  Pck_IO_Clr();       
    Pck_IO_Set();  
    Data_IO_Clr() ; 	
}
//------------------------------------------------------------------------------
void SMG_Display(unsigned char data)
{
	  HC595_WR(data);  
	  HC595_Over(); 
}
//------------------------------------------------------------------------------
void System_595( void )
{
	 SMG_Display(udISR_Led_Data);	 		
}  
//------------------------------------------------------------------------------
//所有灯熄灭
void System_Led_Close( void )
{	
	 udISR_Led_Data = udISR_Led_Data&0x00; 
	 udISR_Led_Data = udISR_Led_Data|0x08;
	 System_595( );		
}
void System_Led_CloseAC( void )
{
   LED_IO_Dir1_Clr();  
	 udISR_Led_Data = 0;	 
	 System_595( );		
}
//-----------------------------------------------------------------------------
//所有灯点亮
void System_Led_AllOpen( void )
{
    u8 i = 0Xff;
	  LED_IO_Dir1_Set()  ;  
  	SMG_Display(i);			
}	
//------------------------------------------------------------------------------
void bsp_led(void)   
{		
     BaseType_t xReturn = pdTRUE;
     xReturn = xSemaphoreTake(Led_BinarySem_Handle,/* 二值信号量句柄 */ 
                            portMAX_DELAY); /* 等待时间 */
	 
     if(pdTRUE == xReturn)
     {
		     if(fISR_Key_Power)
		   {
		       udISR_Led_Data = udISR_Led_Data|0x04;
			  
			      if(fISR_Key_Mode)	 udISR_Led_Data = udISR_Led_Data|0x02; 
                   else    udISR_Led_Data = udISR_Led_Data&(~0x02);
            if(!fISR_Key_Mode)
           {
               udISR_Led_Data = udISR_Led_Data&0x0e; 
			         LED_IO_Dir1_Clr();
           }
            else
           {
                switch(udISR_Key_Speed)
	            {
                    case 1: 
						       udISR_Led_Data = udISR_Led_Data&0x0e;
						       udISR_Led_Data = udISR_Led_Data|0x80;
                               LED_IO_Dir1_Clr()  ;  				 
				             break;
                    case 2:	
                               udISR_Led_Data = udISR_Led_Data&0x0e;						
                               udISR_Led_Data = udISR_Led_Data|0x81;
                               LED_IO_Dir1_Clr()  ;  								 
				             break;
                    case 3:	
					           udISR_Led_Data = udISR_Led_Data&0x0e;			
                               udISR_Led_Data = udISR_Led_Data|0x81;
                               LED_IO_Dir1_Set()  ;  	 
				             break;
                    case 4:	
						       udISR_Led_Data = udISR_Led_Data&0x0e;			
						       udISR_Led_Data = udISR_Led_Data|0x91;
                               LED_IO_Dir1_Set()  ;  
                             break;		
                    case 5: 
                               udISR_Led_Data = udISR_Led_Data&0x0e;								
                               udISR_Led_Data = udISR_Led_Data|0xb1;
                               LED_IO_Dir1_Set()  ;  				 
				             break;
                    case 6:	
						       udISR_Led_Data = udISR_Led_Data&0x0e;	
                               udISR_Led_Data = udISR_Led_Data|0xf1;
                               LED_IO_Dir1_Set()  ;  						 
				           break;       
			        default:
					         break;	
	             }         		   		 
              } 	      		   
		    }	   	   
		     else
		    {
		       udISR_Led_Data = 0;   
               LED_IO_Dir1_Clr();
		    }	           
     }    
     else
       printf("数据接收出错,错误代码0x%lx\n",xReturn); 
     System_595( );	                
}

/*********************************************END OF FILE**********************/

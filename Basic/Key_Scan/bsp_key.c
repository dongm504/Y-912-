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
  * @ ������  �� bsp_key
  * @ ����˵���� ����ɨ�����
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  **********************************************************************/
void bsp_key(void)   
{   
	  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��Ϊ pdPASS */		
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
//������		  
		   if((Value_2 == Trg)&&(!fISR_Key_up))
		  {
			   fISR_Key_up = 1;
			   if(fISR_Key_Power)
			  {
				#ifdef PRINTF
			     printf("��Ʒ�ػ�\r\n");
				#endif 
				 fISR_Key_Power = 0;
                 fISR_Key_Start = 0;
                 fISR_Key_Mode  = 0;					  
			  }	 
			   else
		      {
				#ifdef PRINTF
				  printf("��Ʒ����\r\n");
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
			         printf("��Ϣ Led_BinarySem_Handle ���ͳɹ�!\n\n");	
				 #endif 	 
              }	
			     xReturn = xSemaphoreGive(oLed_BinarySem_Handle);  
	           if(pdPASS == xReturn)
			  { 
				 #ifdef PRINTF 
			         printf("��Ϣ oLcd_BinarySem_Handle ���ͳɹ�!\n\n");	
				 #endif 	 
              }						 
		  }		
//------------------------------------------------------------------------------
//ѡ���		  
          if((Value_1 == Trg)&&(!fISR_Key_up))
		 {
			  fISR_Key_up = 1;          						 
		      if(fISR_Key_Power&&(!fISR_Key_Start))
			 {
			     if(fISR_Key_Mode)
				{//�����Զ�ģʽ
                     fISR_Key_Mode  = 0;
					 #ifdef PRINTF
				  	   printf("�����Զ�ģʽ\r\n");
					 #endif   			  		    
                } 
                 else
			    {//����ģʽѡ��
					 fISR_Key_Mode   = 1;
					 #ifdef PRINTF
					   printf("�����ֶ�ģʽ\r\n");
					 #endif  
				}
                  xReturn = xSemaphoreGive(Led_BinarySem_Handle);  
	              if(pdPASS == xReturn)
			    { 
				    #ifdef PRINTF 
			           printf("��Ϣ Led_BinarySem_Handle ���ͳɹ�!\n\n");	
				    #endif 	 
                }	
			       xReturn = xSemaphoreGive(oLed_BinarySem_Handle);  
	             if(pdPASS == xReturn)
			    { 
				   #ifdef PRINTF 
			          printf("��Ϣ oLcd_BinarySem_Handle ���ͳɹ�!\n\n");	
				   #endif 	 
                }
			 }		 	               
		 }	    			 
//-------------------------------------------------------------------------	
//������		 
		 if((Value_4 == Trg)&&(!fISR_Key_up))
		{
		     fISR_Key_up = 1;  
			 if(fISR_Key_Power)
		    {
			   if(fISR_Key_Start)
			   {//ģʽֹͣ����
			      fISR_Key_Start = 0;
				  #ifdef PRINTF
				     printf("ֹͣ����\n");
				  #endif	   
			   }	   
			   else
			   {//ģʽ��ʼ����
				  fISR_Key_Start = 1;
				  #ifdef PRINTF	 
			         printf("��ʼ����\n");
				   #endif	 	 	
			   }	   
			}	
		}						
//------------------------------------------------------------------------------	
//�����ɿ�		 
		  if(Cont == Value_Key_up)
		 {
    	      fISR_Key_up  = 0;			
         }		 
	  }	
}
/*********************************************END OF FILE**********************/

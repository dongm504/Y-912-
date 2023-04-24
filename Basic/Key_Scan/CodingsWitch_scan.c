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
u8   SW_shadow;//����ɨ��Ĵ���
//---------------------------------------------------------------------------
u8   key_cnt_number;//��������
//---------------------------------------------------------------------------
u8   key_cnt_timer; //������ʱ 
//----------------------------------------------------------------------------
BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��Ϊ pdPASS */		
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
�ͻ��� �����Ŷ����ܿƼ����޹�˾
;------------------------------------------------------------------------------
��Ʒ�� �߶˷�ڻ�
;------------------------------------------------------------------------------						
����˵���� ��⽻���ź�
;------------------------------------------------------------------------------
��Ҫ���ܣ�
;------------------------------------------------------------------------------*/
void Switch_Add(void)
{  
   if(fISR_Key_Mode)
   {	   
      ++udISR_Key_Speed; 
      if(udISR_Key_Speed > 6)
         udISR_Key_Speed = 6;
      printf("��ǰ�ٶ���%d\r\n",udISR_Key_Speed);
   }
    else
   { 
      ++udISR_Key_Mode;
      if(udISR_Key_Mode > 8)
          udISR_Key_Mode = 8;
	   printf("��ǰģʽ��%d\r\n",udISR_Key_Mode);
   }
//----------------------------------------------------------------------------
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
//----------------------------------------------------------------------------
void Switch_Sub(void)
{
   if(fISR_Key_Mode)
   {	   
      --udISR_Key_Speed; 
      if(0 == udISR_Key_Speed)
         udISR_Key_Speed = 1;
      printf("��ǰ�ٶ���%d\r\n",udISR_Key_Speed);
   }
    else
   { 
	    --udISR_Key_Mode;
      if(0 == udISR_Key_Mode)
          udISR_Key_Mode = 1;
	   printf("��ǰģʽ��%d\r\n",udISR_Key_Mode);
   }	
//------------------------------------------------------------------------   
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
//----------------------------------------------------------------------------
void CodingsWitchPolling(void)//���뿪�ش���
{//ɨ��ʱ��1ms
      unsigned char temp;
//--------------------------------------------------------------------------//      
	  temp = 0;
	//��ȡ���뿪�ص�����
	  if(Ks_IO_1 == 1)  temp |= 0x10;
		 else  temp &= 0xef;
	  if(Ks_IO_2 == 1)  temp |= 0x20;
		 else  temp &= 0xdf; 
//--------------------------------------------------------------------------//		 	 
         if(temp == 0x30)   
        {
            SW_shadow = 0x80;//��ͨ�������� ���¿�ʼ��鰴��
            key_cnt_number = 0;//��λ�ӳ�ʱ��
        }
//-------------------------------------------------------------------------//				
		 if(temp == 0x00)
        {
            SW_shadow = 0x40;//��ͨ�������� ���¿�ʼ��鰴��
            key_cnt_number = 0;//��λ�ӳ�ʱ��
        }
//-------------------------------------------------------------------------//			
         if((SW_shadow&0x80)&&(key_cnt_timer == 25))
        {
             if(key_cnt_number < 15) key_cnt_number++;                                                    
             if(((temp&0x20) != 0)&&(key_cnt_number > 2))
            {//Bͨ��δ��ͨ A->B˳�� ������
                SW_shadow=0;//��λ������� ��key_cnt_number�����ۼ�
                key_cnt_number = 0;    
							  key_cnt_timer = 0;
             //  if(key_cnt_number<=3)DIS_SET_Data-=4; //���ת�Ŀ죬���ݱ仯�Ŀ�
                Switch_Add( );      //������ֵ��   	
                					
            }
//-------------------------------------------------------------------------------------------
             if(((temp&0x10) != 0)&&(key_cnt_number > 2))
            {//Aͨ��δ��ͨ B->A˳�� �Ӳ���
                SW_shadow = 0;//��λ������� ��key_cnt_number�����ۼ�
                key_cnt_number = 0;    
				key_cnt_timer = 0;      
             // if(key_cnt_number<=3)DIS_SET_Data+=4; //���ת�Ŀ죬���ݱ仯�Ŀ�
                Switch_Sub( ); 		            			
            }                   
        }
//---------------------------------------------------------------------------------------
			if((SW_shadow&0x40)&&(key_cnt_timer == 25))
        {
             if(key_cnt_number < 15) key_cnt_number++;                                   
             if(((temp&0x10)!= 0)&&(key_cnt_number > 2))
            {//Bͨ��δ��ͨ A->B˳�� ������
                SW_shadow=0;//��λ������� ��key_cnt_number�����ۼ�
                key_cnt_number = 0;
                key_cnt_timer = 0;      
             //  if(key_cnt_number<=3)DIS_SET_Data-=4; //���ת�Ŀ죬���ݱ仯�Ŀ�
                Switch_Add( ); 							
           }
//-------------------------------------------------------------------------------------------
           if(((temp&0x20)!= 0)&&(key_cnt_number > 2))
          {//Aͨ��δ��ͨ B->A˳�� �Ӳ���
                SW_shadow = 0;//��λ������� ��key_cnt_number�����ۼ�
                key_cnt_number = 0;  
                key_cnt_timer = 0;          
           // if(key_cnt_number<=3)DIS_SET_Data+=4; //���ת�Ŀ죬���ݱ仯�Ŀ�
                Switch_Sub( );					
           }            
        }			
         key_cnt_timer++;
         if(key_cnt_timer >= 25)
        {//50ms
           key_cnt_timer = 25;
        ///ÿ50ms��λһ�μ�ʱ����֤���ᳬ��50       
        }
//---------------------------------------------------------------------------- 
//����ѡ�� 

//--------------------------------------------------------------------------------  
}

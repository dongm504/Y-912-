
/**
  ******************************************************************************
  * @file    main..c
  * @author  Youo
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
/* include -------------------------------------------------------------*/
#include "stm32_user.h"
#include "stm32f10x_conf.h"
#include "OLED_I2C.h"
#include "delay.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/                       
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
static void AppTaskCreate(void);/* ���ڴ������� */
static void KEY_Task(void* pvParameters);/* LEDָʾ������ʵ�� */
static void LED_Task(void* pvParameters);/* KEY��������ʵ�� */
static void CODER_Task(void* pvParameters);/*coder����������ʵ�� */
static void MOTOR_Task(void *pvParameters);/*coder����������ʵ�� */
static void OLED_Task(void *pvParameters);/*coder����������ʵ�� */
/* Handle ------------------------------------------------------------------- */
static TaskHandle_t  AppTaskCreate_Handle = NULL;/* ���������� */
static TaskHandle_t  LED_Task_Handle = NULL;     /* LED������ */
static TaskHandle_t  KEY_Task_Handle = NULL;     /* KEY������ */
static TaskHandle_t  CODER_Task_Handle = NULL;    /*CODER������ */
static TaskHandle_t  MOTOR_Task_Handle = NULL;    /*MOTOR������ */
static TaskHandle_t  OLED_Task_Handle = NULL;
/*��Ϣ����---------------------------------------------------------------------*/
QueueHandle_t Led_Message_Queue =NULL;
QueueHandle_t oLed_Message_Queue =NULL;
#define Message_Queue_Size sizeof(u8)
#define Message_Queue_Length 4
/*��ֵ�ź���-------------------------------------------------------------------*/
SemaphoreHandle_t Led_BinarySem_Handle =NULL;
SemaphoreHandle_t oLed_BinarySem_Handle =NULL;
SemaphoreHandle_t Start_BinarySem_Handle =NULL;
/*�������ź���-------------------------------------------------------------------*/
SemaphoreHandle_t CountSem_Handle =NULL;
/*�¼�
EventGroupHandle_t Event_Handle =NULL;

/*****************************************************************
  * @brief  CODER_Task 
  * @param  ��
  * @retval ��
  * @note    
  ****************************************************************/
void OLED_Task(void *pvParameters)
{
	 while(1)
	{	
	   bsp_oled( ); 
	}
}
/*****************************************************************
/*****************************************************************
  * @brief  CODER_Task 
  * @param  ��
  * @retval ��
  * @note    
  ****************************************************************/
void CODER_Task(void *pvParameters)
{
	 while(1)
	{	
		 if(fISR_Key_Power&&(!fISR_Key_Start))
	    {		
		   CodingsWitchPolling( );
		}
		 vTaskDelay(1);
	}
}
/*****************************************************************
  * @brief  KEY_Task 
  * @param  ��
  * @retval ��
  * @note    
  ****************************************************************/
void KEY_Task(void *pvParameters)
{
	 while(1)
	{	
		 //printf("����Key\r\n");
		 bsp_key( );
		 vTaskDelay(1);		
	}
}
/*****************************************************************
  * @brief  Led_Task 
  * @param  ��
  * @retval ��
  * @note    
  ****************************************************************/
void LED_Task(void *pvParameters)
{

     BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
     uint32_t r_queue;	/* ����һ��������Ϣ�ı��� */
     while (1)
    {       
       bsp_led( );     		 
    }	
}
/*****************************************************************
  * @brief  Motor_Task 
  * @param  ��
  * @retval ��
  * @note    
  ****************************************************************/
void MOTOR_Task(void *pvParameters)
{
       while (1)
      {       
         bsp_motor( );   	 
      }	
}
//-------------------------------------------------------------------------------------
/*****************************************************************
  * @brief  ������
  * @param  ��
  * @retval ��
  * @note   ��һ����Ӳ����ʼ��
            �ڶ���������APPӦ������
            ������������FreeRTOS����ʼ���������
  ****************************************************************/

int main(void){
	
	BaseType_t xReturn = pdPASS;/*����һ��������Ϣ�ķ���ֵ��Ĭ��ֵΪpdPASS */
	System_Init( );	
	printf("��ʼ�����\r\n");
	System_Led_CloseAC( );
	DelayInit();
	I2C_Configuration();
	OLED_Init();
	OLED_CLS();
	xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /*��������� */
                         (const char*    )"AppTaskCreate",/*������*/
                         (uint16_t       )512,  /* ����ջ��С */
                         (void*          )NULL,/* ������ں������� */
                         (UBaseType_t    )1, /*���ȼ�Ϊ1*/
                         (TaskHandle_t*  )&AppTaskCreate_Handle);/*������ƿ�ָ��*/ 

						
    if(pdPASS == xReturn)
      vTaskStartScheduler();   /*���������� */
    else
    return -1;  	
	
	while(1)
	{	
			
	};
	return 0;
}
/***********************************************************************
  * @ ������  �� AppTaskCreate
  * @ ����˵���� Ϊ�˷���������е����񴴽����������������������
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  **********************************************************************/
static void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
  
  taskENTER_CRITICAL();           //�����ٽ���
  /* ����Test_Queue */
  #if 0
  Led_Message_Queue =  xQueueCreate((UBaseType_t) Message_Queue_Length,/* ��Ϣ���еĳ��� */
                                   (UBaseType_t)  Message_Queue_Size); /* ��Ϣ�Ĵ�С */
  if(NULL !=  Led_Message_Queue)
     printf("����Key_Message_Queue��Ϣ���гɹ�!\r\n");
  
   oLcd_Message_Queue = xQueueCreate((UBaseType_t) Message_Queue_Length,/* ��Ϣ���еĳ��� */
                                    (UBaseType_t)  Message_Queue_Size); /* ��Ϣ�Ĵ�С */	
  if(NULL != oLcd_Message_Queue )
	 printf("����Key_Message_Queue��Ϣ���гɹ�!\r\n");
 #endif  
//-----------------------------------------------------------------------------------	
 /* ���� BinarySem */
    Led_BinarySem_Handle = xSemaphoreCreateBinary();	
  if(NULL != Led_BinarySem_Handle)
     printf("Led_BinarySem_Handle��ֵ�ź��������ɹ�!\r\n");

    oLed_BinarySem_Handle = xSemaphoreCreateBinary();	
  if(NULL !=  oLed_BinarySem_Handle)
     printf("oLcd_BinarySem_Handle��ֵ�ź��������ɹ�!\r\n");  

    Start_BinarySem_Handle = xSemaphoreCreateBinary();	
  if(NULL != Start_BinarySem_Handle)
     printf("Start_BinarySem_Handle��ֵ�ź��������ɹ�!\r\n");   
//----------------------------------------------------------------------------------   
 /* ���� CountSem */ 
  #if 0
   CountSem_Handle = xSemaphoreCreateCounting(5,5); 
   if (NULL != CountSem_Handle) 
      printf("CountSem_Handle �����ź��������ɹ�!\r\n");
  #endif
//-------------------------------------------------------------------------------   
  /* ����oLcd_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )OLED_Task, /* ������ں��� */
                        (const char*    )OLED_Task,/* �������� */
                        (uint16_t       )512,   /* ����ջ��С */
                        (void*          )NULL,	/* ������ں������� */
                        (UBaseType_t    )1,	    /* ��������ȼ� */
                        (TaskHandle_t*  )&OLED_Task_Handle);/* ������ƿ�ָ�� */
  if(pdPASS == xReturn)
     printf("����OLCD_Task����ɹ�!\r\n");
//-----------------------------------------------------------------------------------      
  /* ����LED_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )MOTOR_Task, /* ������ں��� */
                        (const char*    )"MOTOR_Task",/* �������� */
                        (uint16_t       )512,   /* ����ջ��С */
                        (void*          )NULL,	/* ������ں������� */
                        (UBaseType_t    )1,	    /* ��������ȼ� */
                        (TaskHandle_t*  )&MOTOR_Task_Handle);/* ������ƿ�ָ�� */
  if(pdPASS == xReturn)
     printf("����Motor_Task����ɹ�!\r\n");
//-----------------------------------------------------------------------------------
  /* ����LED_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )LED_Task, /* ������ں��� */
                        (const char*    )"LED_Task",/* �������� */
                        (uint16_t       )512,   /* ����ջ��С */
                        (void*          )NULL,	/* ������ں������� */
                        (UBaseType_t    )1,	    /* ��������ȼ� */
                        (TaskHandle_t*  )&LED_Task_Handle);/* ������ƿ�ָ�� */
  if(pdPASS == xReturn)
     printf("����LED_Task����ɹ�!\r\n");
//--------------------------------------------------------------------------------------	  
  /* ����KEY_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )KEY_Task,  /* ������ں��� */
                        (const char*    )"KEY_Task",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )5, /* ��������ȼ� */
                        (TaskHandle_t*  )&KEY_Task_Handle);/* ������ƿ�ָ�� */					
  if(pdPASS == xReturn)
     printf("����KEY_Task����ɹ�!\r\n");
//-------------------------------------------------------------------------------------- 
    /* ����KEY_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )CODER_Task,  /* ������ں��� */
                        (const char*    )"CODER_Task",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )5, /* ��������ȼ� */
                        (TaskHandle_t*  )&CODER_Task_Handle);/* ������ƿ�ָ�� */					
  if(pdPASS == xReturn)
     printf("����CODER_Task����ɹ�!\r\n");  
//--------------------------------------------------------------------------------------  
  vTaskDelete(AppTaskCreate_Handle); //ɾ��AppTaskCreate����
  printf("ɾ��AppTaskCreate_Handle!\r\n");
  taskEXIT_CRITICAL();            //�˳��ٽ���
}
//------------------------------------------------------------------------------------


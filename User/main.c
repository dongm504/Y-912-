
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
static void AppTaskCreate(void);/* 用于创建任务 */
static void KEY_Task(void* pvParameters);/* LED指示灯任务实现 */
static void LED_Task(void* pvParameters);/* KEY按键任务实现 */
static void CODER_Task(void* pvParameters);/*coder编码器任务实现 */
static void MOTOR_Task(void *pvParameters);/*coder编码器任务实现 */
static void OLED_Task(void *pvParameters);/*coder编码器任务实现 */
/* Handle ------------------------------------------------------------------- */
static TaskHandle_t  AppTaskCreate_Handle = NULL;/* 创建任务句柄 */
static TaskHandle_t  LED_Task_Handle = NULL;     /* LED任务句柄 */
static TaskHandle_t  KEY_Task_Handle = NULL;     /* KEY任务句柄 */
static TaskHandle_t  CODER_Task_Handle = NULL;    /*CODER任务句柄 */
static TaskHandle_t  MOTOR_Task_Handle = NULL;    /*MOTOR任务句柄 */
static TaskHandle_t  OLED_Task_Handle = NULL;
/*消息队列---------------------------------------------------------------------*/
QueueHandle_t Led_Message_Queue =NULL;
QueueHandle_t oLed_Message_Queue =NULL;
#define Message_Queue_Size sizeof(u8)
#define Message_Queue_Length 4
/*二值信号量-------------------------------------------------------------------*/
SemaphoreHandle_t Led_BinarySem_Handle =NULL;
SemaphoreHandle_t oLed_BinarySem_Handle =NULL;
SemaphoreHandle_t Start_BinarySem_Handle =NULL;
/*计数器信号量-------------------------------------------------------------------*/
SemaphoreHandle_t CountSem_Handle =NULL;
/*事件
EventGroupHandle_t Event_Handle =NULL;

/*****************************************************************
  * @brief  CODER_Task 
  * @param  无
  * @retval 无
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
  * @param  无
  * @retval 无
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
  * @param  无
  * @retval 无
  * @note    
  ****************************************************************/
void KEY_Task(void *pvParameters)
{
	 while(1)
	{	
		 //printf("任务Key\r\n");
		 bsp_key( );
		 vTaskDelay(1);		
	}
}
/*****************************************************************
  * @brief  Led_Task 
  * @param  无
  * @retval 无
  * @note    
  ****************************************************************/
void LED_Task(void *pvParameters)
{

     BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
     uint32_t r_queue;	/* 定义一个接收消息的变量 */
     while (1)
    {       
       bsp_led( );     		 
    }	
}
/*****************************************************************
  * @brief  Motor_Task 
  * @param  无
  * @retval 无
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
  * @brief  主函数
  * @param  无
  * @retval 无
  * @note   第一步：硬件初始化
            第二步：创建APP应用任务
            第三步：启动FreeRTOS，开始多任务调度
  ****************************************************************/

int main(void){
	
	BaseType_t xReturn = pdPASS;/*定义一个创建信息的返回值，默认值为pdPASS */
	System_Init( );	
	printf("初始化完成\r\n");
	System_Led_CloseAC( );
	DelayInit();
	I2C_Configuration();
	OLED_Init();
	OLED_CLS();
	xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /*任务函数入口 */
                         (const char*    )"AppTaskCreate",/*任务名*/
                         (uint16_t       )512,  /* 任务栈大小 */
                         (void*          )NULL,/* 任务入口函数参数 */
                         (UBaseType_t    )1, /*优先级为1*/
                         (TaskHandle_t*  )&AppTaskCreate_Handle);/*任务控制块指针*/ 

						
    if(pdPASS == xReturn)
      vTaskStartScheduler();   /*开启调度器 */
    else
    return -1;  	
	
	while(1)
	{	
			
	};
	return 0;
}
/***********************************************************************
  * @ 函数名  ： AppTaskCreate
  * @ 功能说明： 为了方便管理，所有的任务创建函数都放在这个函数里面
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  **********************************************************************/
static void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
  
  taskENTER_CRITICAL();           //进入临界区
  /* 创建Test_Queue */
  #if 0
  Led_Message_Queue =  xQueueCreate((UBaseType_t) Message_Queue_Length,/* 消息队列的长度 */
                                   (UBaseType_t)  Message_Queue_Size); /* 消息的大小 */
  if(NULL !=  Led_Message_Queue)
     printf("创建Key_Message_Queue消息队列成功!\r\n");
  
   oLcd_Message_Queue = xQueueCreate((UBaseType_t) Message_Queue_Length,/* 消息队列的长度 */
                                    (UBaseType_t)  Message_Queue_Size); /* 消息的大小 */	
  if(NULL != oLcd_Message_Queue )
	 printf("创建Key_Message_Queue消息队列成功!\r\n");
 #endif  
//-----------------------------------------------------------------------------------	
 /* 创建 BinarySem */
    Led_BinarySem_Handle = xSemaphoreCreateBinary();	
  if(NULL != Led_BinarySem_Handle)
     printf("Led_BinarySem_Handle二值信号量创建成功!\r\n");

    oLed_BinarySem_Handle = xSemaphoreCreateBinary();	
  if(NULL !=  oLed_BinarySem_Handle)
     printf("oLcd_BinarySem_Handle二值信号量创建成功!\r\n");  

    Start_BinarySem_Handle = xSemaphoreCreateBinary();	
  if(NULL != Start_BinarySem_Handle)
     printf("Start_BinarySem_Handle二值信号量创建成功!\r\n");   
//----------------------------------------------------------------------------------   
 /* 创建 CountSem */ 
  #if 0
   CountSem_Handle = xSemaphoreCreateCounting(5,5); 
   if (NULL != CountSem_Handle) 
      printf("CountSem_Handle 计数信号量创建成功!\r\n");
  #endif
//-------------------------------------------------------------------------------   
  /* 创建oLcd_Task任务 */
  xReturn = xTaskCreate((TaskFunction_t )OLED_Task, /* 任务入口函数 */
                        (const char*    )OLED_Task,/* 任务名字 */
                        (uint16_t       )512,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )1,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&OLED_Task_Handle);/* 任务控制块指针 */
  if(pdPASS == xReturn)
     printf("创建OLCD_Task任务成功!\r\n");
//-----------------------------------------------------------------------------------      
  /* 创建LED_Task任务 */
  xReturn = xTaskCreate((TaskFunction_t )MOTOR_Task, /* 任务入口函数 */
                        (const char*    )"MOTOR_Task",/* 任务名字 */
                        (uint16_t       )512,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )1,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&MOTOR_Task_Handle);/* 任务控制块指针 */
  if(pdPASS == xReturn)
     printf("创建Motor_Task任务成功!\r\n");
//-----------------------------------------------------------------------------------
  /* 创建LED_Task任务 */
  xReturn = xTaskCreate((TaskFunction_t )LED_Task, /* 任务入口函数 */
                        (const char*    )"LED_Task",/* 任务名字 */
                        (uint16_t       )512,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )1,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&LED_Task_Handle);/* 任务控制块指针 */
  if(pdPASS == xReturn)
     printf("创建LED_Task任务成功!\r\n");
//--------------------------------------------------------------------------------------	  
  /* 创建KEY_Task任务 */
  xReturn = xTaskCreate((TaskFunction_t )KEY_Task,  /* 任务入口函数 */
                        (const char*    )"KEY_Task",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )5, /* 任务的优先级 */
                        (TaskHandle_t*  )&KEY_Task_Handle);/* 任务控制块指针 */					
  if(pdPASS == xReturn)
     printf("创建KEY_Task任务成功!\r\n");
//-------------------------------------------------------------------------------------- 
    /* 创建KEY_Task任务 */
  xReturn = xTaskCreate((TaskFunction_t )CODER_Task,  /* 任务入口函数 */
                        (const char*    )"CODER_Task",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )5, /* 任务的优先级 */
                        (TaskHandle_t*  )&CODER_Task_Handle);/* 任务控制块指针 */					
  if(pdPASS == xReturn)
     printf("创建CODER_Task任务成功!\r\n");  
//--------------------------------------------------------------------------------------  
  vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务
  printf("删除AppTaskCreate_Handle!\r\n");
  taskEXIT_CRITICAL();            //退出临界区
}
//------------------------------------------------------------------------------------


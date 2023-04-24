/*
 * FreeRTOS Kernel V10.3.1
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/
#define configUSE_PREEMPTION			1	//Ϊ1ʱRTOSʹ����ռʽ��������Ϊ0ʱRTOSʹ��Э��ʽ��������ʱ��Ƭ��
#define configUSE_IDLE_HOOK				0	//����Ϊ1ʹ�ÿ��й��ӣ�Idle Hook�����ڻص���������0���Կ��й��ӡ�
#define configUSE_TICK_HOOK				0 //����Ϊ1ʹ��ʱ��Ƭ���ӣ�Tick Hook����0����ʱ��Ƭ���ӡ�
#define configCPU_CLOCK_HZ				( ( unsigned long ) 72000000 )	//CPU�ں�ʱ��Ƶ��
#define configTICK_RATE_HZ				( ( TickType_t ) 100 ) //RTOS ϵͳ�����жϵ�Ƶ�ʡ���һ���жϵĴ�����ÿ���ж�RTOS�������������ȡ�
#define configMAX_PRIORITIES			( 5 ) //����Ӧ�ó�����Ч�����ȼ���Ŀ 0���ȼ���С
#define configMINIMAL_STACK_SIZE    	( ( unsigned short ) 128 ) //�����������ʹ�õĶ�ջ��С��
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 17 * 1024 ) ) //RTOS�ں��ܼƿ��õ���Ч��RAM��С ���Ϊ17K
#define configMAX_TASK_NAME_LEN	    	( 16 ) //������������Ƴ������ֵ ����\0
#define configUSE_TRACE_FACILITY	    0 //���ó�1��ʾ�������ӻ����ٵ��ԣ��ἤ��һЩ���ӵĽṹ���Ա�ͺ�����
#define configUSE_16_BIT_TICKS		    0 //����Ϊ1ʹ��16λ������ Ϊ0ʹ��32λ �������������ʱ������ʱ�䣬16λ��������262�룬��32λ��17179869�롣
#define configIDLE_SHOULD_YIELD		    1 //���Ϳ���������ͬ���ȼ����û��������ʱ ���������Ƿ��ó�

//#define configSUPPORT_STATIC_ALLOCATION 1   //ʹ�þ�̬���� 
//#define configSUPPORT_DYNAMIC_ALLOCATION 1  //Ĭ��Ϊ1
#define  configUSE_TIMERS 1             //ʹ�ܶ�ʱ��
#define  configTIMER_TASK_PRIORITY 31   //�ػ���������ȼ��������ܸ�һ��  
#define  configTIMER_QUEUE_LENGTH  5    //������еĳ���
#define  configTIMER_TASK_STACK_DEPTH   32 //�ػ������ջ�Ĵ�С
/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 						0 //���ó�1��ʾʹ��Э�̣�0��ʾ��ʹ��Э�̡����ʹ��Э�̣������ڹ����а���croutine.c�ļ���
#define configMAX_CO_ROUTINE_PRIORITIES 	( 2 ) //Ӧ�ó���Э�̣�Co-routines������Ч���ȼ���Ŀ
#define configUSE_COUNTING_SEMAPHORES   1
//--------------------------------------------------------------------------------------
//�¼���������
//��������xEventGroupSetBitsFromISR����������������룬��Ҫ
//#define  configUSE_TRACE_FACILITY  1
//#define  INCLUDE_xTimerPendFunctionCall 1
//#define  configUSE_TIMERS 1
//#define configTIMER_TASK_PRIORITY    (configMAX_PRIORITIES-1)     //�����ʱ�����ȼ�
//#define configTIMER_QUEUE_LENGTH     5                            //�����ʱ�����г���
//#define configTIMER_TASK_STACK_DEPT  (configMINIMAL_STACK_SIZE*2) //�����ʱ�������ջ��С

#define INCLUDE_vTaskPrioritySet			1
#define INCLUDE_uxTaskPriorityGet			1
#define INCLUDE_vTaskDelete						1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend					1
#define INCLUDE_vTaskDelayUntil				1
#define INCLUDE_vTaskDelay						1

/* This is the raw value as per the Cortex-M3 NVIC.  Values can be 255
(lowest) to 0 (1?) (highest). */
#define configKERNEL_INTERRUPT_PRIORITY 		255
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	191 /* equivalent to 0xb0, or priority 11. */


/* This is the value being used as per the ST library which permits 16
priority values, 0 to 15.  This must correspond to the
configKERNEL_INTERRUPT_PRIORITY setting.  Here 15 corresponds to the lowest
NVIC value of 255. */
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	15

#endif /* FREERTOS_CONFIG_H */


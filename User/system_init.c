/*
 * system_init.c
 *
 *  Created on: May 8, 2024
 *      Author: i.dymov
 */
#include "system_init.h"
#include "hal_wdt.h"
#include "inputs.h"
#include "process.h"
#include "hal_rtc.h"
#include "debug.h"

static void StartDefaultTask(void *argument);
static StaticTask_t xIdleTaskTCB;
static StaticTask_t xTimerTaskTCB;
static StaticTask_t defaultTaskControlBlock;
static StaticTask_t CanOpneProccesTaskControlBlock;
static StaticTask_t CanOpnePeriodicTaskControlBlock;
static StaticTask_t ProcessTaskControlBlock;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];
static StackType_t defaultTaskBuffer[DEFAULT_TASK_STACK_SIZE];
static StackType_t CanOpneProccesTaskBuffer[CAN_OPEN_STK_SIZE ];
static StackType_t CanOpnePeriodicTaskBuffer[PERIODIC_CAN_STK_SIZE ];
static StackType_t ProcessTaskBuffer[ PROCESS_STK_SIZE ];
static TaskHandle_t DefautTask_Handler;
static StackType_t defaultTaskBuffer[DEFAULT_TASK_STACK_SIZE];
static StackType_t InputsTaskBuffer[INPUTS_TASK_STACK_SIZE];
static StaticTask_t defaultTaskControlBlock;
static StaticTask_t InputsTaskControlBlock;
static TaskHandle_t DefautTask_Handler;
static uint8_t ucQueueStorageArea[  16U * sizeof( EEPROM_REG_Q_t ) ];
static StaticQueue_t xStaticQueue;

/*
 * 妤快把快技快扶扶抑快
 */

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
   *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
   *ppxIdleTaskStackBuffer = uxIdleTaskStack;
   *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}


 void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
   *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
   *ppxTimerTaskStackBuffer = uxTimerTaskStack;
   *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
/*
 *
 */

void vSystemStop()
{
    vTaskSuspend(* xProcessTaskHandle ());
    vTaskSuspend( *xCanOpenPeriodicTaskHandle ());
    vTaskSuspend( *xCanOpenProcessTaskHandle());
}


INIT_FUNC_LOC  void vSYStaskInit ( void )
{
   (* xProcessTaskHandle ())
             = xTaskCreateStatic( vRedrawTask, "ProcessTask", PROCESS_STK_SIZE , ( void * ) 1, PROCESS_TASK_PRIO  ,
                                     (StackType_t * const )ProcessTaskBuffer, &ProcessTaskControlBlock );
  (* xCanOpenPeriodicTaskHandle ())
  = xTaskCreateStatic( vCanOpenPeriodicProcess, "CanOpenPeriodic", PERIODIC_CAN_STK_SIZE , ( void * ) 1, PERIODIC_CAN_TASK_PRIO ,
                     (StackType_t * const )CanOpnePeriodicTaskBuffer, &CanOpnePeriodicTaskControlBlock );
  (* xCanOpenProcessTaskHandle())
  = xTaskCreateStatic( vCanOpenProcess, "CanOpenProcessTask", CAN_OPEN_STK_SIZE , ( void * ) 1, CAN_OPEN_TASK_PRIO ,
  (StackType_t * const )CanOpneProccesTaskBuffer, &CanOpneProccesTaskControlBlock );
 (* getInputsTaskHandle()) =   xTaskCreateStatic( vInputsTask, "InputsTask", INPUTS_TASK_STACK_SIZE , ( void * ) 1, INPUT_TASK_PRIO, (StackType_t * const )InputsTaskBuffer, &InputsTaskControlBlock );
  DefautTask_Handler = xTaskCreateStatic( StartDefaultTask, "DefTask", DEFAULT_TASK_STACK_SIZE , ( void * ) 1, DEFAULT_TASK_PRIOR, (StackType_t * const )defaultTaskBuffer, &defaultTaskControlBlock );
  vSystemStop();
  vTaskSuspend(* getInputsTaskHandle());
  return;
}

INIT_FUNC_LOC void vSYSqueueInit ( void )
{
    *( xDataRegQueue()) = xQueueCreateStatic( 16U, sizeof( EEPROM_REG_Q_t ),ucQueueStorageArea, &xStaticQueue );;
}
/*----------------------------------------------------------------------------*/
void vSYSeventInit ( void )
{
 // *(osLUAetPDMstatusHandle () ) = xEventGroupCreateStatic(&xLuaStateEventGroup );
}




void StartDefaultTask(void *argument)
{
   uint8_t counter = 0;
   DataModel_Init();
   uint8_t test_mode =((getReg8(BITRATE_ADR ) & 0x80) == 0 )?0:1;
   vProceesInit();
   vTaskResume( *xCanOpenProcessTaskHandle());
   vTaskResume( *xCanOpenPeriodicTaskHandle ());
   vTaskResume(* xProcessTaskHandle ());
   vTaskDelay(100);
   vTaskResume(* getInputsTaskHandle());
   for(;;)
   {
      vTaskDelay(500);
      HAL_WDTReset();
      if (test_mode )
      {
          if (counter++ ==2)
          {
             printf("\r\n Sec =%d \r\n", DataModelGetSecCounter());
             for (uint8_t i=AIN1;i<=AIN3;i++)
             {
                  printf("ain%d R  %d \r\n",i,(uint16_t)GetAIN(i));
             }
             for (uint8_t i=AIN4;i<=AIN5;i++)
             {
                 printf("ain%d B*100 %d \r\n",i,(uint16_t)(GetAIN(i)*100));
             }
             for (uint8_t i = 0 ; i< 4;i++)
             printf("DIN%d =%d \r\n", i,InputsGetTest( i));
             counter = 0;
          }
      }
   }
  /* USER CODE END 5 */
}

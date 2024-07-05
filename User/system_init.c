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
static StaticTask_t xIdleTaskTCB                                     __SECTION(RAM_SECTION_CCMRAM);
static StaticTask_t xTimerTaskTCB                                    __SECTION(RAM_SECTION_CCMRAM);
static StaticTask_t defaultTaskControlBlock;
static StaticTask_t CanOpneProccesTaskControlBlock;
static StaticTask_t CanOpnePeriodicTaskControlBlock;

static StaticTask_t ProcessTaskControlBlock;

static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ]       __SECTION(RAM_SECTION_CCMRAM);
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ]  __SECTION(RAM_SECTION_CCMRAM);
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

void vSystemStopProcess()
{
   // vTaskSuspend(* xProcessTaskHandle ());
    vTaskSuspend( *xCanOpenPeriodicTaskHandle ());
    vTaskSuspend( *xCanOpenProcessTaskHandle());
}

void vSYStaskInit ( void )
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
  vSystemStopProcess();
  return;
}

void vSYSqueueInit ( void )
{
    *( xDataRegQueue()) = xQueueCreateStatic( 16U, sizeof( EEPROM_REG_Q_t ),ucQueueStorageArea, &xStaticQueue );;
}
/*----------------------------------------------------------------------------*/
void vSYSeventInit ( void )
{
 // *(osLUAetPDMstatusHandle () ) = xEventGroupCreateStatic(&xLuaStateEventGroup );
}


static  TaskFSM_t DeafaultTaskFSM = STATE_INIT;

void StartDefaultTask(void *argument)
{
  uint32_t ulNotifiedValue;
  for(;;)
  {
      switch( DeafaultTaskFSM)
      {
          case STATE_INIT:
              DataModel_Init();
              vLedDriverStart();
              InputsNotifyTaskToInit();
              RedrawNotifyTaskToInit();
              vProceesInit();
              DeafaultTaskFSM = STATE_WHAIT_TO_RAEDY;
              break;
          case STATE_WHAIT_TO_RAEDY:
              xTaskNotifyWait(0, 0, &ulNotifiedValue,portMAX_DELAY);
              if ( ulNotifiedValue == 2)
              {
                  ulTaskNotifyValueClearIndexed(0, 0, 0xFFFF);
                  vTaskResume( *xCanOpenProcessTaskHandle());
                  vTaskResume( *xCanOpenPeriodicTaskHandle ());
                  DeafaultTaskFSM = STATE_RUN;
              }
              break;
          case STATE_RUN:
              vTaskDelay(500);
            // printf("SystemClk\r\n");

              HAL_WDTReset();
              break;
      }
  }
  /* USER CODE END 5 */
}

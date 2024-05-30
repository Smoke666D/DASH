/*
 * system_init.c
 *
 *  Created on: May 8, 2024
 *      Author: i.dymov
 */
#include "system_init.h"
#include "hal_wdt.h"
#include "inputs.h"
#include "portmacro.h"




static void StartDefaultTask(void *argument);
static StaticTask_t xIdleTaskTCB                                     __SECTION(RAM_SECTION_CCMRAM);
static StaticTask_t xTimerTaskTCB                                    __SECTION(RAM_SECTION_CCMRAM);
static StaticTask_t defaultTaskControlBlock;
static StaticTask_t CanOpneProccesTaskControlBlock;
static StaticTask_t CanOpnePeriodicTaskControlBlock;
static StaticTask_t KeyboardTaskControlBlock;
static StaticTask_t ProcessTaskControlBlock;

static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ]       __SECTION(RAM_SECTION_CCMRAM);
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ]  __SECTION(RAM_SECTION_CCMRAM);
static StackType_t defaultTaskBuffer[DEFAULT_TASK_STACK_SIZE];
static StackType_t CanOpneProccesTaskBuffer[CAN_OPEN_STK_SIZE ];
static StackType_t CanOpnePeriodicTaskBuffer[PERIODIC_CAN_STK_SIZE ];
static StackType_t KeyboardTaskBuffer[KEYBOARD_STK_SIZE ];
static StackType_t ProcessTaskBuffer[ PROCESS_STK_SIZE ];
static TaskHandle_t DefautTask_Handler;
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
static TaskHandle_t DefautTask_Handler;
static StackType_t defaultTaskBuffer[DEFAULT_TASK_STACK_SIZE];
static StackType_t InputsTaskBuffer[INPUTS_TASK_STACK_SIZE];
static StaticTask_t defaultTaskControlBlock;
static StaticTask_t InputsTaskControlBlock;


/*


   xTaskCreate((TaskFunction_t )vKeyboardTask,
                       (const char*    )"Keyboard",
                       (uint16_t       )DRAW_STK_SIZE,
                       (void*          )NULL,
                       (UBaseType_t    )DRAW_TASK_PRIO,
                       (TaskHandle_t*  )&DrawHandle);

*/

void vSYStaskInit ( void )
{
   (* xProcessTaskHandle ())
             = xTaskCreateStatic( vRedrawTask, "ProcessTask", PROCESS_STK_SIZE , ( void * ) 1, PROCESS_TASK_PRIO  ,
                                     (StackType_t * const )ProcessTaskBuffer, &ProcessTaskControlBlock );
  /*(* xCanOpenPeriodicTaskHandle ())
  = xTaskCreateStatic( vCanOpenPeriodicProcess, "CanOpenPeriodic", PERIODIC_CAN_STK_SIZE , ( void * ) 1, PERIODIC_CAN_TASK_PRIO ,
                     (StackType_t * const )CanOpnePeriodicTaskBuffer, &CanOpnePeriodicTaskControlBlock );
  (* xCanOpenProcessTaskHandle())
  = xTaskCreateStatic( vCanOpenProcess, "CanOpenProcessTask", CAN_OPEN_STK_SIZE , ( void * ) 1, CAN_OPEN_TASK_PRIO ,
  (StackType_t * const )CanOpneProccesTaskBuffer, &CanOpneProccesTaskControlBlock );*/
  (* getInputsTaskHandle()) =   xTaskCreateStatic( vInputsTask, "InputsTask", INPUTS_TASK_STACK_SIZE , ( void * ) 1, 3, (StackType_t * const )InputsTaskBuffer, &InputsTaskControlBlock );
  DefautTask_Handler = xTaskCreateStatic( StartDefaultTask, "DefTask", DEFAULT_TASK_STACK_SIZE , ( void * ) 1, 3, (StackType_t * const )defaultTaskBuffer, &defaultTaskControlBlock );
  return;
}

void vSYSqueueInit ( void )
{
//  *( pCANRXgetQueue() ) = xQueueCreate( CANRX_QUEUE_SIZE, sizeof( CAN_FRAME_TYPE));
  //*( pCANTXgetQueue() ) = xQueueCreate( CANTX_QUEUE_SIZE, sizeof( CAN_TX_FRAME_TYPE ) );
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
    uint16_t dd = 0;
    u16 i= 0;
  /* USER CODE BEGIN 5 */
  /* Infinite loop */

 // vProceesInit();

  //xEventGroupSetBits( xResetEventHandle, RESTART_DISABLE);
  for(;;)
  {
      switch( DeafaultTaskFSM)
      {
          case STATE_INIT:
              DataModel_Init();
               setReg16(BAR_VALUE_HIGH        ,360);
               setReg16(BAR_VALUE_LOW         ,0);
               setReg16(BAR_VALUE_RED_HIGH    ,150);
               setReg16(BAR_VALUE_RED_LOW     ,230);
               setReg16(BAR_VALUE_GREEN_HIGH  ,270);
               setReg16(BAR_VALUE_GREEN_LOW   ,110);
               setReg8(BAR_MODE   ,1);

               setReg16(RGB5_VALUE_GREEN_HIGH       ,190);
               setReg16(RGB5_VALUE_GREEN_LOW        ,110);
               setReg16(RGB5_VALUE_RED_HIGH        ,100);
               setReg16(RGB5_VALUE_RED_LOW         ,200);
               setReg16(RGB5_VALUE_BLUE_HIGH       ,0);
               setReg16(RGB5_VALUE_BLUE_LOW        ,0);
               setReg8(RGBMAP5   ,1);

               setReg16(RGB9_VALUE_GREEN_HIGH       ,190);
               setReg16(RGB9_VALUE_GREEN_LOW        ,110);
               setReg16(RGB9_VALUE_RED_HIGH        ,100);
               setReg16(RGB9_VALUE_RED_LOW         ,200);
               setReg16(RGB9_VALUE_BLUE_HIGH       ,0);
               setReg16(RGB9_VALUE_BLUE_LOW        ,0);
               setReg8(RGBMAP9   ,1);


               setReg16(RGB14_VALUE_GREEN_HIGH       ,190);
               setReg16(RGB14_VALUE_GREEN_LOW        ,110);
               setReg16(RGB14_VALUE_RED_HIGH        ,100);
                              setReg16(RGB14_VALUE_RED_LOW         ,200);
                              setReg16(RGB14_VALUE_BLUE_HIGH       ,0);
                              setReg16(RGB14_VALUE_BLUE_LOW        ,0);
                              setReg8(RGBMAP14   ,1);


               setReg8(RGBMAP13, 0);
             //  setReg8(RGBMAP14, 0);
           //   xTaskNotifyWait(0, pdTRUE, &ulNotifiedValue,portMAX_DELAY);
              vLedDriverStart();
              InputsNotifyTaskToInit();
              DeafaultTaskFSM = STATE_WHAIT_TO_RAEDY;
              break;
          case STATE_WHAIT_TO_RAEDY:
              xTaskNotifyWait(0, 0, &ulNotifiedValue,portMAX_DELAY);
              if ( ulNotifiedValue == 1)
              {
                  ulTaskNotifyValueClearIndexed(0, 0, 0xFFFF);
                  DeafaultTaskFSM = STATE_RUN;
              }
              break;
          case STATE_RUN:
              setReg(BIG_SEG,&dd,2);
              setReg8( V1, i);
              vTaskDelay(500);
              if (++dd>9) dd = 0;
              i= i+10;
              if (i >=370) i = 0;

              HAL_WDTReset();
              printf("We alive!!\r\n");
              break;
      }
  }
  /* USER CODE END 5 */
}

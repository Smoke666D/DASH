/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *task1 and task2 alternate printing
 */

#include "main.h"
#include "process.h"
#include "HW_API.h"
#include "system_init.h"




/* Global Variable */
TaskHandle_t KeyboardTaskHandle;


TaskHandle_t DrawHandle;
TaskHandle_t LedHandle;


void vKeyboardTask(void *argument);


EventGroupHandle_t xResetEventHandle;
StaticEventGroup_t xCreatedEventGroup;
EventGroupHandle_t xSystemEventHandle;

EventGroupHandle_t xGetSystemEventHeandler()
{
    return (xSystemEventHandle);
}
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("Start\n");
    vInit_DeviceConfig( );
   // xSystemEventHandle  = xEventGroupCreate(  );
   // InitDataModel();
   // vLedDriverStart();
  //  vCanOpenInit(CAN1);
    vSYSeventInit ();
    vSYSqueueInit ();
    vSYStaskInit ( );
    vTaskStartScheduler();
    while(1)
    {
        printf("shouldn't run at here!!\n");
    }
}




void vKeyboardTask(void *argument)
{
   vSetupKeyboard();
   for (;;)
   {
      KeyBoardProcess();
   }
}


void vRestartNode( void )
{
    xEventGroupClearBitsFromISR(xResetEventHandle,RESTART_DISABLE);
    return;
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


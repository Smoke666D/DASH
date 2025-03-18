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

#include "system_init.h"
#include "debug.h"

/* Global Variable */
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    SystemCoreClockUpdate();    //§ª§ß§Ú§è§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ §ä§Ñ§Ü§ä§Ú§â§à§Ó§Ñ§ß§Ú§ñ
    Delay_Init();               //§ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ §ã§Ú§ã§ä§Ö§Þ§ß§à§Ô§à §ä§Ñ§Û§Þ§Ö§â§Ñ,§Ú§ã§á§à§Ý§î§Ù§å§Ö§ä§ã§ñ §Õ§Ý§ñ §â§Ñ§ã§é§Ö§ä§Ñ §Ù§Ñ§Õ§Ö§â§Ø§Ö §Ú §ä§Ñ§Û§Þ§Ñ§å§ä§à§Ó
                                //§Ó §æ§å§ß§Ü§è§Ú§Ú §Ú§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§Ú §á§Ö§â§Ö§æ§Ú§â§Ú§Ú. §±§à§ã§Ý§Ö §ï§ä§à§Ô§à §à§ß §Ú§ã§á§à§Ý§î§Ù§å§Ö§ä§ã§ñ §Õ§Ý§ñ §ä§Ñ§Ü§ä§Ú§â§à§Ó§Ñ§ß§Ú§ñ §°§³
    vInit_DeviceConfig( );      //§ª§ß§Ú§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ §á§Ö§â§Ö§æ§Ú§â§Ú§Ú
    USART_Printf_Init(115200);  //§ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ §à§ä§Õ§Ñ§Ý§à§é§ß§à§Ô§à §Ó§í§Ó§à§Õ§Ñ
    printf("SystemClk:%d\r\n", SystemCoreClock);
    vSYSqueueInit (  );         // §ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ñ§Ù§è§Ú§ñ §à§é§Ö§â§Ö§Õ§Ö§Û §à§ã.
    vSYStaskInit ( );           // §ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ §á§â§à§è§Ö§ã§ã§à§Ó §°§³
    vTaskStartScheduler();      // §³§ä§Ñ§â§ä §°§³.
    while(1);
}






void vRestartNode( void )
{

    return;
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  printf("Memory error!\r\n");
  while (1)
  {

  }
  /* USER CODE END Error_Handler_Debug */
}



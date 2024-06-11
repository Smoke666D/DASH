/*
 * keyboard_task.c
 *
 *  Created on: May 30, 2024
 *      Author: i.dymov
 */


#include "keyboard_task.h"
#include "HW_API.h"


static TaskHandle_t  pKeybardTaskHandle ;
static uint8_t  STATUS[KEY_COUNT];
static uint8_t  COUNTERS[KEY_COUNT];

TaskHandle_t * xKeyboardProcessTaskHandle ()
{
    return  &pKeybardTaskHandle ;
}


BitState_t fPortState (uint8_t i)
{

     return HAL_GetBit( Din3_4_5_Port ,Din4_Pin );

}
/*
 *
 *
 */
/*void vInitKeybord()
{
    KeybaordStruct_t KeyboardInit;
    KeyboardInit.KEYBOARD_COUNT    = KEY_COUNT;
    KeyboardInit.COUNTERS          = COUNTERS;
    KeyboardInit.STATUS            = STATUS;
    KeyboardInit.REPEAT_TIME       = 10;
    KeyboardInit.KEYDOWN_HOLD_TIME = 20 ;
    KeyboardInit.KEYDOWN_DELAY     = 4;
    KeyboardInit.KEYBOARD_PERIOD   = 10;
    KeyboardInit.getPortCallback = &fPortState;
    eKeyboardInit(&KeyboardInit);
}
*/
/*
void vKeyboardTask( void * argument )
{
  vInitKeybord();
  for(;;)
  {
    vTaskDelay( HW_LIB_GetKeyboardPeriod() );
    HW_LIB_KeyboradFSM();
  }
}
*/

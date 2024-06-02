/*
 * keyboard_task.h
 *
 *  Created on: May 30, 2024
 *      Author: i.dymov
 */

#ifndef USER_KEYBOARD_TASK_H_
#define USER_KEYBOARD_TASK_H_


#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "string.h"
#include "event_groups.h"
#include "system_init.h"
#include "hw_lib_keyboard.h"
#include "hal_gpio.h"

TaskHandle_t * xKeyboardProcessTaskHandle ();
void          vKeyboardTask( void  * argument );

#endif /* USER_KEYBOARD_TASK_H_ */

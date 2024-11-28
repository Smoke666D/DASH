/*
 * main.h
 *
 *  Created on: Feb 16, 2024
 *      Author: i.dymov
 */

#ifndef USER_MAIN_H_
#define USER_MAIN_H_


#include <inputs.h>
#include "string.h"
#include "debug.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "dash_draw.h"
#include "semphr.h"
#include "CO_driver_ST32F103.h"
#include "CanOpenNode.h"
#include "led.h"
#include "stdlib.h"
#include "init.h"

#include "DataModel.h"
#include "inputs.h"
#include "DataModel.h"

#define WCH32V3   2
#define WCH32V2   1

#define CORE WCH32V2


/***************************watchdog***************************/
//§¡§Ü§ä§Ú§Ó§Ú§â§à§Ó§Ñ§ä§î §Ó§Ñ§ä§é§Õ§à§Ô
#define WDT_ENABLE
/****************************RTC**************************/
#define RTC_IRQ_ENABLE
/************************I2C************************************/
#define I2C1_IT_ENABLE
//#define I2C2_IT_ENABLE

#define INIT_FUNC_LOC //__attribute__((section(".stext")))
#define RESTART_DISABLE  0x0001
#define DATA_MODEL_READY 0x02
#define IGNITON_FLAG    0x08
#define SPI1_READY      0x10
#define SPI2_READY      0x20
#define KEYBOARD_START  0x40

void vRestartNode( void );
void Error_Handler(void);


#endif /* USER_MAIN_H_ */

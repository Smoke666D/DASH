/*
 * keyboard.h
 *
 *  Created on: 25 февр. 2020 г.
 *      Author: igor.dymov
 */

#ifndef INC_INPUTS_H_
#define INC_INPUTS_H_
/*----------------------- Includes -------------------------------------*/
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#include "filters.h"




#define ADC1_DATA_READY 0x01

#define AIN_NUMBER       5
#define ADC1_CHANNELS    5
#define ADC2_CHANNELS    0
#define ADC3_CHANNELS    0
#define ADC_CHANNEL      AIN_NUMBER


#include "hw_lib_adc.h"

#define RR  300.0


#define RA  10000.0
/*----------------------------- Functions ------------------------------------*/
TaskHandle_t * getInputsTaskHandle();
void vInputsTask( void * argument );
void InputsNotifyTaskToStop();
void InputsNotifyTaskToInit();


/*----------------------------------------------------------------------------*/
#endif /* INC_KEYBOARD_H_ */

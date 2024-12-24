/*
 * keyboard.h
 *
 *  Created on: 25 февр. 2020 г.
 *      Author: igor.dymov
 */

#ifndef INC_INPUTS_H_
#define INC_INPUTS_H_
/*----------------------- Includes -------------------------------------*/
#include "system_init.h"
#include "main.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "list.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
//#include "hw_lib_adc.h"




#define ADC1_DATA_READY 0x01


#define DAC_NUMBER       0
#define AIN_NUMBER       5
#define ADC1_CHANNELS    5
#define ADC2_CHANNELS    0
#define ADC3_CHANNELS    0
#define ADC_CHANNEL      AIN_NUMBER




#define RR  300.0


typedef enum
{
    START_UP_STATE,
    RUN_STATE_INIT,
    RUN_STATE,
    SAVE_STATE,
} INPUTS_FSM_t;

#define RA  10000.0
#define R22 15000.0
#define R21 10000.0
#define VADD_COOF ((R21+R22)/R22)
#define Rgnd  15000.0
#define Rup   10000.0
#define Rpup  3000.0
#define RpupAIN3  500.0
#define AIN_COOF   ((Rup+Rgnd)/Rgnd)
#define DIOD    0.2
/*----------------------------- Functions ------------------------------------*/
TaskHandle_t * getInputsTaskHandle();
void vInputsTask( void * argument );
void InputsNotifyTaskToStop();
void InputsNotifyTaskToInit();
float GetAIN(u8 ch);

/*----------------------------------------------------------------------------*/
#endif /* INC_KEYBOARD_H_ */

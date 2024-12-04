/*
 * system_init.h
 *
 *  Created on: May 8, 2024
 *      Author: i.dymov
 */

#ifndef USER_SYSTEM_INIT_H_
#define USER_SYSTEM_INIT_H_

#include "main.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "list.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#include "portmacro.h"
#include "stdbool.h"

#define __SECTION(x)


#define DEFAULT_TASK_STACK_SIZE         128U
#define INPUTS_TASK_STACK_SIZE          256U
#define DEFAULT_TASK_STACK_SIZE         128U
#define CAN_OPEN_TASK_PRIO              5
#define INPUT_TASK_PRIO                 8
#define DEFAULT_TASK_PRIOR              9
#define CAN_OPEN_STK_SIZE               800
#define PERIODIC_CAN_TASK_PRIO          4
#define PERIODIC_CAN_STK_SIZE           256
#define PROCESS_TASK_PRIO               6  //§¥§°§­§¨§¦§¯ §¢§½§´§¾ §³§¡§®§½ §£§½§³§°§¬§ª§«
#define PROCESS_STK_SIZE                256


#define TASK_RUN_NOTIFY    0x01
#define TASK_STOP_NOTIFY   0x02
#define TASK_INIT_NOTIFY   0x04
#define INPUTS_DRIVER_READY   0x08
#define AIN_DRIVER_READY   0x10
#define ADC2_READY         0x20
#define ADC3_READY         0x40
#define ADC1_READY         0x80



typedef enum
{
    STATE_INIT,
    STATE_IDLE,
    STATE_RUN,
    STATE_WHAIT_TO_RAEDY,
    STATE_SAVE_DATA,
    STATE_TEST,
} TaskFSM_t;

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize );

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize );
void vSystemStopProcess();
void vSYStaskInit ( void );
void vSYSqueueInit ( void );
void vSYSeventInit ( void );
void vSystemStop();
#endif /* USER_SYSTEM_INIT_H_ */

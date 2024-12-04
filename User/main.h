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


#define WCH32V3   2
#define WCH32V2   1

#define ADC_Port            PORT_A
#define ADC0_Pin            GPIO_0
#define ADC1_Pin            GPIO_1
#define ADC2_Pin            GPIO_2
#define ADC3_Pin            GPIO_3
#define SPI1_Port           PORT_A
#define SPI1_NSS_Pin        GPIO_4
#define SPI1_SCK_Pin        GPIO_5
#define ADC6_Pin            GPIO_6
#define SPI1_MOSI_Pin       GPIO_7
#define nOE_Port           PORT_B
#define nOE1_Pin            GPIO_0
#define nOE2_Pin            GPIO_1
#define Din3_4_5_Port       PORT_B
#define Din3_Pin            GPIO_10
#define Din4_Pin            GPIO_11
#define SPI2_NSS_Pin        GPIO_12
#define SPI2_Port           PORT_B
#define SPI2_SCK_Pin        GPIO_13
#define SPI2_MOSI_Pin       GPIO_15
#define UARTTX_Port         PORT_A
#define UARTTX_Pin          GPIO_9
#define Din1_Port           PORT_A
#define Din1_Pin            GPIO_11
#define Din2_Port           PORT_B
#define Din2_Pin            GPIO_3
#define PowerOn_Port        PORT_B
#define PowerOn_Pin         GPIO_4
#define Din5_Pin            GPIO_5
#define I2C1_Port          PORT_B
#define I2C1_SCL_Pin       GPIO_6
#define I2C1_SDA_Pin       GPIO_7
#define CAN_Port            PORT_B
#define CAN_RX_Pin          GPIO_8
#define CAN_TX_Pin          GPIO_9


#define CORE WCH32V2


#define DEF_H_FRONT 10U
#define DEF_L_FRONT 10U
#define RPM_CHANNEL_COUNT     2
#define DIN_CHANNEL_COUNT     2
#define DIN_COUNT            ( RPM_CHANNEL_COUNT + DIN_CHANNEL_COUNT )

#define DOUT_COUNT            1

/***************************watchdog***************************/
//§¡§Ü§ä§Ú§Ó§Ú§â§à§Ó§Ñ§ä§î §Ó§Ñ§ä§é§Õ§à§Ô
//#define WDT_ENABLE
/****************************RTC**************************/
#define RTC_IRQ_ENABLE
/************************I2C************************************/
#define I2C1_ENABLE
#define I2C1_IT_ENABLE
//#define I2C2_IT_ENABLE

#define INIT_FUNC_LOC __attribute__((section(".stext")))
#define RESTART_DISABLE  0x0001
#define DATA_MODEL_READY 0x02
#define IGNITON_FLAG    0x08
#define SPI1_READY      0x10
#define SPI2_READY      0x20
#define KEYBOARD_START  0x40

void vRestartNode( void );
void Error_Handler(void);


#endif /* USER_MAIN_H_ */

/*
 * drivers_config.h
 *
 *  Created on: May 8, 2024
 *      Author: i.dymov
 */

#ifndef DRIVERS_DRIVERS_CONFIG_H_
#define DRIVERS_DRIVERS_CONFIG_H_

#include "hal_config.h"

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

#define DEF_H_FRONT 10U
#define DEF_L_FRONT 10U
#define RPM_CHANNEL_COUNT     2
#define DIN_CHANNEL_COUNT     2
#define DIN_COUNT            ( RPM_CHANNEL_COUNT + DIN_CHANNEL_COUNT )

#define DOUT_COUNT            1


#endif /* DRIVERS_DRIVERS_CONFIG_H_ */

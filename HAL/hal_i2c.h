/*
 * hal_i2c.h
 *
 *  Created on: 20 апр. 2024 г.
 *      Author: i.dymov
 */

#ifndef HAL_HAL_I2C_H_
#define HAL_HAL_I2C_H_

#include "main.h"
#include "system_init.h"
#include "hal_config.h"



#if MCU == APM32
#include "apm32f4xx_i2c.h"

#endif


typedef enum
{
  I2C_IDLE   		= 0,
  I2C_MASTER_RECIVE_START  = 1,
  I2C_MASTER_RECIVE_WRITE_ADDR =2,
  I2C_MASTER_RECIVE_WRITE_ADDR2 = 11,
  I2C_MASTER_RECIVE_DA_WRITE = 3,
  I2C_MASTER_RECIVE_ADDR = 4,
  I2C_MASTER_RECIVE_MODE = 5,
  I2C_MASTER_RECIEVE 	 = 6,
  I2C_MASTER_TRANSMIT_START  = 7,
  I2C_MASTER_TRANSMIT_ADDR = 8,
  I2C_MASTER_TRANSMIT_ADDR2 = 12,
  I2C_MASTER_TRANSMIT_NEXT  = 9,
  I2C_MASTER_TRANSMIT_LAST = 10,

} I2C_STATE_t;

#define MODE_DMA 1
#define MODE_IT  2

#define MODE_I2C  MODE_IT


#if MCU == APM32
#define I2C_1  I2C1
#define I2C_2  I2C2
#define  I2C_NAME_t I2C_T*
#endif
#if MCU == CH32V2
#define I2C_1  I2C1
#define I2C_2  I2C2
#define I2C_NAME_t I2C_TypeDef *

#define STAR1_SB_FLAG     0x0001
#define STAR1_ADDR_FLAG   0x0002
#define STAR1_BTF_FLAG    0x0004
#define STAR1_TXE_FLAG    0x0080
#define STAR2_BUSY_FLAG   0x0002
#endif

void InitI2CDMA( I2C_NAME_t i2c, uint8_t prior, uint8_t subprior);
void I2C1_EV_IRQHandler( void );
void I2C1_ER_IRQHandler ( void );
void I2C2_EV_IRQHandler( void );
void I2C2_ER_IRQHandler ( void );
void DMA1_STR3_IRQHandler( void );
void DMA1_STR7_IRQHandler( void );

#endif /* HAL_HAL_I2C_H_ */

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




#define MODE_DMA 1
#define MODE_IT  2

#define MODE_I2C  MODE_IT


#if MCU == APM32
#define I2C_1  I2C1
#define I2C_2  I2C2
#define  I2C_NAME_t I2C_T*
#endif
#if MCU == CH32V2

typedef enum
      {
    I2C_1  =0,
    I2C_2  =1,
      }
 I2C_NAME_t;
/*#define I2C_1  I2C1
#define I2C_2  I2C2
#define I2C_NAME_t I2C_TypeDef *
*/

 typedef struct
 {
   void (* datacallback) ( void );
   void (* errorcallback)(void );
 } HAL_I2C_t;

#define STAR1_SB_FLAG     0x0001
#define STAR1_ADDR_FLAG   0x0002
#define STAR1_BTF_FLAG    0x0004
#define STAR1_TXE_FLAG    0x0080
#define STAR2_BUSY_FLAG   0x0002
#endif




#include "main.h"



#if  CORE == APM32
#include "apm32f4xx_i2c.h"
#define I2C_T I2C_T
#define  DIR_TRANSMIT     I2C_DIRECTION_TX
#define  DIR_RECIEVE      I2C_DIRECTION_RX

#endif
#if  CORE == WCH32V2

#define  DIR_TRANSMIT I2C_Direction_Transmitter
#define  DIR_RECIEVE  I2C_Direction_Receiver

#endif














 void  HAL_I2C_SEND_ADDR_TRANS(I2C_NAME_t i2c,  u8 DATA) ;
 void  HAL_I2C_SEND_ADDR_RECIEVE(I2C_NAME_t i2c,  u8 DATA);
 void HAL_I2C_ClearFlag( I2C_NAME_t i2c , uint32_t flag);
uint16_t HAL_I2C_GET_STAR2(I2C_NAME_t i2c );
uint16_t HAL_I2C_GET_STAR1(I2C_NAME_t i2c );
void HAL_I2C_ENABLE( I2C_NAME_t i2c ) ;
void HAL_I2C_DISABLE( I2C_NAME_t i2c );
void I2C_IT_ENABLE( I2C_NAME_t i2c , u16 DATA );
void I2C_IT_DISABLE(I2C_NAME_t i2c , u16 DATA );
void HAL_I2C_STOP(I2C_NAME_t i2c );
void HAL_I2C_START(I2C_NAME_t i2c );
void HAL_I2C_ACK_DISABLE(I2C_NAME_t i2c ) ;
void HAL_I2C_SEND( I2C_NAME_t i2c, u8 DATA);
void HAL_I2C_ACK_ENABLE(I2C_NAME_t i2c ) ;
u16  HAL_I2C_READ_DATA();
void InitI2CIT( I2C_NAME_t i2c, uint8_t prior, uint8_t subprior, void (* fdata) ( void ), void (* ferror) ( void ));
void I2C1_EV_IRQHandler( void );
void I2C1_ER_IRQHandler ( void );
void I2C2_EV_IRQHandler( void );
void I2C2_ER_IRQHandler ( void );
void DMA1_STR3_IRQHandler( void );
void DMA1_STR7_IRQHandler( void );

#endif /* HAL_HAL_I2C_H_ */

/*
 * led.h
 *
 *  Created on: Nov 12, 2021
 *      Author: igor.dymov
 */

#ifndef INC_LED_H_
#define INC_LED_H_


#include "main.h"
#include "types.h"
//#include "stm32f1xx_hal.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "semphr.h"



#define MAX_BRIGTH  15



#define BUTTON_COUNT 8

#define  MAX_DATA 0xFF
#define  MAX_BRIGTH_COUNTER    150//MAX_BRIGTH *2
#define  OFF 0x00

#define LATCH_DEALY 	100U
#define SPI_PACKET_SIZE 3U
#define SPI_TIMEOUT		100U

#define SPI1_CHIP_COUNT     5
#define SPI2_CHIP_COUNT     4

#define BAR_GREEN_WORD   0
#define BAR_RED_WORD     1
#define RGB_BLUE_WORD    2
#define RGB_GREEN_WORD   3
#define RGB_RED_WOED     4


#define RED		     0x01
#define GREEN	     0x02
#define BLUE	     0x03
#define YELLOW       0x04
#define CYAN		 0x05
#define VIOLET		 0x06
#define WHITE		 0x07
#define AMBER        0x08
#define YELLOW_GREEN 0x09


#define SET_LED_ON_RED		0x01
#define SET_LED_ON_GREEN	0x02
#define SET_LED_ON_BLUE 	0x03
#define SET_LED_BLINK_RED	0x04
#define SET_LED_BLINK_GREEN	0x05
#define SET_LED_BLINK_BLUE 	0x06

extern const u8 DigitMask[];
void SetSegPoint( u8 on);
void SetSegDirect( u8 number, u8 mask);
void SetSEG( u16 mask, u32 value, u8 point);
void vSetInitBrigth(BRIGTH_CHANNEL_t ch, u8 brigth);
void vSetBrigth( BRIGTH_CHANNEL_t ch, u8 brigth);
void SetBigSeg( u16 mask);
void SetBarState( u8 start_g, u8 count_g, u8 start_r, u8 count_r );
void SetRGB(  u8 number, LED_COLOR_t color, LED_STATE_t state);
void vRGBProcess();
void vLedDriverStart(void);
void vLedProcess( void );
#endif /* INC_LED_H_ */

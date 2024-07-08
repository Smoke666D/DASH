/*
 * hal_dma.h
 *
 *  Created on: 25
 *      Author: i.dymov
 */

#ifndef HAL_HAL_DMA_H_
#define HAL_HAL_DMA_H_

#include "main.h"
#include "hal_config.h"
#include "system_init.h"


#if MCU == APM32
#define DMA_Stram_t DMA_Stream_T*
#define DMA2_CH0  	DMA2_Stream0
#define DMA2_CH1  	DMA2_Stream1
#define DMA2_CH2  	DMA2_Stream2
#define DMA2_CH3  	DMA2_Stream3
#define DMA2_CH4  	DMA2_Stream4
#define DMA2_CH5  	DMA2_Stream5
#define DMA2_CH6  	DMA2_Stream6
#define DMA2_CH7  	DMA2_Stream7
#define DMA2_CH8  	DMA2_Stream8
#endif
#if MCU == CH32V2
typedef enum
{
    DMA1_CH1 =0,
    DMA1_CH2 =1,
    DMA1_CH3 =2,
    DMA1_CH4 =3,
    DMA1_CH5 =4,
    DMA1_CH6 =5,
    DMA1_CH7 =6,
}
DMA_Stram_t;
#endif

typedef enum
{
  PTOM,
  MTOP,
} DMA_Derection_t;

typedef enum
{
  DMA_BYTE,
  DMA_HWORD,
  DMA_WORD,
} DMA_Size_t;


typedef enum
{
    DMA_CH_0,  /*!< Select DMA channel 0 */
    DMA_CH_1,  /*!< Select DMA channel 1 */
    DMA_CH_2,  /*!< Select DMA channel 2 */
    DMA_CH_3,  /*!< Select DMA channel 3 */
    DMA_CH_4,  /*!< Select DMA channel 4 */
    DMA_CH_5,  /*!< Select DMA channel 5 */
    DMA_CH_6,  /*!< Select DMA channel 6 */
    DMA_CH_7   /*!< Select DMA channel 7 */
} DMA_CHANNEL_t;


typedef struct
{
	void (* CallBack)( void );

} DMA_CFG_t;

#if MCU == CH32V2
void HAL_DMAInitIT( DMA_Stram_t stream , DMA_Derection_t direction, DMA_Size_t dma_size, uint32_t paddr, uint32_t memadr,  uint8_t prior, uint8_t subprior, void (*f)(void));
void HAL_DMA_SetCouterAndEnable(DMA_Stram_t stream, uint32_t counter );
void HAL_DMA_Enable(DMA_Stram_t stream  );
void HAL_DMA_Disable(DMA_Stram_t stream  );
void HAL_DMA_SetCounter( DMA_Stram_t stream, uint32_t counter );
void HAL_DMA_ITENABLE( DMA_Stram_t stream, uint32_t it );
#endif
#if MCU == APM32
void DMA2_STR4_IRQHandler( void );
void DMA2_STR2_IRQHandler( void );
void DMA2_STR0_IRQHandler( void );
void HAL_DMAInitIT( DMA_Stram_t stream , DMA_Derection_t direction, DMA_Size_t dma_size, uint32_t paddr, uint32_t memadr, DMA_CHANNEL_t channel, uint8_t prior, uint8_t subprior, void (*f)(void));
#endif

#endif /* HAL_HAL_DMA_H_ */

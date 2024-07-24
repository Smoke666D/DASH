/*
 * HAL_SPI.c
 *
 *  Created on: 14 灞戦偑瑜� 2024 璋�.
 *      Author: i.dymov
 */


#include "hal_spi.h"

#if MCU == CH32V2

SPI_TypeDef * SPI[] ={SPI1,SPI2};

#define CTLR1_SPE_Set         ((uint16_t)0x0040)
    #define CTLR1_SPE_Reset       ((uint16_t)0xFFBF)
    /* SPI registers Masks */
    #define CTLR1_CLEAR_Mask      ((uint16_t)0x3040)
    #define I2SCFGR_CLEAR_Mask    ((uint16_t)0xF040)

void HAL_SPI_InitDMA(HAL_SPI_t spi , SPI_DATA_Size_t data_size )
{
    SPI_TypeDef * SPI_;
    if ( spi == HAL_SPI1)
    {
    	SPI_ = SPI1;
    	RCC->APB2PRSTR |= RCC_APB2Periph_SPI1;
    	RCC->APB2PRSTR &= ~RCC_APB2Periph_SPI1;
    	RCC->APB2PCENR |= RCC_APB2Periph_SPI1;
   }
   else
   {
    	 SPI_ = SPI2;
    	 RCC->APB1PRSTR |= RCC_APB1Periph_SPI2;
    	 RCC->APB1PRSTR &= ~RCC_APB1Periph_SPI2;
    	 RCC->APB1PCENR |= RCC_APB1Periph_SPI2;
   }
	u16 SPI_DataSize = ( data_size == SPI_8bit) ? SPI_DataSize_8b : SPI_DataSize_16b;
    uint16_t tmpreg = 0;
    tmpreg = SPI_->CTLR1;
    tmpreg &= CTLR1_CLEAR_Mask;
    tmpreg |= (uint16_t)((uint32_t)SPI_Direction_1Line_Tx | SPI_Mode_Master |
                             SPI_DataSize | SPI_CPOL_Low |
                             SPI_CPHA_1Edge | SPI_NSS_Soft |
                             SPI_BaudRatePrescaler_4 | SPI_FirstBit_MSB );

    SPI_->CTLR1 = tmpreg;
    SPI_->I2SCFGR &= SPI_Mode_Master;
    SPI_->CRCR = 0;
    SPI_->CTLR2 |= SPI_I2S_DMAReq_Tx;
    SPI_->CTLR1 |= CTLR1_SPE_Set;


}

void HAL_SPI_RXOveleyClear(HAL_SPI_t spi )
{

    SPI[spi]->STATR = (uint16_t)~SPI_I2S_FLAG_OVR;


}

uint8_t HAL_SPI_GetBusy(HAL_SPI_t spi )
{
	return (((SPI[spi]->STATR & SPI_I2S_FLAG_BSY) == SET) ? HAL_SET : HAL_RESET);

}

#endif

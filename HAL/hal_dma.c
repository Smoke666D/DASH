/*
 * hal_dma.c
 *
 *  Created on: 25 апр. 2024 г.
 *      Author: i.dymov
 */

#include "hal_dma.h"
#if MCU == APM32
	#include "apm32f4xx_dma.h"
	#include "apm32f4xx_rcm.h"
	#include "apm32f4xx_adc.h"
#endif
#if MCU == CH32V2
    #include "ch32v20x_dma.h"
	#include "ch32v20x_adc.h"
	#include "ch32v20x_rcc.h"


#if DMA1_CH1_ENABLE == 1
void     DMA1_Channel1_IRQHandler(void)   __attribute__((interrupt()));
#endif
#if DMA1_CH2_ENABLE == 1
void     DMA1_Channel2_IRQHandler(void)   __attribute__((interrupt()));
#endif
#if DMA1_CH3_ENABLE == 1
void     DMA1_Channel3_IRQHandler(void)   __attribute__((interrupt()));
#endif
#if DMA1_CH4_ENABLE == 1
void     DMA1_Channel4_IRQHandler(void)   __attribute__((interrupt()));
#endif
#if DMA1_CH5_ENABLE == 1
void     DMA1_Channel5_IRQHandler(void)   __attribute__((interrupt()));
#endif
#if DMA1_CH6_ENABLE == 1
void     DMA1_Channel6_IRQHandler(void)   __attribute__((interrupt()));
#endif
#if DMA1_CH7_ENABLE == 1
void     DMA1_Channel7_IRQHandler(void)   __attribute__((interrupt()));
#endif
#endif

DMA_CFG_t DMA_CALLback[7]   __SECTION(RAM_SECTION_CCMRAM);
/*
 * Включить выбрвнный канал DMA
 */
void HAL_DMA_Enable(DMA_Stram_t stream  )
{
#if MCU == CH32V2
    stream->CFGR |= DMA_CFGR1_EN;
#endif
}
/*
 * Выключить выбранный канал DMA
 */

void HAL_DMA_Disable(DMA_Stram_t stream  )
{
#if MCU == CH32V2
    stream->CFGR &= (uint16_t)(~DMA_CFGR1_EN);
#endif
}

void HAL_DMA_SetCounter( DMA_Stram_t stream, uint32_t counter )
{
	#if MCU == CH32V2
     stream->CNTR = counter;
	#endif

}

void HAL_DMA_SetCouterAndEnable(DMA_Stram_t stream, uint32_t counter )
{
#if MCU == CH32V2
     stream->CNTR = counter;
     stream->CFGR |= DMA_CFGR1_EN;
    #endif
}


void HAL_DMAInitIT( DMA_Stram_t stream , DMA_Derection_t direction, DMA_Size_t dma_size, uint32_t paddr, uint32_t memadr, DMA_CHANNEL_t channel, uint8_t prior, uint8_t subprior, void (*f)(void))
{
#if MCU== APM32
	   DMA_Config_T dmaConfig;
	   uint32_t flag;
	   IRQn_Type  irq;
	   DMA_CHANNEL_T ch;
	  /* Enable DMA clock */
	   RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_DMA2);
	   switch (direction)
	   {
	   	   case MTOP:
	   		   dmaConfig.dir =  DMA_DIR_MEMORYTOPERIPHERAL;
	   		   break;
	   	   case PTOM:
	   		   dmaConfig.dir = DMA_DIR_PERIPHERALTOMEMORY;
	   		   break;
	   }
	   switch (dma_size)
	   {
	   	   case DMA_BYTE:
	   		   dmaConfig.memoryDataSize = DMA_MEMORY_DATA_SIZE_BYTE;
	   		   dmaConfig.peripheralDataSize = DMA_PERIPHERAL_DATA_SIZE_BYTE;
	   		   break;
	   	   case DMA_HWORD:
	   		   dmaConfig.memoryDataSize = DMA_MEMORY_DATA_SIZE_HALFWORD;
	   		   dmaConfig.peripheralDataSize = DMA_PERIPHERAL_DATA_SIZE_HALFWORD;
	   		   break;
	   	   case DMA_WORD:
	   		   dmaConfig.memoryDataSize = DMA_MEMORY_DATA_SIZE_WORD;
	   		   dmaConfig.peripheralDataSize = DMA_PERIPHERAL_DATA_SIZE_WORD;
	   		   break;
	   }
	   switch (channel)
	   {
	   	   case DMA_CH_0:
	   		   ch =DMA_CHANNEL_0;

			   break;
	   	   case DMA_CH_1:
	   		   ch =DMA_CHANNEL_1;

	   		   break;
	   	   case DMA_CH_2:
	   		   ch =DMA_CHANNEL_2;

	   		   break;
	   	   case DMA_CH_3:
	   		   ch =DMA_CHANNEL_3;

	   		   break;
	   	case DMA_CH_4:
	   		   ch =DMA_CHANNEL_4;

	   		   break;
	   	case DMA_CH_5:
	   		   ch =DMA_CHANNEL_5;
	   		   break;
	     case DMA_CH_6:
	   		   ch =DMA_CHANNEL_6;

	   		   break;
	   	case DMA_CH_7:
	   		   ch =DMA_CHANNEL_7;
	   		   break;
	   	default:
	   		return;
	   }
	   if  ( stream == DMA2_CH0 )
	   {
	   		   flag = DMA_INT_TCIFLG0;
	   		   irq = DMA2_STR0_IRQn;
	   		   DMA_CALLback[0].CallBack = f;
	   }
	   else if (stream == DMA2_CH1)
	   {
	   		   flag = DMA_INT_TCIFLG1;
	   		   irq = DMA2_STR1_IRQn;
	   		   DMA_CALLback[1].CallBack = f;
	   }
	   else if  (stream == DMA2_CH2)
	   {
	   		   flag = DMA_INT_TCIFLG2;
	   		   irq = DMA2_STR2_IRQn;
	   		   DMA_CALLback[2].CallBack = f;
	   }
	   else if  (stream == DMA2_CH3)
	   {
	   		   flag = DMA_INT_TCIFLG3;
	   		   irq = DMA2_STR3_IRQn;
	   		   DMA_CALLback[3].CallBack = f;
	   }
	   else if  (stream == DMA2_CH4)
	   {
	   		   flag = DMA_INT_TCIFLG4;
	   		   irq = DMA2_STR4_IRQn;
	   		   DMA_CALLback[4].CallBack = f;
	   }
	   else if  (stream == DMA2_CH5)
	   {
	   		   flag = DMA_INT_TCIFLG5;
	   		   irq = DMA2_STR5_IRQn;
	   		   DMA_CALLback[5].CallBack = f;
	   }
	   else if  (stream == DMA2_CH6)
	   {
	   		   flag = DMA_INT_TCIFLG6;
	   		   irq = DMA2_STR6_IRQn;
	   		   DMA_CALLback[6].CallBack = f;
	   }
	   else
	   {
	   		   flag = DMA_INT_TCIFLG7;
	   		   irq = DMA2_STR7_IRQn;
	   		   DMA_CALLback[7].CallBack = f;
	   }
	   dmaConfig.memoryInc		   = DMA_MEMORY_INC_ENABLE;
	   dmaConfig.peripheralInc 	   = DMA_PERIPHERAL_INC_DISABLE;
	   dmaConfig.loopMode 		   = DMA_MODE_NORMAL;
	   dmaConfig.priority 		   = DMA_PRIORITY_LOW;
	   dmaConfig.fifoMode          = DMA_FIFOMODE_DISABLE;
	   dmaConfig.fifoThreshold     = DMA_FIFOTHRESHOLD_FULL;
	   dmaConfig.peripheralBurst   = DMA_PERIPHERALBURST_SINGLE;
	   dmaConfig.memoryBurst       = DMA_MEMORYBURST_SINGLE;
	   dmaConfig.peripheralBaseAddr = paddr;
	   dmaConfig.channel           = ch;
	   DMA_Config(stream, &dmaConfig);
	   DMA_Enable(stream);
	   DMA_ClearIntFlag(stream, flag);
	   NVIC_EnableIRQRequest( irq, prior , subprior);
#endif
#if MCU== CH32V2
	   DMA_InitTypeDef  dmaConfig;

	   IRQn_Type  irq;
	  /* Enable DMA clock */
	   RCC->AHBPCENR |= RCC_AHBPeriph_DMA1;

	   dmaConfig.DMA_DIR = ( direction== MTOP ) ?DMA_DIR_PeripheralDST : DMA_DIR_PeripheralSRC;


	   switch (dma_size)
	   {
	   	   case DMA_BYTE:
	   		   dmaConfig.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	   		   dmaConfig.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	   		   break;
	   	   case DMA_HWORD:
	   		   dmaConfig.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	   		   dmaConfig.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	   		   break;
	   	   default:
	   		   dmaConfig.DMA_MemoryDataSize = DMA_MemoryDataSize_Word ;
	   		   dmaConfig.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word ;
	   		   break;
	   }
	   if (stream == DMA1_CH1)
	   {
	   		   irq = DMA1_Channel1_IRQn;
	   		   DMA_CALLback[0].CallBack = f;
	   }
	   else if  (stream == DMA1_CH2)
	   {

	   		   irq = DMA1_Channel2_IRQn;
	   		   DMA_CALLback[1].CallBack = f;
	   }
	   else if  (stream == DMA1_CH3)
	   {

	   		   irq = DMA1_Channel3_IRQn;
	   		   DMA_CALLback[2].CallBack = f;
	   }
	   else if  (stream == DMA1_CH4)
	   {

	   		   irq = DMA1_Channel4_IRQn;
	   		   DMA_CALLback[3].CallBack = f;
	   }
	   else if  (stream == DMA1_CH5)
	   {

	   		   irq = DMA1_Channel5_IRQn;
	   		   DMA_CALLback[4].CallBack = f;
	   }
	   else if  (stream == DMA1_CH6)
	   {

	   		   irq = DMA1_Channel6_IRQn;
	   		   DMA_CALLback[5].CallBack = f;
	   }
	   else
	{

		   		   irq = DMA1_Channel7_IRQn;
		   		   DMA_CALLback[6].CallBack = f;
	    }

	   dmaConfig.DMA_MemoryInc		    = DMA_MemoryInc_Enable;
	   dmaConfig.DMA_PeripheralInc 	    = DMA_PeripheralInc_Disable;
	   dmaConfig.DMA_Mode		   		= DMA_Mode_Normal;
	   dmaConfig.DMA_Priority		    = DMA_Priority_Medium;
	   dmaConfig.DMA_PeripheralBaseAddr = paddr;
	   dmaConfig.DMA_MemoryBaseAddr     = memadr;
	   dmaConfig.DMA_M2M 		        = DMA_M2M_Disable;
	   HAL_DMA_Disable(stream);
	   DMA_Init(stream , &dmaConfig);
	   stream->CFGR |= DMA_IT_TC;
	   PFIC_IRQ_ENABLE_PG1(irq ,prior,subprior);


#endif
}






void HAL_ADC_StartDMA( DMA_Stram_t chanel, uint16_t * data, uint16_t size)
{
#if MCU == APM32
	ADC_T* adc;
	if (chanel == DMA2_CH4)
	{
			DMA_ClearStatusFlag(chanel, DMA_FLAG_TEIFLG4 | DMA_FLAG_DMEIFLG4 );
			adc = ADC1;
	}
	else if (chanel == DMA2_CH2)
	{
			DMA_ClearStatusFlag(chanel, DMA_FLAG_TEIFLG2 | DMA_FLAG_DMEIFLG2 );
			adc = ADC2;
	}
	else if (chanel == DMA2_CH0)
    {
			DMA_ClearStatusFlag(chanel, DMA_FLAG_TEIFLG0 | DMA_FLAG_DMEIFLG0 );
			adc = ADC3;
	}
	DMA_ConfigDataNumber(chanel, size);
	DMA_ConfigMemoryTarget(chanel, data, DMA_MEMORY_0);
	ADC_ClearStatusFlag(adc, ADC_FLAG_EOC | ADC_FLAG_OVR);
	ADC_EnableDMA(adc);
	DMA_EnableInterrupt(chanel, DMA_INT_TCIFLG);
	DMA_Enable(chanel);
	ADC_SoftwareStartConv(adc);
#endif
#if MCU == CH32V2
	DMA_ClearITPendingBit( DMA1_IT_GL1 );
	chanel->CNTR  = size;
	chanel->MADDR = (u32)data;
	ADC_DMACmd(ADC1, ENABLE);
	ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
	chanel->CFGR |=DMA_IT_TC;
	chanel->CFGR |= DMA_CFGR1_EN;
	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
#endif
}

#if MCU == APM32
void DMA2_STR4_IRQHandler( void )
{
	if ( DMA_ReadIntFlag(DMA2_Stream4, DMA_INT_TCIFLG4) ==SET)
	{
		DMA_ClearIntFlag(DMA2_Stream4, DMA_INT_TCIFLG4);
		DMA_DisableInterrupt(DMA2_Stream4, DMA_INT_TCIFLG);
		DMA_CALLback[4].CallBack();
	}
}

void DMA2_STR2_IRQHandler( void )
{
	if ( DMA_ReadIntFlag(DMA2_Stream2, DMA_INT_TCIFLG2) ==SET)
	{
		DMA_DisableInterrupt(DMA2_Stream2, DMA_INT_TCIFLG);
		DMA_ClearIntFlag(DMA2_Stream2, DMA_INT_TCIFLG2);
		DMA_CALLback[2].CallBack();
	}
}
void DMA2_STR0_IRQHandler( void )
{
	if ( DMA_ReadIntFlag(DMA2_Stream0, DMA_INT_TCIFLG0) ==SET)
	{
		DMA_DisableInterrupt(DMA2_Stream0, DMA_INT_TCIFLG);
		DMA_ClearIntFlag(DMA2_Stream0, DMA_INT_TCIFLG0);
		DMA_CALLback[0].CallBack();
	}
}
#endif

#if MCU == CH32V2

static void DMA_IRQ( u8 ch)
{
    if ( DMA_GetITStatus(DMA1_IT_TC1<<(4*ch))==SET )
    {
         DMA_CALLback[ch].CallBack();
         DMA_ClearITPendingBit(DMA1_IT_GL1<<(4*ch)); //Сбрасываем флаг
    }
    return;

}

#if DMA1_CH1_ENABLE == 1
void DMA1_Channel1_IRQHandler(void)
{
    DMA_IRQ(0);
    return;
}
#endif
#if DMA1_CH2_ENABLE == 1
void DMA1_Channel2_IRQHandler(void)
{
    DMA_IRQ(1);
    return;
}
#endif
#if DMA1_CH3_ENABLE == 1
void DMA1_Channel3_IRQHandler(void)
{
    DMA_IRQ(2);
    return;
}
#endif
#if DMA1_CH4_ENABLE == 1
void  DMA1_Channel4_IRQHandler(void)
{
    DMA_IRQ(3);
    return;
}
#endif
#if DMA1_CH5_ENABLE == 1
void  DMA1_Channel5_IRQHandler(void)
{
    DMA_IRQ(4);
    return;
}
#endif
#if DMA1_CH6_ENABLE == 1
void  DMA1_Channel6_IRQHandler(void)
{
    DMA_IRQ(5);
    return;
}
#endif
#if DMA1_CH7_ENABLE == 1
void DMA1_Channel7_IRQHandler(void)
{
    DMA_IRQ(6);
    return;
}
#endif


#endif


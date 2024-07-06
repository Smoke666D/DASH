/*
 * hal_adc.c
 *
 *  Created on: 11 апр. 2024 г.
 *      Author: i.dymov
 */

#include "hal_adc.h"
#include "hal_irq.h"
#if MCU == APM32
	#include "apm32f4xx_adc.h"
	#include "apm32f4xx_rcm.h"
	#include "apm32f4xx_dma.h"
    static uint8_t ADC_INIT = 0;
#endif



ADC_t adcs;

#if MCU == APM32
static const  ADC_CHANNEL_T ADC_chennel_ref[]={  ADC_CHANNEL_0,  ADC_CHANNEL_1,  ADC_CHANNEL_2, ADC_CHANNEL_3, ADC_CHANNEL_4,  ADC_CHANNEL_5,  ADC_CHANNEL_6,  ADC_CHANNEL_7,  ADC_CHANNEL_8,  ADC_CHANNEL_9,  ADC_CHANNEL_10,
    ADC_CHANNEL_11, ADC_CHANNEL_12, ADC_CHANNEL_13, ADC_CHANNEL_14, ADC_CHANNEL_15,  ADC_CHANNEL_16,  ADC_CHANNEL_17, ADC_CHANNEL_18, } ;
#endif

#if MCU == CH32V2
static s16 Calibrattion_Val = 0;
static const  uint8_t ADC_chennel_ref[]={  ADC_Channel_0,  ADC_Channel_1,  ADC_Channel_2, ADC_Channel_3, ADC_Channel_4,  ADC_Channel_5,  ADC_Channel_6,  ADC_Channel_7,  ADC_Channel_8,  ADC_Channel_9,  ADC_Channel_10,
		ADC_Channel_11, ADC_Channel_12, ADC_Channel_13, ADC_Channel_14, ADC_Channel_15,  ADC_Channel_16,  ADC_Channel_17} ;

#if ADC_1_2_ENABLE == 1
void ADC1_2_IRQHandler(void) __attribute__((interrupt()));
#endif
u16 Get_ConversionVal(s16 val)
{
    if((val+Calibrattion_Val)<0|| val==0) return 0;
    if((Calibrattion_Val+val)>4095||val==4095) return 4095;
    return (val+Calibrattion_Val);
}

static ADC_TypeDef* ADCS[]={ADC1,ADC2};
static inline void ADC_ENABLE( ADC_NUMBER_t adc )  {  ADCS[adc]->CTLR2 |= CTLR2_ADON_Set; }
static inline void ADC_DISABLE (ADC_NUMBER_t adc  ) { ADCS[adc]->CTLR2 &= CTLR2_ADON_Reset;}
static inline void ADC_BUFFER_ENABLE ( ADC_NUMBER_t adc ) {   ADCS[adc]->CTLR1 |= (1 << 26);  }
static inline void ADC_BUFFER_DISABLE ( ADC_NUMBER_t adc ) {  ADCS[adc]->CTLR1 &= ~(1 << 26);  }
static inline void ADC_DMA_ENABLE ( ADC_NUMBER_t adc ) {  ADCS[adc]->CTLR2 |= CTLR2_DMA_Set; }
static inline void ADC_DMA_DISABLE ( ADC_NUMBER_t adc ) {  ADCS[adc]->CTLR2  &= CTLR2_DMA_Reset; }
static inline void ADC_RESET_CAL( ADC_NUMBER_t adc  )  { ADCS[adc]->CTLR2 |= CTLR2_RSTCAL_Set; }
static inline void ADC_START_CAL ( ADC_NUMBER_t adc  )     {ADCS[adc]->CTLR2 |= CTLR2_CAL_Set; }
static inline void ADC_EXT_TRIG_ENABLE ( ADC_NUMBER_t adc )  {ADCS[adc]->CTLR2 |= CTLR2_EXTTRIG_Set;}

#endif


void  ADC_Enable_and_Start( ADC_NUMBER_t adc  )
{
    ADC_ENABLE(adc);
    ADCS[adc]->CTLR2 |= CTLR2_EXTTRIG_SWSTART_Set;
}

void ADC_Clear_Pending_and_DMA_EN( ADC_NUMBER_t adc )
{
    ADC_DMA_ENABLE (adc);
    ADC_ClearITPendingBit(ADCS[adc],ADC_IT_EOC);
}

void HAL_ADC_CommonConfig()
 {
#if MCU == APM32
	 ADC_CommonConfig_T      adcCommonConfig;
	 if (ADC_INIT==0)
	 {
		 ADC_Reset();
		 ADC_CommonConfigStructInit(&adcCommonConfig);
		 adcCommonConfig.mode            = ADC_MODE_INDEPENDENT;
		 adcCommonConfig.prescaler       = ADC_PRESCALER_DIV8;
		 ADC_CommonConfig(&adcCommonConfig);
		 ADC_INIT = 1;
	 }
#endif
#if MCU == CH32V2
	 RCC_ADCCLKConfig(RCC_PCLK2_Div8);
#endif
 }


void HAL_ADC_ContiniusScanCinvertionDMA( ADC_NUMBER_t adc, uint8_t channel_count, uint8_t *  channel_nmber)
 {
#if MCU == APM32
	ADC_Config_T  adcConfig;
	if ( adc == ADC_1)
	    RCM_EnableAPB2PeriphClock( RCM_APB2_PERIPH_ADC1 );
	else
	if (adc == ADC_2)
	   RCM_EnableAPB2PeriphClock( RCM_APB2_PERIPH_ADC2 );
	else
	   RCM_EnableAPB2PeriphClock( RCM_APB2_PERIPH_ADC3 );
#endif
#if MCU == CH32V2
	ADC_InitTypeDef  adcConfig;
	if ( adc == ADC_1)
	{
	    RCC->APB2PRSTR |= RCC_APB2Periph_ADC1;
	    RCC->APB2PRSTR &= ~RCC_APB2Periph_ADC1;
	    RCC->APB2PCENR |= RCC_APB2Periph_ADC1;
	}
    else
    {
        RCC->APB2PRSTR |= RCC_APB2Periph_ADC2;
        RCC->APB2PRSTR &= ~RCC_APB2Periph_ADC2;
        RCC->APB2PCENR |= RCC_APB2Periph_ADC2;
    }
#endif
	 HAL_ADC_CommonConfig();


#if MCU == APM32

	 ADC_ConfigStructInit( &adcConfig );
	 adcConfig.resolution            = ADC_RESOLUTION_12BIT;
	 adcConfig.scanConvMode          = ENABLE;
	 adcConfig.continuousConvMode    = ENABLE;
	 adcConfig.dataAlign             = ADC_DATA_ALIGN_RIGHT;
	 adcConfig.extTrigEdge           = ADC_EXT_TRIG_EDGE_NONE;
	 adcConfig.nbrOfChannel          = channel_count;
	 ADC_Config(adc, &adcConfig);
	 for (u8 i=0; i< (channel_count) ;i++)
	 {
		 ADC_ConfigRegularChannel(adc,  ADC_chennel_ref[channel_nmber[ i  ]],  i + 1, ADC_SAMPLETIME_112CYCLES);
	 }
	 ADC_EnableEOCOnEachChannel( adc );
#endif



#if MCU==CH32V2
	 adcConfig.ADC_Mode = ADC_Mode_Independent;
	 adcConfig.ADC_ScanConvMode =ENABLE;
	 adcConfig.ADC_ContinuousConvMode = ENABLE;
	 adcConfig.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;
	 adcConfig.ADC_DataAlign = ADC_DataAlign_Right;
	 adcConfig.ADC_NbrOfChannel = ADC_CHANNEL;
	 adcConfig.ADC_OutputBuffer = ADC_OutputBuffer_Disable;
	 adcConfig.ADC_Pga = ADC_Pga_1;
	 ADC_Init(ADCS[adc], &adcConfig);
	 for (u8 i=0; i< (channel_count) ;i++)
	 {
		 ADC_RegularChannelConfig(ADCS[adc],ADC_chennel_ref[channel_nmber[ i  ]], i + 1,  ADC_SampleTime_239Cycles5 );
	 }
	 ADC_EXT_TRIG_ENABLE( adc);
	 ADC_DMA_ENABLE (adc);
	 ADC_ENABLE(adc);
	 ADC_BUFFER_DISABLE(adc);
	 ADC_RESET_CAL(adc);
	 while(ADC_GetResetCalibrationStatus(ADCS[adc]));
	 ADC_START_CAL(adc);
	 while(ADC_GetCalibrationStatus(ADCS[adc]));
	 Calibrattion_Val = Get_CalibrationValue(ADCS[adc]);
	 ADC_BUFFER_ENABLE(adc);
#endif

 }


void HAL_ADC_TempEnable()
{
#if MCU == APM32
	 ADC_EnableTempSensorVrefint();
#endif
}

void HAL_ADC_VrefEnable()
{
#if MCU == APM32
	  ADC_EnableVbat();
#endif
}




void HAL_ADC_Enable(ADC_NUMBER_t adc_number)
{
#if MCU == APM32
	ADC_Enable(adc_number);
#endif
}


void HAL_ADCDMA_Disable(ADC_NUMBER_t adc_number)
{
#if MCU == APM32
	ADC_Disable(adc_number);
	ADC_DisableDMA(adc_number);
#endif
}

void HAL_ADC_AWDT_IT_Init( ADC_NUMBER_t adc, uint8_t channel,u16 low, u16 high, void (*f)(void ) , uint8_t prior, uint8_t subprior )
{
	adcs.awdt_callback = f;
#if MCU == CH32V2
	ADC_DISABLE(adc);
    ADC_AnalogWatchdogThresholdsConfig(ADCS[adc], high, low);
    ADC_AnalogWatchdogSingleChannelConfig( ADCS[adc],  channel);
    ADC_AnalogWatchdogCmd( ADCS[adc], ADC_AnalogWatchdog_SingleRegEnable);
    ADC_ITConfig( ADCS[adc], ADC_IT_AWD, ENABLE);
    ADC_ENABLE(adc);

    PFIC_IRQ_ENABLE_PG1( ADC_IRQn,prior,subprior);

#endif
}

#if MCU == CH32V2

#if ADC_1_2_ENABLE == 1

void ADC1_2_IRQHandler(void)
{
    if(ADC_GetITStatus( ADC1, ADC_IT_AWD))
    {
        ADC_ClearITPendingBit( ADC1, ADC_IT_AWD);
        adcs.awdt_callback();
    }
}
#endif
#endif



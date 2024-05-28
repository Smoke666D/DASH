#ifndef __INIT_H
#define __INIT_H


#include "FreeRTOS.h"
#include "task.h"

//#include "cmsis_os.h"

#define RPM1_Pin GPIO_Pin_11
#define RPM2_Pin GPIO_Pin_3
#define RPM1_Port GPIOA
#define RPM2_Port GPIOB

#define ADC1_CHANNEL1_Pin   GPIO_Pin_0
#define ADC1_CHANNEL2_Pin   GPIO_Pin_1
#define ADC1_CHANNEL3_Pin   GPIO_Pin_2
#define ADC1_CHANNEL4_Pin   GPIO_Pin_3
#define ADC1_CHANNEL1_Port  GPIOA
#define ADC1_CHANNEL2_Port  GPIOA
#define ADC1_CHANNEL3_Port  GPIOA
#define ADC1_CHANNEL4_Port  GPIOA


#define KL_Pin              GPIO_Pin_11
#define KL_Port            GPIOB
#define PowerON_Pin         GPIO_Pin_4
#define PowerON_Port        GPIOB



#define BASE_TIMER     TIM4
#define PWM_TIMER_2    TIM4
#define PWM_TIMER_1    TIM3

#define PWM_TIM_PERIOD   1000
uint32_t GetDelay( uint32_t start_delay);
void vCaptureTimerInit();
void vInit_DeviceConfig( void  );
void DMA_Tx_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize);
void DMA_CC_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize);
uint32_t GetBaseTick();
#endif

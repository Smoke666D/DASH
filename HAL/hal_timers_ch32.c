/*
 * hal_timers.c
 *
 *  Created on: 9 апр. 2024 г.
 *      Author: i.dymov
 */


#include "hal_timers.h"

#if MCU == CH32V2
#include "hal_irq.h"

static void vTimerInitRCC(TimerName_t TimerName);
static TimerCallback_t callback[TIMERS_COUNT];
static TIM_TypeDef * timers[TIMERS_COUNT] = { TIM1,TIM2,TIM3,TIM4};

static uint32_t getTimerFreq(  )
{
    return  ( SystemCoreClock );
}


#if TIM1_UP_ENABLE == 1
void TIM1_UP_IRQHandler(void) __attribute__((interrupt()));
#endif
#if TIM2_UP_ENABLE == 1
void TIM2_IRQHandler(void) __attribute__((interrupt()));
#endif
#if TIM3_UP_ENABLE == 1
void TIM3_IRQHandler(void) __attribute__((interrupt()));
#endif
#if TIM4_UP_ENABLE == 1
void TIM4_IRQHandler(void) __attribute__((interrupt()));
#endif



void HAL_TIMER_InitIt( TimerName_t TimerName, uint32_t freq_in_hz, uint32_t Period, void (*f)() ,uint8_t prior, uint8_t subprior )
{

    callback[TimerName].callback_function = f;
    HAL_TIMER_BaseTimerInit(TimerName,0,Period,( getTimerFreq() /freq_in_hz));
    timers[TimerName]->INTFR = (uint16_t)~TIM_IT_Update;
    timers[TimerName]->DMAINTENR |=  TIM_IT_Update;
   // uint8_t irq;
    switch (TimerName )
    {
#if TIM1_UP_ENABLE == 1
        case TIMER1:
            irq = TIM1_UP_IRQn;
            break;
#endif
#if TIM2_UP_ENABLE == 1
        case TIMER2:
            irq = TIM2_IRQn;
            break;
#endif
#if TIM3_UP_ENABLE == 1
        case TIMER3:
            irq = TIM3_IRQn;
            break;
#endif
#if TIM4_UP_ENABLE == 1
        default:
            PFIC_IRQ_ENABLE_PG1(TIM4_IRQn,prior,subprior);
          //  irq = TIM4_IRQn;
            break;
#endif
    }
    //PFIC_IRQ_ENABLE_PG1(irq,prior,subprior);
}


void static TimerUPIrq( TimerName_t TimerName )
{
    if   (SET == TIM_GetITStatus(timers[TimerName], TIM_IT_Update) )
    {
        callback[TimerName].callback_function();
        timers[TimerName]->INTFR = (uint16_t)~TIM_IT_Update;
    }
}

#if TIM1_UP_ENABLE == 1
void  TIM1_UP_IRQHandler(void)
{
    TimerUPIrq(TIMER1);
}
#endif
#if TIM2_UP_ENABLE == 1
void  TIM2_IRQHandler(void)
{
    TimerUPIrq(TIMER2);
}
#endif
#if TIM3_UP_ENABLE == 1
void  TIM3_IRQHandler(void)
{
    TimerUPIrq(TIMER3);
}
#endif
#if TIM4_UP_ENABLE == 1
void  TIM4_IRQHandler(void)
{
    TimerUPIrq(TIMER4);
}
#endif


void HAL_TiemrEneblae( TimerName_t TimerName )
{
    timers[TimerName]->CNT = 0;
    timers[TimerName]->CTLR1 |= TIM_CEN;
}

void HAL_TiemrDisable( TimerName_t TimerName )
{
    timers[TimerName]->CTLR1 &= (uint16_t)(~((uint16_t)TIM_CEN));
}
/*
 * Функция базовой инициализации таймера.
 * Проводиться через полный ресет. Поэтому регитстры в дефолных,  обычно нулевых значениях
 * Необхоидмости сброса разных битов нет, все они уже сброшены после ресета
 */
void  HAL_TIMER_BaseTimerInit(TimerName_t TimerName, u16 ClockDiv, u16 Period, u16 Div)
{
    vTimerInitRCC(TimerName) ;
    timers[TimerName]->SMCFGR &= (uint16_t)(~((uint16_t)TIM_SMS)); //Тактирование от внутренней шины
    uint16_t tmpcr1 = 0;
    tmpcr1 = timers[TimerName]->CTLR1;
    tmpcr1 &= (uint16_t)(~((uint16_t)(TIM_DIR | TIM_CMS)));
    tmpcr1 |= (uint32_t)TIM_CounterMode_Up;
    tmpcr1 &= (uint16_t)(~((uint16_t)TIM_CTLR1_CKD));
    tmpcr1 |= (uint32_t)ClockDiv;
    timers[TimerName]->CTLR1   = tmpcr1;
    timers[TimerName]->ATRLR   = Period;
    timers[TimerName]->PSC     = Div;
    if((TimerName == TIMER1 ))  timers[TimerName]->RPTCR = 0x0000;
    timers[TimerName]->SWEVGR = TIM_PSCReloadMode_Immediate;
}



void HAL_TIMER_PWMTimersInit(TimerName_t TimerName , uint32_t freq_in_hz, uint32_t Period, uint8_t channel)
{
	 TIM_OCInitTypeDef TIM_OCInitStructure={0};
	 HAL_TIMER_BaseTimerInit(TimerName,0,Period,( getTimerFreq() /freq_in_hz));
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	 TIM_OCInitStructure.TIM_Pulse = Period;
	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 if (channel &  TIM_CHANNEL_1)
	 {
		 TIM_OC1Init( timers[TimerName], &TIM_OCInitStructure );
		 TIM_OC1PreloadConfig( timers[TimerName], TIM_OCPreload_Disable );
	 }
	 if (channel &  TIM_CHANNEL_2)
	 {
	     TIM_OC2Init( timers[TimerName], &TIM_OCInitStructure );
		 TIM_OC2PreloadConfig( timers[TimerName], TIM_OCPreload_Disable );
	 }
	 if (channel &  TIM_CHANNEL_3)
	 {
		TIM_OC3Init( timers[TimerName], &TIM_OCInitStructure );
	    TIM_OC3PreloadConfig( timers[TimerName], TIM_OCPreload_Disable );
	 }
	 if (channel &  TIM_CHANNEL_4)
	 {
		 TIM_OC4Init( timers[TimerName], &TIM_OCInitStructure );
		 TIM_OC4PreloadConfig( timers[TimerName], TIM_OCPreload_Disable );
	 }
	 timers[TimerName]->CTLR1 |= TIM_ARPE;
	 timers[TimerName]->BDTR |= TIM_MOE;
}

static void TI2_Config(TimerName_t TimerName, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
    uint16_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;

    timers[TimerName]->CCER &= (uint16_t) ~((uint16_t)TIM_CC2E);
    tmpccmr1 = timers[TimerName]->CHCTLR1;
    tmpccer = timers[TimerName]->CCER;
    tmp = (uint16_t)(TIM_ICPolarity << 4);
    tmpccmr1 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CC2S)) & ((uint16_t) ~((uint16_t)TIM_IC2F)));
    tmpccmr1 |= (uint16_t)(TIM_ICFilter << 12);
    tmpccmr1 |= (uint16_t)(TIM_ICSelection << 8);
    tmpccer &= (uint16_t) ~((uint16_t)(TIM_CC2P));
    tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CC2E);
    timers[TimerName]->CHCTLR1 = tmpccmr1;
    timers[TimerName]->CCER = tmpccer;
}

static void TI4_Config(TimerName_t TimerName, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
    uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;
    timers[TimerName]->CCER &= (uint16_t) ~((uint16_t)TIM_CC4E);
    tmpccmr2 = timers[TimerName]->CHCTLR2;
    tmpccer = timers[TimerName]->CCER;
    tmp = (uint16_t)(TIM_ICPolarity << 12);
    tmpccmr2 &= (uint16_t)((uint16_t)(~(uint16_t)TIM_CC4S) & ((uint16_t) ~((uint16_t)TIM_IC4F)));
    tmpccmr2 |= (uint16_t)(TIM_ICSelection << 8);
    tmpccmr2 |= (uint16_t)(TIM_ICFilter << 12);
    tmpccer &= (uint16_t) ~((uint16_t)(TIM_CC4P));
    tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CC4E);
    timers[TimerName]->CHCTLR2 = tmpccmr2;
    timers[TimerName]->CCER = tmpccer;
}

void HAL_TimeInitCaptureDMA( TimerName_t TimerName , uint32_t freq_in_hz, uint32_t Period, uint8_t channel )
{
     HAL_TIMER_BaseTimerInit(TimerName,0,Period,( getTimerFreq() /freq_in_hz));
     if ( channel == TIM_CHANNEL_2 )
     {
         TI2_Config(TimerName, TIM_ICPolarity_Falling , TIM_ICSelection_DirectTI, 4);
         timers[TimerName]->CHCTLR1 &= (uint16_t) ~((uint16_t)TIM_IC2PSC);   // Устанавилваем предделитель
         timers[TimerName]->CHCTLR1 |= (uint16_t)(TIM_ICPSC_DIV1 << 8);
         timers[TimerName]->DMAINTENR |= ( TIM_IT_CC2 | TIM_DMA_CC2 ) ;      //Рзрешаем прерывание и работу по DMA
     }
     if ( channel == TIM_CHANNEL_4 )
     {
          TI4_Config(TimerName, TIM_ICPolarity_Falling ,  TIM_ICSelection_DirectTI,  4);
          timers[TimerName]->CHCTLR2 &= (uint16_t) ~((uint16_t)TIM_IC4PSC); // Устанавилваем предделитель
          timers[TimerName]->CHCTLR2 |= (uint16_t)(TIM_ICPSC_DIV1 << 8);
          timers[TimerName]->DMAINTENR |= ( TIM_IT_CC4 | TIM_DMA_CC4 ) ;    //Рзрешаем прерывание и работу по DMA
     }
}


void HAL_TIMER_SetPWMPulse( TimerName_t TimerName , uint8_t channel, uint32_t pulse )
{
     timers[TimerName]->BDTR &= (uint16_t)(~((uint16_t)TIM_MOE));
     TIM_OCInitTypeDef TIM_OCInitStructure={0};
     timers[TimerName]->BDTR &= (uint16_t)(~((uint16_t)TIM_MOE)); //Выключаем выхода ШИМ
     TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
     TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
     TIM_OCInitStructure.TIM_Pulse = (uint16_t) pulse ;
     TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
     if (channel &  TIM_CHANNEL_1) TIM_OC1Init( timers[TimerName], &TIM_OCInitStructure );
     if (channel &  TIM_CHANNEL_2) TIM_OC2Init( timers[TimerName], &TIM_OCInitStructure );
     if (channel &  TIM_CHANNEL_3) TIM_OC3Init( timers[TimerName], &TIM_OCInitStructure );
     if (channel &  TIM_CHANNEL_4) TIM_OC4Init( timers[TimerName], &TIM_OCInitStructure );
     timers[TimerName]->BDTR |= TIM_MOE;   //Включем выхода ШИМ
}


void HAL_TIMER_EnablePWMCH(TimerName_t TimerName  )
{
    timers[TimerName]->BDTR |= TIM_MOE;

}


/*
 *  Функция иницализаиурет тактирование таймера и возвращает указатель
 *  на handle нужного таймера
 */



static void vTimerInitRCC(TimerName_t TimerName)
{
    u32 timers_mask;
    if ((TimerName == TIMER1) || (TimerName > TIMER7))
    {
#if CORE == WCH32V3
        switch (TimerName)
        {
            case TIMER1:
#endif
                timers_mask = RCC_APB2Periph_TIM1;
#if CORE == WCH32V3
                break;
            case TIMER8:
                timers_mask = RCC_APB2Periph_TIM8;
                break;
            case TIMER9:
                timers_mask = RCC_APB2Periph_TIM9;
                break;
            default:
                timers_mask = RCC_APB2Periph_TIM10;
                break;
        }
#endif
        RCC->APB2PRSTR |= timers_mask;
        RCC->APB2PRSTR &= ~timers_mask;
        RCC->APB2PCENR |= timers_mask;

    }
    else
    {
        switch (TimerName)
        {
            case TIMER2:
                timers_mask = RCC_APB1Periph_TIM2;
                break;
            case TIMER3:
                timers_mask = RCC_APB1Periph_TIM3;
                break;
            case TIMER4:
                timers_mask = RCC_APB1Periph_TIM4;
                break;
#if CORE == WCH32V3
            case TIMER5:
                timers_mask = RCC_APB1Periph_TIM5;
                break;
            case TIMER6:
                timers_mask = RCC_APB1Periph_TIM6;
                break;
            default:
                timers_mask = RCC_APB1Periph_TIM7;
                break;
#endif
        }
        RCC->APB1PRSTR |= timers_mask;
        RCC->APB1PRSTR &= ~timers_mask;
        RCC->APB1PCENR |= timers_mask;
    }
}


#endif


/*
 * hal_irq.c
 *
 *  Created on: 25 июл. 2024 г.
 *      Author: i.dymov
 */



/*
 * hal_irq.c
 *
 *  Created on: Jul 6, 2024
 *      Author: i.dymov
 */
#include "hal_irq.h"

#if CORE == WCH32V2 || CORE == WCH32V3
void HAL_InitAPB1(uint32_t apbmask)
{
    RCC->APB1PCENR |= apbmask;
    RCC->APB1PRSTR |= apbmask;
    RCC->APB1PRSTR &= ~apbmask;

}
void HAL_InitAPB2(uint32_t apbmask)
{
    RCC->APB2PCENR |= apbmask;
    RCC->APB2PRSTR |= apbmask;
    RCC->APB2PRSTR &= ~apbmask;

}

#if CORE == WCH32V2
void PFIC_IRQ_ENABLE_PG1(IRQn_Type irg, u8 prior, u8 subprior)
{
    if (prior == 1 )
    {
        NVIC_SetPriority(irg, (1 << 7) | (subprior << 4));
    }
    else
    {
         NVIC_SetPriority(irg, (0 << 7) | (subprior << 4));
    }
    NVIC_EnableIRQ(irg);
}
#endif

#if  CORE == WCH32V3
void PFIC_IRQ_ENABLE_PG2(IRQn_Type irq, u8 prior, u8 subprior)
{

    NVIC_SetPriority(irq, prior << 5);
   // uint8_t tmppre = 0;
      /*  if(prior  <= 1)
        {
            tmppre = subprior+ (4 * prior);
            NVIC_SetPriority(irq, (0 << 7) | (tmppre << 4));
        }
        else
        {
            tmppre = subprior+ (4 * (prior - 2));
            NVIC_SetPriority(irq, (1 << 7) | (tmppre << 4));
        }
*/
    NVIC_EnableIRQ(irq);
 }
#endif
#endif

/*
 * hal_irq.h
 *
 *  Created on: Jul 6, 2024
 *      Author: i.dymov
 */

#ifndef HAL_HAL_IRQ_H_
#define HAL_HAL_IRQ_H_


#include "ch32v20x.h"

void PFIC_IRQ_ENABLE_PG1(IRQn_Type irg, u8 prior, u8 subprior);

#endif /* HAL_HAL_IRQ_H_ */

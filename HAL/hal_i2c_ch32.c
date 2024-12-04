/*
 * hal_i2c_ch32.c
 *
 *  Created on: 1 авг. 2024 г.
 *      Author: i.dymov
 */


#if MCU == CH32V2


#include "hal_irq.h"
#include "hal_i2c.h"

static I2C_TypeDef * I2C[]={I2C1,I2C2};
static HAL_I2C_t   I2C_Callback[2];
/* I2C START mask */
#define CTLR1_START_Set          ((uint16_t)0x0100)
#define CTLR1_START_Reset        ((uint16_t)0xFEFF)

/* I2C ADD0 mask */
#define OADDR1_ADD0_Set          ((uint16_t)0x0001)
#define OADDR1_ADD0_Reset        ((uint16_t)0xFFFE)
/* I2C SPE mask */
#define CTLR1_PE_Set             ((uint16_t)0x0001)
#define CTLR1_PE_Reset           ((uint16_t)0xFFFE)
/* I2C ACK mask */
#define CTLR1_ACK_Set            ((uint16_t)0x0400)
#define CTLR1_ACK_Reset          ((uint16_t)0xFBFF)

/* I2C ENDUAL mask */
#define OADDR2_ENDUAL_Set        ((uint16_t)0x0001)
#define OADDR2_ENDUAL_Reset      ((uint16_t)0xFFFE)
#define EEPROM_I2C_DUALADDR_DISABLE       I2C[Dev.dev]->OADDR2 &= OADDR2_ENDUAL_Reset
/* I2C STOP mask */
#define CTLR1_STOP_Set           ((uint16_t)0x0200)
#define CTLR1_STOP_Reset         ((uint16_t)0xFDFF)
/* I2C FREQ mask */
#define CTLR2_FREQ_Reset         ((uint16_t)0xFFC0)
/* I2C F/S mask */
#define CKCFGR_FS_Set            ((uint16_t)0x8000)
/* I2C registers Masks */
#define CTLR1_CLEAR_Mask         ((uint16_t)0xFBF5)
/* I2C CCR mask */
#define CKCFGR_CCR_Set           ((uint16_t)0x0FFF)
/* I2C FLAG mask */
#define FLAG_Mask                ((uint32_t)0x00FFFFFF)




uint16_t HAL_I2C_GET_STAR2(I2C_NAME_t i2c )                { return  (I2C[i2c]->STAR2); };
uint16_t HAL_I2C_GET_STAR1(I2C_NAME_t i2c )                { return  (I2C[i2c]->STAR1); };
void HAL_I2C_ENABLE( I2C_NAME_t i2c )                      { I2C[i2c]->CTLR1 |= CTLR1_PE_Set;    }
void HAL_I2C_DISABLE( I2C_NAME_t i2c )                     { I2C[i2c]->CTLR1 &= CTLR1_PE_Reset;   }
void I2C_IT_ENABLE( I2C_NAME_t i2c , u16 DATA )            { I2C[i2c]->CTLR2  |= DATA;           }
void I2C_IT_DISABLE(I2C_NAME_t i2c , u16 DATA )            {  I2C[i2c]->CTLR2 &= (uint16_t)~DATA; }
void HAL_I2C_STOP(I2C_NAME_t i2c )                         { I2C[i2c]->CTLR1 |= CTLR1_STOP_Set;  }
void HAL_I2C_START(I2C_NAME_t i2c )                        { I2C[i2c]->CTLR1 |= CTLR1_START_Set; }
void HAL_I2C_SEND( I2C_NAME_t i2c, u8 DATA)                {I2C[i2c]->DATAR = DATA;}
void  HAL_I2C_SEND_ADDR_TRANS(I2C_NAME_t i2c,  u8 DATA)    { I2C[i2c]->DATAR = ( DATA & OADDR1_ADD0_Reset);}
void  HAL_I2C_SEND_ADDR_RECIEVE(I2C_NAME_t i2c,  u8 DATA)  { I2C[i2c]->DATAR = DATA | OADDR1_ADD0_Set;}
void HAL_I2C_ACK_ENABLE(I2C_NAME_t i2c )                   { I2C[i2c]->CTLR1 |= CTLR1_ACK_Set;}
void HAL_I2C_ACK_DISABLE(I2C_NAME_t i2c )     { I2C[i2c]->CTLR1 &= CTLR1_ACK_Reset;}
void HAL_I2C_ClearFlag( I2C_NAME_t i2c , uint32_t flag)   { I2C_ClearFlag(I2C[i2c],I2C_FLAG_AF);}
u16  HAL_I2C_READ_DATA(I2C_NAME_t i2c)                                   { return  I2C[i2c]->DATAR; }

#if I2C1_ENABLE == 1
void   I2C1_EV_IRQHandler(void)  __attribute__((interrupt()));  /* USB HP and CAN1 TX */
void   I2C1_ER_IRQHandler(void)  __attribute__((interrupt()));/* USB LP and CAN1RX0 */
#endif
#if I2C2_ENABLE == 1
void   I2C2_EV_IRQHandler(void)  __attribute__((interrupt()));        /* CAN1 RX1 */
void   I2C2_ER_IRQHandler(void)  __attribute__((interrupt()));     /* CAN1 SCE */
#endif





void InitI2CIT( I2C_NAME_t i2c, uint8_t prior, uint8_t subprior, void (* fdata) ( void ), void (* ferror) ( void ))
{
   // I2C_TypeDef *  I2Cx = i2c;
#if I2C1_ENABLE == 1
    if ( i2c == I2C_1)
    {
        I2C_Callback[0].datacallback  = fdata;
        I2C_Callback[0].errorcallback = ferror;
        HAL_InitAPB1(RCC_APB1Periph_I2C1);
    }
#endif
#if I2C2_ENABLE == 1
    if ( i2c == I2C_2)
    {
        I2C_Callback[1].datacallback  = fdata;
        I2C_Callback[1].errorcallback = ferror;
        HAL_InitAPB1(RCC_APB1Periph_I2C2);

    }
#endif
   uint16_t  freqrange = 0;
   uint16_t result = 0x04;
   uint32_t pclk1 = 8000000;
   RCC_ClocksTypeDef rcc_clocks;;
   RCC_GetClocksFreq(&rcc_clocks);
   pclk1 = rcc_clocks.PCLK1_Frequency;
   I2C[i2c]->CTLR2 = (uint16_t)(pclk1 / 1000000);;
   I2C[i2c]->CTLR1 &= CTLR1_PE_Reset;
   result = (uint16_t)(pclk1 / ( 400000 * 25));
   result |= I2C_DutyCycle_16_9;
   if((result & CKCFGR_CCR_Set) == 0)
   {
       result |= (uint16_t)0x0001;
   }
   I2C[i2c]->RTR = (uint16_t)(((freqrange * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);
   I2C[i2c]->CKCFGR = (uint16_t)(result | CKCFGR_FS_Set);
   I2C[i2c]->CTLR1 |= CTLR1_PE_Set;
   I2C[i2c]->CTLR1 |= (uint16_t)((uint32_t)I2C_Mode_I2C | I2C_Ack_Enable);
   I2C[i2c]->OADDR1 = I2C_AcknowledgedAddress_7bit ;
   if (i2c == I2C_1)
   {

	   PFIC_IRQ_ENABLE_PG1(I2C1_EV_IRQn ,prior,subprior);
	   PFIC_IRQ_ENABLE_PG1(I2C1_ER_IRQn ,prior,subprior);
   }
   else
   {
       PFIC_IRQ_ENABLE_PG1(I2C2_EV_IRQn ,prior,subprior);
       PFIC_IRQ_ENABLE_PG1(I2C2_ER_IRQn ,prior,subprior);

   }
   I2C_DualAddressCmd(I2C[i2c],DISABLE);
   HAL_I2C_ENABLE(i2c);
}













#if I2C1_ENABLE == 1
void I2C1_EV_IRQHandler( void )
{
   I2C_Callback[0].datacallback();

}
void I2C1_ER_IRQHandler ( void )
{
    I2C_Callback[0].errorcallback();
}
#endif
#if I2C2_ENABLE == 1
void  I2C2_EV_IRQHandler( void )
{
    I2C_Callback[1].datacallback();
}
void I2C2_ER_IRQHandler ( void )
{
    I2C_Callback[1].errorcallback();
}
#endif





#endif

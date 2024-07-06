/*
 * hal_i2c.c
 *
 *  Created on: 20 апр. 2024 г.
 *      Author: i.dymov
 */
#include "hal_i2c.h"
#include "hw_lib_eeprom.h"
#include "hal_gpio.h"
#include "hal_irq.h"


EEPOROM *   pEEPROM             __SECTION(RAM_SECTION_CCMRAM);

#if MCU == APM32
#include "apm32f4xx_dma.h"
#endif
#if MCU == CH32V2

static I2C_TypeDef * I2C[]={I2C1,I2C2};
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
#define EEPROM_I2C_DISABLE        I2C[pEEPROM->dev]->CTLR1 &= CTLR1_PE_Reset
/* I2C ENDUAL mask */
#define OADDR2_ENDUAL_Set        ((uint16_t)0x0001)
#define OADDR2_ENDUAL_Reset      ((uint16_t)0xFFFE)
#define EEPROM_I2C_DUALADDR_DISABLE       I2C[pEEPROM->dev]->OADDR2 &= OADDR2_ENDUAL_Reset
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

#if I2C1_ENABLE == 1
void   I2C1_EV_IRQHandler(void)  __attribute__((interrupt()));  /* USB HP and CAN1 TX */
void   I2C1_ER_IRQHandler(void)  __attribute__((interrupt()));/* USB LP and CAN1RX0 */
#endif
#if I2C2_ENABLE == 1
void   I2C2_EV_IRQHandler(void)  __attribute__((interrupt()));        /* CAN1 RX1 */
void   I2C2_ER_IRQHandler(void)  __attribute__((interrupt()));     /* CAN1 SCE */
#endif

static inline void EEPROM_I2C_ENABLE()          { I2C[pEEPROM->dev]->CTLR1 |= CTLR1_PE_Set;    }
static inline void EEPROM_I2C_STOP()            { I2C[pEEPROM->dev]->CTLR1 |= CTLR1_STOP_Set;  }
static inline void EEPROM_I2C_SEND( u8 DATA)    {I2C[pEEPROM->dev]->DATAR = DATA;             }
static inline void I2C_IT_ENABLE( u16 DATA )    { I2C[pEEPROM->dev]->CTLR2  |= DATA;           }
static inline void I2C_IT_DISABLE( u16 DATA )   { I2C[pEEPROM->dev]->CTLR2 &= (uint16_t)~DATA; }
static inline void EEPROM_I2C_START()           { I2C[pEEPROM->dev]->CTLR1 |= CTLR1_START_Set; }
#define            EERPOM_I2C_SEND_ADDR_TRANS( DATA)   I2C[pEEPROM->dev]->DATAR = DATA & OADDR1_ADD0_Reset
static inline void EEPROM_I2C_ACK_ENABLE()      { I2C[pEEPROM->dev]->CTLR1 |= CTLR1_ACK_Set;}
static inline void EEPROM_I2C_ACK_DISABLE()     { I2C[pEEPROM->dev]->CTLR1 &= CTLR1_ACK_Reset;}
#define            EEPROM_I2C_READ_DATA()       I2C[pEEPROM->dev]->DATAR
#endif



static void vDMAI2CEnable( void );
static EERPOM_ERROR_CODE_t I2C_Master_ReviceDMA(  u8 DevAdrees, u16 data_addres,  u8 * data, u16 data_size, u32 timeout,uint8_t TNI  );
static EERPOM_ERROR_CODE_t I2C_Master_TransmitDMA(  u8 DevAdrees,  u8 * data, u16 data_size, u32 timeout,uint8_t TNI  );
static EERPOM_ERROR_CODE_t I2C_Master_ReviceIT(  u8 DevAdrees, u16 data_addres,  u8 * data, u16 data_size, u32 timeout,uint8_t TNI  );
static EERPOM_ERROR_CODE_t I2C_Master_TransmitIT(  u8 DevAdrees, u16 data_addres, u8 * data, u16 data_size, u32 timeout,uint8_t TNI  );
static EERPOM_ERROR_CODE_t I2C_Master_TransmitFast( u8 DevAdrees, u16 data_addres,  u8 * data, u16 data_size  );



void InitI2CDMA( I2C_NAME_t i2c, uint8_t prior, uint8_t subprior)
{

#if	MCU == CH32V2

    I2C_TypeDef *  I2Cx = I2C[i2c];
#if I2C1_ENABLE == 1
	if ( i2c == I2C_1)
	{
	    RCC->APB1PRSTR |= RCC_APB1Periph_I2C1;
	    RCC->APB1PRSTR &= ~RCC_APB1Periph_I2C1;
	    RCC->APB1PCENR |= RCC_APB1Periph_I2C1;
	}
#endif
#if I2C2_ENABLE == 1
	if ( i2c == I2C_2)
	{
	    RCC->APB1PRSTR |= RCC_APB1Periph_I2C2;
	    RCC->APB1PRSTR &= ~RCC_APB1Periph_I2C2;
	    RCC->APB1PCENR |= RCC_APB1Periph_I2C2;
	}
#endif
    uint16_t tmpreg = 0, freqrange = 0;
    uint16_t result = 0x04;
    uint32_t pclk1 = 8000000;

    RCC_ClocksTypeDef rcc_clocks;

    tmpreg = I2Cx->CTLR2;
    tmpreg &= CTLR2_FREQ_Reset;
    RCC_GetClocksFreq(&rcc_clocks);
    pclk1 = rcc_clocks.PCLK1_Frequency;
    freqrange = (uint16_t)(pclk1 / 1000000);
    tmpreg |= freqrange;
    I2Cx->CTLR2 = tmpreg;
    I2Cx->CTLR1 &= CTLR1_PE_Reset;
    tmpreg = 0;
    result = (uint16_t)(pclk1 / ( 400000 * 25));
    result |= I2C_DutyCycle_16_9;
    if((result & CKCFGR_CCR_Set) == 0)
    {
       result |= (uint16_t)0x0001;
    }
    tmpreg |= (uint16_t)(result | CKCFGR_FS_Set);
    I2Cx->RTR = (uint16_t)(((freqrange * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);
    I2Cx->CKCFGR = tmpreg;
    I2Cx->CTLR1 |= CTLR1_PE_Set;
    tmpreg = I2Cx->CTLR1;
    tmpreg &= CTLR1_CLEAR_Mask;
    tmpreg |= (uint16_t)((uint32_t)I2C_Mode_I2C | I2C_Ack_Enable);
    I2Cx->CTLR1 = tmpreg;
    I2Cx->OADDR1 = I2C_AcknowledgedAddress_7bit ;
#endif
#if MCU == APM32
    if ( i2c == I2C_1)
    		RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_I2C1);
    else
    if (i2c == I2C_2)
    {
    		HAL_InitGpioAF( PORT_F, GPIO_PIN_0, GPIO_AF_I2C2, GPIO_OTYPE_OD );
    		HAL_InitGpioAF( PORT_F, GPIO_PIN_1, GPIO_AF_I2C2 ,GPIO_OTYPE_OD );
    		RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_I2C2);

    }
    I2C_Config_T I2C_InitTSturcture;
    I2C_InitTSturcture.clockSpeed 	= 400000;
    I2C_InitTSturcture.mode 		= I2C_MODE_I2C;
    I2C_InitTSturcture.dutyCycle 	= I2C_DUTYCYCLE_16_9;
    I2C_InitTSturcture.ack 			= I2C_ACK_ENABLE;
    I2C_InitTSturcture.ackAddress 	= I2C_ACK_ADDRESS_7BIT;
    I2C_Config(i2c,&I2C_InitTSturcture );
#endif
   pEEPROM =xGetEEPROM();
   pEEPROM->dev = i2c;

#if MODE_I2D == MODE_DMA
   pEEPROM->I2C_Master_Recive_func = I2C_Master_ReviceDMA;
   pEEPROM->I2C_Master_Transmit_func =  I2C_Master_TransmitDMA;
#endif
#if MODE_I2C == MODE_IT
   pEEPROM->I2C_Master_Recive_func =    I2C_Master_ReviceIT;
   pEEPROM->I2C_Master_Transmit_func =  I2C_Master_TransmitIT;
   pEEPROM->I2C_Master_Transmit_func_fast = I2C_Master_TransmitFast;

#endif
#if MCU == CH32V2
#if I2C1_ENABLE == 1
   if (i2c == I2C_1)
   {
       PFIC_IRQ_ENABLE_PG1(I2C1_EV_IRQn,prior,subprior);
       PFIC_IRQ_ENABLE_PG1(I2C1_ER_IRQn,prior,subprior);

   }
#endif
#if I2C2_ENABLE == 1
   if (i2c == I2C_2)
   {
       PFIC_IRQ_ENABLE_PG1(I2C2_EV_IRQn,prior,subprior);
       PFIC_IRQ_ENABLE_PG1(I2C2_ER_IRQn,prior,subprior);

   }
#endif
   EEPROM_I2C_DUALADDR_DISABLE;
   EEPROM_I2C_ENABLE();
#endif
#if MCU == APM32
    if (i2c == I2C_1)
    {
    		NVIC_EnableIRQRequest(I2C1_EV_IRQn, prior, subprior);
    		NVIC_EnableIRQRequest(I2C1_ER_IRQn, prior, subprior);
    }
    else
    if (i2c == I2C_2)
    {
    		NVIC_EnableIRQRequest(I2C2_EV_IRQn, prior, subprior);
    	    NVIC_EnableIRQRequest(I2C2_ER_IRQn, prior, subprior);
    }
    I2C_DisableDualAddress(pEEPROM->dev);
    I2C_Enable(pEEPROM->dev);
#if MODE_I2D == MODE_DMA
    	vDMAI2CEnable();
#endif
#endif

}


static EERPOM_ERROR_CODE_t I2C_Master_ReviceIT( u8 DevAdrees, u16 data_addres,  u8 * data, u16 data_size, u32 timeout,uint8_t TNI  )
{
	EERPOM_ERROR_CODE_t res = EEPROM_ACCESS_ERROR;


	pEEPROM->ucTaskNatificationIndex = TNI;
	pEEPROM->Index          = 0;
    pEEPROM->DataLength     = data_size;
	pEEPROM->ReciveBuffer   = data;
	pEEPROM->DevAdrres      = DevAdrees;
	pEEPROM->data_address   = data_addres;
	pEEPROM->NotifyTaskHeandle = xTaskGetCurrentTaskHandle();
	pEEPROM->I2C_State = I2C_MASTER_RECIVE_START;
#if MCU == APM32
	while (I2C_ReadStatusFlag(pEEPROM->dev, I2C_FLAG_BUSBSY) == SET);
	I2C_EnableAcknowledge(  pEEPROM->dev);
	I2C_EnableGenerateStart(pEEPROM->dev);
	I2C_EnableInterrupt( pEEPROM->dev ,  I2C_INT_EVT | I2C_INT_BUF );
	uint32_t exit_code = ulTaskNotifyTakeIndexed( pEEPROM->ucTaskNatificationIndex, 0xFFFFFFFF, timeout );
	I2C_DisableInterrupt(pEEPROM->dev, I2C_INT_EVT | I2C_INT_BUF | I2C_INT_ERR);
#endif
#if MCU == CH32V2
	EEPROM_I2C_ENABLE();
	while(  I2C[pEEPROM->dev]->STAR2 & STAR2_BUSY_FLAG  );
	EEPROM_I2C_ACK_ENABLE();
	EEPROM_I2C_START();
	I2C_IT_ENABLE( I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR );
	uint32_t exit_code = ulTaskNotifyTakeIndexed( pEEPROM->ucTaskNatificationIndex, 0xFFFFFFFF, timeout );
	I2C_IT_DISABLE(I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR );
    EEPROM_I2C_DISABLE;
#endif
	res = (exit_code == 0x01  )? (EEPROM_OK) : (EEPROM_WRITE_ERROR) ;

    return (res);


}



static EERPOM_ERROR_CODE_t I2C_Master_TransmitFast( u8 DevAdrees, u16 data_addres,  u8 * data, u16 data_size  )
{
   EEPROM_I2C_ENABLE();
   while(  I2C[pEEPROM->dev]->STAR2 & STAR2_BUSY_FLAG  );
   EEPROM_I2C_START();
   while( !( I2C[pEEPROM->dev]->STAR1 & STAR1_SB_FLAG )) ;
   EERPOM_I2C_SEND_ADDR_TRANS( DevAdrees );
   while( !( I2C[pEEPROM->dev]->STAR1 & STAR1_ADDR_FLAG ) );
   EEPROM_I2C_SEND( (u8)((data_addres >>  8) & 0x1F ));   //I2C_SendData
   while( !( I2C[pEEPROM->dev]->STAR1 & STAR1_TXE_FLAG ) );
   EEPROM_I2C_SEND( data_addres & 0xFF) ;
   while( !( I2C[pEEPROM->dev]->STAR1 & STAR1_TXE_FLAG ) );;
   for (u8 i = 0;i<data_size;i++)
   {
       EEPROM_I2C_SEND( data[i] );
       while( !( I2C[pEEPROM->dev]->STAR1 & STAR1_TXE_FLAG ) );;
   }
   while( !( I2C[pEEPROM->dev]->STAR1 & STAR1_BTF_FLAG ) );;
   EEPROM_I2C_STOP();
   return (EEPROM_OK);
}



static EERPOM_ERROR_CODE_t I2C_Master_TransmitIT(  u8 DevAdrees, u16 data_addres,  u8 * data, u16 data_size, u32 timeout,uint8_t TNI  )
{
	EERPOM_ERROR_CODE_t res = EEPROM_ACCESS_ERROR;
	uint32_t exit_code;
	pEEPROM->ucTaskNatificationIndex = TNI;
	pEEPROM->Index          = 0;
	pEEPROM->DataLength     = data_size;
    pEEPROM->ReciveBuffer   = data;
	pEEPROM->DevAdrres      = DevAdrees;
    pEEPROM->data_address   = data_addres;
    pEEPROM->NotifyTaskHeandle = xTaskGetCurrentTaskHandle();
    pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_START;
#if MCU == APM32
	while (I2C_ReadStatusFlag(pEEPROM->dev, I2C_FLAG_BUSBSY) == SET);
    I2C_EnableGenerateStart(pEEPROM->dev);
    I2C_EnableInterrupt( pEEPROM->dev ,  I2C_INT_EVT | I2C_INT_BUF | I2C_INT_ERR);
	uint32_t exit_code = ulTaskNotifyTakeIndexed( pEEPROM->ucTaskNatificationIndex, 0xFFFFFFFF, timeout);
	I2C_DisableInterrupt(pEEPROM->dev, I2C_INT_EVT | I2C_INT_BUF | I2C_INT_ERR);
#endif

#if MCU == CH32V2
	EEPROM_I2C_ENABLE();
	 while(  I2C[pEEPROM->dev]->STAR2 & STAR2_BUSY_FLAG  );
	I2C_IT_ENABLE( I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR);
	EEPROM_I2C_START();
	exit_code = ulTaskNotifyTakeIndexed( pEEPROM->ucTaskNatificationIndex, 0xFFFFFFFF, timeout );
	I2C_IT_DISABLE(I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR );
	EEPROM_I2C_DISABLE;
#endif
	res = (exit_code > 0  )? (EEPROM_OK) : (EEPROM_READ_ERROR);
	//}
	return (res) ;


}

static EERPOM_ERROR_CODE_t I2C_Master_ReviceDMA(  u8 DevAdrees, u16 data_addres,  u8 * data, u16 data_size, u32 timeout,uint8_t TNI  )
{

	EERPOM_ERROR_CODE_t res = EEPROM_ACCESS_ERROR;
#if MCU == APM32
	if ( pEEPROM->BusyFlag == 0 )
	{
		pEEPROM->BusyFlag = 1;
		pEEPROM->ucTaskNatificationIndex = TNI;
		pEEPROM->Index          = data_addres;
		pEEPROM->DataLength     = data_size;
		pEEPROM->ReciveBuffer   = data;
		pEEPROM->DevAdrres      = DevAdrees;
		pEEPROM->direciorn =     0;
		pEEPROM->DMA_TX = 0;
        pEEPROM->NotifyTaskHeandle = xTaskGetCurrentTaskHandle();
	    I2C_EnableInterrupt( pEEPROM->dev ,  I2C_INT_EVT | I2C_INT_BUF);
	    I2C_DisableInterrupt( pEEPROM->dev ,  I2C_INT_ERR );
	    I2C_EnableAcknowledge(  pEEPROM->dev);
	    I2C_EnableDMALastTransfer( pEEPROM->dev );
	    DMA_ConfigDataNumber(DMA1_Stream3, data_size);
	    DMA_ConfigMemoryTarget(DMA1_Stream3, ( uint32_t ) data, DMA_MEMORY_0);
	    DMA_Enable(DMA1_Stream3);
		I2C_EnableGenerateStart(  pEEPROM->dev);
		uint32_t exit_code = ulTaskNotifyTakeIndexed( pEEPROM->ucTaskNatificationIndex, 0xFFFFFFFF, timeout);
	    res = (exit_code > 0  )? (EEPROM_OK) : (EEPROM_READ_ERROR);
	    pEEPROM->BusyFlag = 0;
	  }
#endif
	  return (res);
}


static EERPOM_ERROR_CODE_t I2C_Master_TransmitDMA(  u8 DevAdrees,   u8 * data, u16 data_size, u32 timeout,uint8_t TNI  )
{
	EERPOM_ERROR_CODE_t res = EEPROM_ACCESS_ERROR;
#if MCU == APM32
	if ( pEEPROM->BusyFlag == 0 )
	{
		pEEPROM->BusyFlag = 1;
		pEEPROM->ucTaskNatificationIndex = TNI;
		pEEPROM->Index          = 0;
		pEEPROM->DataLength     = data_size;
		pEEPROM->ReciveBuffer   = data;
		pEEPROM->DevAdrres      = DevAdrees;
		pEEPROM->direciorn      = 0;
		pEEPROM->DMA_TX = 1;
        pEEPROM->NotifyTaskHeandle = xTaskGetCurrentTaskHandle();
        I2C_DisableAcknowledge(pEEPROM->dev);
        I2C_EnableInterrupt( pEEPROM->dev  , I2C_INT_EVT | I2C_INT_ERR );
        I2C_DisableInterrupt( pEEPROM->dev ,  I2C_INT_BUF );
        DMA_ConfigDataNumber(DMA1_Stream7, data_size);
        DMA_ConfigMemoryTarget(DMA1_Stream7, (uint32_t) data, DMA_MEMORY_0);
        DMA_ClearIntFlag(DMA1_Stream7, DMA_INT_TEIFLG7 |  DMA_INT_FEIFLG7 );
        DMA_Enable(DMA1_Stream7);
        I2C_EnableGenerateStart( pEEPROM->dev );
        uint32_t exit_code = ulTaskNotifyTakeIndexed( pEEPROM->ucTaskNatificationIndex, 0xFFFFFFFF, timeout );
        res = (exit_code == 0x01  )? (EEPROM_OK) : (EEPROM_WRITE_ERROR) ;
        pEEPROM->BusyFlag = 0;
	  }
#endif
	  return (res);
}





static void vDMAI2CEnable(void )
{
/* Enable DMA clock */
#if MCU == APM32
   DMA_Config_T dmaConfig;
   RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_DMA1);
   NVIC_EnableIRQRequest(DMA1_STR3_IRQn, 6, 0);
   DMA_Disable(DMA1_Stream3);
   DMA_Disable(DMA1_Stream7);
   dmaConfig.bufferSize = 0;
   dmaConfig.memoryDataSize = DMA_MEMORY_DATA_SIZE_BYTE;
   dmaConfig.peripheralDataSize = DMA_MEMORY_DATA_SIZE_BYTE;
   dmaConfig.memoryInc = DMA_MEMORY_INC_ENABLE;
   dmaConfig.peripheralInc = DMA_PERIPHERAL_INC_DISABLE;
   dmaConfig.loopMode = DMA_MODE_NORMAL;
   dmaConfig.priority =  DMA_PRIORITY_HIGH;
   /* read from peripheral*/
   dmaConfig.dir = DMA_DIR_PERIPHERALTOMEMORY;
   dmaConfig.peripheralBaseAddr = (uint32_t)&I2C2->DATA;
   dmaConfig.memoryBaseAddr =   0;
   dmaConfig.channel           = DMA_CHANNEL_7;
   dmaConfig.fifoMode          = DMA_FIFOMODE_DISABLE;
   dmaConfig.fifoThreshold     = DMA_FIFOTHRESHOLD_FULL;
   dmaConfig.peripheralBurst   = DMA_PERIPHERALBURST_SINGLE;
   dmaConfig.memoryBurst       = DMA_MEMORYBURST_SINGLE;
   DMA_Config(DMA1_Stream3, &dmaConfig);
   DMA_ClearIntFlag(DMA1_Stream3, DMA_INT_TCIFLG3 | DMA_INT_TEIFLG3 );
   DMA_ClearStatusFlag(DMA1_Stream3, DMA_FLAG_TEIFLG3 | DMA_FLAG_DMEIFLG3 );
   DMA_EnableInterrupt(DMA1_Stream3, DMA_INT_TCIFLG );
   NVIC_EnableIRQRequest(DMA1_STR7_IRQn, 6, 0);

   dmaConfig.dir = DMA_DIR_MEMORYTOPERIPHERAL;
   DMA_Config(DMA1_Stream7, &dmaConfig);
   DMA_ClearIntFlag(DMA1_Stream7, DMA_INT_TCIFLG7 | DMA_INT_TEIFLG7 );
   DMA_ClearStatusFlag(DMA1_Stream7, DMA_FLAG_TEIFLG7 | DMA_FLAG_DMEIFLG7 );
   DMA_EnableInterrupt(DMA1_Stream7, DMA_INT_TCIFLG );

#endif
 }

#if MCU == APM32
void DMA1_STR3_IRQHandler( void )
{
	if ( DMA_ReadIntFlag(DMA1_Stream3, DMA_INT_TCIFLG3) ==SET)
	{
		DMA_ClearIntFlag(DMA1_Stream3, DMA_INT_TCIFLG3);
		I2C_DisableDMA( pEEPROM->dev );
	 	I2C_EnableGenerateStop(  pEEPROM->dev );
	 	DMA_Disable(DMA1_Stream3);
	    portBASE_TYPE xHigherPriorityTaskWoken =  pdFALSE;
	    xTaskNotifyIndexedFromISR(pEEPROM->NotifyTaskHeandle, pEEPROM->ucTaskNatificationIndex,0x01, eSetValueWithOverwrite, &xHigherPriorityTaskWoken  );
	    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
}

#endif


#if MCU == APM32
void DMA1_STR7_IRQHandler( void )
{
	if ( DMA_ReadIntFlag(DMA1_Stream7, DMA_INT_TCIFLG7) ==SET)
	{
		DMA_ClearIntFlag(DMA1_Stream7, DMA_INT_TCIFLG7);
		I2C_DisableDMA( pEEPROM->dev );
	 	DMA_Disable(DMA1_Stream7);
	}
}
#endif

static void I2C_FSM()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;


#if MCU == CH32V2
        uint16_t int_flags =  I2C[pEEPROM->dev]->STAR1;
        switch(pEEPROM->I2C_State)
        {
             case  I2C_MASTER_RECIVE_START:
                 if (int_flags & STAR1_SB_FLAG)
                 {
                     EERPOM_I2C_SEND_ADDR_TRANS( pEEPROM->DevAdrres);
                     pEEPROM->I2C_State = I2C_MASTER_RECIVE_WRITE_ADDR;
                 }
                 break;
              case I2C_MASTER_RECIVE_WRITE_ADDR:
                 if (int_flags & STAR1_ADDR_FLAG)
                 {
                       int_flags = I2C[pEEPROM->dev]->STAR2;
                       EEPROM_I2C_SEND( (pEEPROM->data_address >>  8) & 0x1F );
                       pEEPROM->I2C_State = I2C_MASTER_RECIVE_WRITE_ADDR2;
                 }
                 break;
              case  I2C_MASTER_RECIVE_WRITE_ADDR2:
                  if (int_flags &  STAR1_TXE_FLAG)
                  {
                      EEPROM_I2C_SEND( pEEPROM->data_address & 0xFF );
                      pEEPROM->I2C_State = I2C_MASTER_RECIVE_DA_WRITE;
                  }
                  break;
              case I2C_MASTER_RECIVE_DA_WRITE:
                  if (int_flags &   STAR1_TXE_FLAG)
                  {
                      EEPROM_I2C_START();
                      pEEPROM->I2C_State = I2C_MASTER_RECIVE_ADDR;
                   }
                   break;
              case I2C_MASTER_RECIVE_ADDR:
                  if (int_flags & STAR1_SB_FLAG)
                  {
                      I2C[pEEPROM->dev]->DATAR = ( pEEPROM->DevAdrres | OADDR1_ADD0_Set);
                      pEEPROM->I2C_State = I2C_MASTER_RECIVE_MODE;
                  }
                  break;
             case I2C_MASTER_RECIVE_MODE:
                  if (int_flags & STAR1_ADDR_FLAG)
                  {
                      int_flags = I2C[pEEPROM->dev]->STAR2;
                      pEEPROM->I2C_State = I2C_MASTER_RECIEVE;
                   }
                   break;
            case I2C_MASTER_RECIEVE:
                   if (int_flags & 0x0040)
                   {
                       if (pEEPROM->Index < (pEEPROM->DataLength-1))
                       {
                            pEEPROM->ReciveBuffer[pEEPROM->Index++] = EEPROM_I2C_READ_DATA();
                       }
                       else
                       {
                            EEPROM_I2C_ACK_DISABLE();
                            pEEPROM->ReciveBuffer[pEEPROM->Index++] = EEPROM_I2C_READ_DATA();
                            EEPROM_I2C_STOP();
                            xTaskNotifyIndexedFromISR(pEEPROM->NotifyTaskHeandle, pEEPROM->ucTaskNatificationIndex, 0x01, eSetValueWithOverwrite, &xHigherPriorityTaskWoken  );
                            portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
                            pEEPROM->I2C_State = I2C_IDLE;
                        }
                     }
                     break;
                 case  I2C_MASTER_TRANSMIT_START:

                    if (int_flags & STAR1_SB_FLAG)
                    {
                        EERPOM_I2C_SEND_ADDR_TRANS( pEEPROM->DevAdrres );
                        pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_ADDR;
                    }
                     break;
                 case I2C_MASTER_TRANSMIT_ADDR:
                    if  ( int_flags & 0x0400)
                     {
                        I2C[pEEPROM->dev]->STAR1 = (uint16_t)~(I2C_FLAG_AF & FLAG_Mask);
                        EEPROM_I2C_START();
                         pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_START;
                      }
                     else

                    if (int_flags & STAR1_ADDR_FLAG)
                    {
                        int_flags = I2C[pEEPROM->dev]->STAR2;
                        EEPROM_I2C_SEND((pEEPROM->data_address >>  8) & 0x1F );
                        pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_ADDR2;
                    }
                     break;

                 case I2C_MASTER_TRANSMIT_ADDR2:
                     if (int_flags &  STAR1_TXE_FLAG)
                     {
                         EEPROM_I2C_SEND( pEEPROM->data_address & 0xFF );
                         pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_NEXT;
                     }

                     break;
                 case I2C_MASTER_TRANSMIT_NEXT:
                     if (int_flags &  STAR1_TXE_FLAG)
                     {
                        if (pEEPROM->Index < pEEPROM->DataLength )
                        {
                           EEPROM_I2C_SEND( pEEPROM->ReciveBuffer[pEEPROM->Index] );
                           pEEPROM->Index++;
                        }
                        else
                             pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_LAST;
                     }
                     break;
                 case  I2C_MASTER_TRANSMIT_LAST: //��������ߧڧ� ��֧�֧էѧ�� ����ݧ֧էߧ֧ԧ� �ҧѧۧ��
                     if (int_flags & STAR1_BTF_FLAG)
                     {
                         EEPROM_I2C_STOP();
                         xTaskNotifyIndexedFromISR(pEEPROM->NotifyTaskHeandle, pEEPROM->ucTaskNatificationIndex, 0x01, eSetValueWithOverwrite, &xHigherPriorityTaskWoken  );
                         portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
                         pEEPROM->I2C_State = I2C_IDLE;
                     }
                     break;
                 default:
                     break;
             }


#endif

#if MCU == APM32

#if MODE_I2C == MODE_IT
     uint16_t int_flags =   I2C_ReadRegister( pEEPROM->dev,  I2C_REGISTER_STS1 );
     switch(pEEPROM->I2C_State)
     {
     case  I2C_MASTER_RECIVE_START:
    	 	 if (int_flags & 0x0001)
    	 	 {
    	 		 	 I2C_Tx7BitAddress(  pEEPROM->dev, pEEPROM->DevAdrres |  GET_ADDR_MSB(pEEPROM->data_address), I2C_DIRECTION_TX );
    	 		 	 pEEPROM->I2C_State = I2C_MASTER_RECIVE_WRITE_ADDR;
    	 	 }
    	 	 break;
     	 case I2C_MASTER_RECIVE_WRITE_ADDR:
     		 if (int_flags & 0x0002)
     		 {
     			 I2C_ReadRegister( pEEPROM->dev,  I2C_REGISTER_STS2 );
     			 I2C_TxData( pEEPROM->dev , (pEEPROM->data_address & 0xFF) );
     			 pEEPROM->I2C_State = I2C_MASTER_RECIVE_DA_WRITE;
     		 }
     		 break;
     	 case I2C_MASTER_RECIVE_DA_WRITE:
     		 if (int_flags & 0x0080)
     		 {
     			 I2C_EnableGenerateStart(pEEPROM->dev);
     			 pEEPROM->I2C_State = I2C_MASTER_RECIVE_ADDR;
     		 }
     		 break;
         case I2C_MASTER_RECIVE_ADDR:
        	 if (int_flags & 0x0001)
        	 {
        		 I2C_Tx7BitAddress(  pEEPROM->dev, pEEPROM->DevAdrres , I2C_DIRECTION_RX );
        		 pEEPROM->I2C_State = I2C_MASTER_RECIVE_MODE;
        	 }
        	 break;

         case I2C_MASTER_RECIVE_MODE:
        	 if (int_flags & 0x0002)
        	 {
        		 I2C_ReadRegister( pEEPROM->dev,  I2C_REGISTER_STS2 );
        		 pEEPROM->I2C_State = I2C_MASTER_RECIEVE;
        	 }
        	 break;
     	 case I2C_MASTER_RECIEVE:
     		 if (int_flags & 0x0040)
     		 {
     			if (pEEPROM->Index < (pEEPROM->DataLength-1))
     			{
     			    pEEPROM->ReciveBuffer[pEEPROM->Index++] = I2C_RxData( pEEPROM->dev);
     			}
     			else
     			{
     				I2C_DisableAcknowledge(pEEPROM->dev);
     				pEEPROM->ReciveBuffer[pEEPROM->Index++] = I2C_RxData( pEEPROM->dev);
     				I2C_EnableGenerateStop(  pEEPROM->dev );
     			    xTaskNotifyIndexedFromISR(pEEPROM->NotifyTaskHeandle, pEEPROM->ucTaskNatificationIndex, 0x01, eSetValueWithOverwrite, &xHigherPriorityTaskWoken  );
     				portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
     				pEEPROM->I2C_State = I2C_IDLE;
     			}
     		 }
     		 break;
     	 case  I2C_MASTER_TRANSMIT_START:

     		if (int_flags & 0x0001)
     		{
     			 I2C_Tx7BitAddress(  pEEPROM->dev, pEEPROM->DevAdrres |  GET_ADDR_MSB(pEEPROM->data_address), I2C_DIRECTION_TX );
     			 pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_ADDR;
     		}
     		 break;
     	 case I2C_MASTER_TRANSMIT_ADDR:
     		if  ( int_flags & 0x0400)
     		 {
     		     I2C_ClearIntFlag( pEEPROM->dev,I2C_INT_FLAG_AE);
     		     I2C_EnableGenerateStart(  pEEPROM->dev );
     		     pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_START;
     		  }
     		 else

     		if (int_flags & 0x0002)
     		{
     			 I2C_ReadRegister( pEEPROM->dev,  I2C_REGISTER_STS2 );
     			 I2C_TxData( pEEPROM->dev , (pEEPROM->data_address & 0xFF) );
     			 pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_NEXT;
     		}
     		 break;
     	 case I2C_MASTER_TRANSMIT_NEXT:
     		 if (int_flags & 0x0080)
     		 {
     			if (pEEPROM->Index < pEEPROM->DataLength )
     			{
     			   I2C_TxData( pEEPROM->dev, pEEPROM->ReciveBuffer[pEEPROM->Index] );
     			   pEEPROM->Index++;
     			}
     			else
     				 pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_LAST;
     		 }
     		 break;
     	 case  I2C_MASTER_TRANSMIT_LAST:
     		 if (int_flags & 0x0004)
     		 {
     			 I2C_EnableGenerateStop(  pEEPROM->dev );
     			 xTaskNotifyIndexedFromISR(pEEPROM->NotifyTaskHeandle, pEEPROM->ucTaskNatificationIndex, 0x01, eSetValueWithOverwrite, &xHigherPriorityTaskWoken  );
     			 portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
     			 pEEPROM->I2C_State = I2C_IDLE;
     		 }
     		 break;
     	 default:
     		 break;



     }

    #endif
#if  I2C_MODE == MODE_DMA


    if ( ( int_flags  & (I2C_INT_FLAG_ADDR  & 0xFF) )  &&  ( pEEPROM->direciorn == 0 )  )
    {

    	if (pEEPROM->DMA_TX == 0)
    	{
    		I2C_ReadRegister( pEEPROM->dev,  I2C_REGISTER_STS2 );
    		I2C_TxData( pEEPROM->dev , (pEEPROM->Index & 0xFF) );
    	}
    	else
    	{
    		 I2C_EnableDMA( pEEPROM->dev );
    		 I2C_ReadRegister( pEEPROM->dev,  I2C_REGISTER_STS2 );
    	}
    	 return;
    }
    if ((pEEPROM->DMA_TX == 0) && (int_flags  &  I2C_INT_FLAG_BTC) )
    {
    	pEEPROM->direciorn =   1;
    	I2C_EnableGenerateStart(  pEEPROM->dev  );
    }


    if (( int_flags  & ((I2C_INT_FLAG_TXBE  | I2C_INT_FLAG_BTC)   & 0xFF) ) )
    {
    	if (pEEPROM->DMA_TX == 1)

    	{
    		I2C_EnableGenerateStop( pEEPROM->dev);
    		xTaskNotifyIndexedFromISR(pEEPROM->NotifyTaskHeandle, pEEPROM->ucTaskNatificationIndex,0x01, eSetValueWithOverwrite, &xHigherPriorityTaskWoken  );
    		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

    	}

    	return;

    }

#endif
#endif
}

/*
 * ���ҧ�ѧҧ���ڧܧ� ���֧���ӧѧߧڧ� I2C
 */
#if MCU == CH32V2

#if I2C1_ENABLE == 1
void I2C1_EV_IRQHandler( void )
{
	I2C_FSM();
}
void I2C1_ER_IRQHandler ( void )
{
	I2C_FSM();
}
#endif
#if I2C2_ENABLE == 1
void  I2C2_EV_IRQHandler( void )
{
	I2C_FSM();
}
void I2C2_ER_IRQHandler ( void )
{
	I2C_FSM();
}
#endif
#endif

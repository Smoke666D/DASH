/*
 * hal_i2c.c
 *
 *  Created on: 20 апр. 2024 г.
 *      Author: i.dymov
 */
#include "hal_i2c.h"
#include "hw_lib_eeprom.h"
#include "hal_gpio.h"

#if MCU == APM32
#include "apm32f4xx_dma.h"
#endif
#if MCU == CH32V2
void   I2C1_EV_IRQHandler(void)  __attribute__((interrupt()));  /* USB HP and CAN1 TX */
void   I2C1_ER_IRQHandler(void)  __attribute__((interrupt()));/* USB LP and CAN1RX0 */
void   I2C2_EV_IRQHandler(void)  __attribute__((interrupt()));        /* CAN1 RX1 */
void   I2C2_ER_IRQHandler(void)  __attribute__((interrupt()));     /* CAN1 SCE */
#endif


EEPOROM *   pEEPROM 			__SECTION(RAM_SECTION_CCMRAM);
static void vDMAI2CEnable( void );
static EERPOM_ERROR_CODE_t I2C_Master_ReviceDMA(  u8 DevAdrees, u16 data_addres,  u8 * data, u16 data_size, u32 timeout,uint8_t TNI  );
static EERPOM_ERROR_CODE_t I2C_Master_TransmitDMA(  u8 DevAdrees,  u8 * data, u16 data_size, u32 timeout,uint8_t TNI  );
static EERPOM_ERROR_CODE_t I2C_Master_ReviceIT(  u8 DevAdrees, u16 data_addres,  u8 * data, u16 data_size, u32 timeout,uint8_t TNI  );
static EERPOM_ERROR_CODE_t I2C_Master_TransmitIT(  u8 DevAdrees, u16 data_addres, u8 * data, u16 data_size, u32 timeout,uint8_t TNI  );



void InitI2CDMA( I2C_NAME_t i2c, uint8_t prior, uint8_t subprior)
{

#if	MCU == CH32V2
	NVIC_InitTypeDef      NVIC_InitStructure = {0};

	if ( i2c == I2C_1)
	{
	    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );
	    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, DISABLE );
		RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );
	}
	else
	{
	    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C2, ENABLE );
	    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C2, DISABLE );
	    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C2, ENABLE );
	}
    I2C_InitTypeDef I2C_InitTSturcture={0};
    I2C_InitTSturcture.I2C_ClockSpeed          = 400000;
    I2C_InitTSturcture.I2C_Mode                = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle           = I2C_DutyCycle_16_9;
    I2C_InitTSturcture.I2C_Ack                 = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(i2c, &I2C_InitTSturcture );
    I2C_Cmd( i2c, ENABLE );
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
   pEEPROM->BusyFlag = 0;
#if MODE_I2D == MODE_DMA
   pEEPROM->I2C_Master_Recive_func = I2C_Master_ReviceDMA;
   pEEPROM->I2C_Master_Transmit_func =  I2C_Master_TransmitDMA;
#endif
#if MODE_I2C == MODE_IT
   pEEPROM->I2C_Master_Recive_func =    I2C_Master_ReviceIT;
   pEEPROM->I2C_Master_Transmit_func =  I2C_Master_TransmitIT;

#endif
#if MCU == CH32V2
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = prior;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority        =  subprior;
   NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
   if (i2c == I2C_1)
   {
	   NVIC_InitStructure.NVIC_IRQChannel =  I2C1_EV_IRQn ;
	   NVIC_Init(&NVIC_InitStructure);
	   NVIC_InitStructure.NVIC_IRQChannel =  I2C1_ER_IRQn;
	   NVIC_Init(&NVIC_InitStructure);
   }
   else
   {
       NVIC_InitStructure.NVIC_IRQChannel =  I2C2_EV_IRQn ;
       NVIC_Init(&NVIC_InitStructure);
       NVIC_InitStructure.NVIC_IRQChannel =  I2C2_ER_IRQn;
       NVIC_Init(&NVIC_InitStructure);
   }
   I2C_DualAddressCmd(pEEPROM->dev,DISABLE);
   I2C_Cmd(pEEPROM->dev,ENABLE);
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
	pEEPROM->BusyFlag		 = 1;

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
	I2C_Cmd(pEEPROM->dev,ENABLE);
	while( I2C_GetFlagStatus( pEEPROM->dev, I2C_FLAG_BUSY ) != RESET );
	I2C_AcknowledgeConfig(pEEPROM->dev,ENABLE);
	I2C_GenerateSTART( pEEPROM->dev,ENABLE);
    I2C_ITConfig(pEEPROM->dev, I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR, ENABLE );
	uint32_t exit_code = ulTaskNotifyTakeIndexed( pEEPROM->ucTaskNatificationIndex, 0xFFFFFFFF, timeout );
    I2C_ITConfig(pEEPROM->dev, I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR, DISABLE );
    I2C_Cmd(pEEPROM->dev,DISABLE);
#endif
	res = (exit_code == 0x01  )? (EEPROM_OK) : (EEPROM_WRITE_ERROR) ;
	pEEPROM->BusyFlag = 0;
    return (res);


}




static EERPOM_ERROR_CODE_t I2C_Master_TransmitIT(  u8 DevAdrees, u16 data_addres,  u8 * data, u16 data_size, u32 timeout,uint8_t TNI  )
{
	EERPOM_ERROR_CODE_t res = EEPROM_ACCESS_ERROR;
	uint32_t exit_code;

	pEEPROM->BusyFlag = 1;
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
#if MCU == CH32V2
	I2C_Cmd(pEEPROM->dev,ENABLE);
	//xTaskNotifyStateClearIndexed( pEEPROM->NotifyTaskHeandle,pEEPROM->ucTaskNatificationIndex);
	//I2C_SoftwareResetCmd(pEEPROM->dev,ENABLE);
	I2C_ITConfig(pEEPROM->dev, I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR, DISABLE );
	while( I2C_GetFlagStatus( pEEPROM->dev, I2C_FLAG_BUSY ) != RESET );

	I2C_ITConfig(pEEPROM->dev, I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR, ENABLE );
	I2C_GenerateSTART( pEEPROM->dev,ENABLE);
	exit_code = ulTaskNotifyTakeIndexed( pEEPROM->ucTaskNatificationIndex, 0xFFFFFFFF, timeout );
	I2C_ITConfig(pEEPROM->dev, I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR, DISABLE );
	I2C_Cmd(pEEPROM->dev,DISABLE);
#endif
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
        uint16_t int_flags =   I2C_ReadRegister( pEEPROM->dev,  I2C_Register_STAR1 );
        switch(pEEPROM->I2C_State)
        {
             case  I2C_MASTER_RECIVE_START:
                 if (int_flags & 0x0001)
                 {
                     I2C_Send7bitAddress(  pEEPROM->dev, pEEPROM->DevAdrres, I2C_Direction_Transmitter );
                     pEEPROM->I2C_State = I2C_MASTER_RECIVE_WRITE_ADDR;
                 }
                 break;
              case I2C_MASTER_RECIVE_WRITE_ADDR:
                 if (int_flags & 0x0002)
                 {
                       I2C_ReadRegister( pEEPROM->dev,  I2C_Register_STAR2 );
                       I2C_SendData( pEEPROM->dev , (pEEPROM->data_address >>  8) & 0x1F );
                       pEEPROM->I2C_State = I2C_MASTER_RECIVE_WRITE_ADDR2;
                 }
                 break;
              case  I2C_MASTER_RECIVE_WRITE_ADDR2:
                  if (int_flags & 0x0080)
                  {
                      I2C_SendData( pEEPROM->dev , pEEPROM->data_address & 0xFF );
                      pEEPROM->I2C_State = I2C_MASTER_RECIVE_DA_WRITE;
                  }
                  break;
              case I2C_MASTER_RECIVE_DA_WRITE:
                  if (int_flags & 0x0080)
                  {
                      I2C_GenerateSTART(  pEEPROM->dev, ENABLE);
                      pEEPROM->I2C_State = I2C_MASTER_RECIVE_ADDR;
                   }
                   break;
              case I2C_MASTER_RECIVE_ADDR:
                  if (int_flags & 0x0001)
                  {
                      I2C_Send7bitAddress(  pEEPROM->dev, pEEPROM->DevAdrres, I2C_Direction_Receiver);
                      pEEPROM->I2C_State = I2C_MASTER_RECIVE_MODE;
                  }
                  break;
             case I2C_MASTER_RECIVE_MODE:
                  if (int_flags & 0x0002)
                  {
                      I2C_ReadRegister( pEEPROM->dev,  I2C_Register_STAR2 );
                      pEEPROM->I2C_State = I2C_MASTER_RECIEVE;
                   }
                   break;
            case I2C_MASTER_RECIEVE:
                   if (int_flags & 0x0040)
                   {
                       if (pEEPROM->Index < (pEEPROM->DataLength-1))
                       {
                            pEEPROM->ReciveBuffer[pEEPROM->Index++] = I2C_ReceiveData( pEEPROM->dev);
                       }
                       else
                       {
                            I2C_AcknowledgeConfig(pEEPROM->dev, DISABLE );
                            pEEPROM->ReciveBuffer[pEEPROM->Index++] = I2C_ReceiveData( pEEPROM->dev);
                            I2C_GenerateSTOP( pEEPROM->dev, ENABLE );

                                xTaskNotifyIndexedFromISR(pEEPROM->NotifyTaskHeandle, pEEPROM->ucTaskNatificationIndex, 0x01, eSetValueWithOverwrite, &xHigherPriorityTaskWoken  );
                                portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

                            pEEPROM->I2C_State = I2C_IDLE;
                        }
                     }
                     break;
                 case  I2C_MASTER_TRANSMIT_START:

                    if (int_flags & 0x0001)
                    {
                        I2C_Send7bitAddress(  pEEPROM->dev, pEEPROM->DevAdrres, I2C_Direction_Transmitter );
                        pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_ADDR;
                    }
                     break;
                 case I2C_MASTER_TRANSMIT_ADDR:
                    if  ( int_flags & 0x0400)
                     {
                        I2C_ClearFlag( pEEPROM->dev,I2C_FLAG_AF);
                         I2C_GenerateSTART( pEEPROM->dev,ENABLE);
                         pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_START;
                      }
                     else

                    if (int_flags & 0x0002)
                    {
                        I2C_ReadRegister( pEEPROM->dev,  I2C_Register_STAR2 );
                        I2C_SendData( pEEPROM->dev , (pEEPROM->data_address >>  8) & 0x1F );
                        pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_ADDR2;
                    }
                     break;

                 case I2C_MASTER_TRANSMIT_ADDR2:
                     if (int_flags & 0x0080)
                     {
                         I2C_SendData( pEEPROM->dev , pEEPROM->data_address & 0xFF );
                         pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_NEXT;
                     }

                     break;
                 case I2C_MASTER_TRANSMIT_NEXT:
                     if (int_flags & 0x0080)
                     {
                        if (pEEPROM->Index < pEEPROM->DataLength )
                        {
                            I2C_SendData( pEEPROM->dev, pEEPROM->ReciveBuffer[pEEPROM->Index] );
                           pEEPROM->Index++;
                        }
                        else
                             pEEPROM->I2C_State = I2C_MASTER_TRANSMIT_LAST;
                     }
                     break;
                 case  I2C_MASTER_TRANSMIT_LAST:
                     if (int_flags & 0x0004)
                     {
                         I2C_GenerateSTOP( pEEPROM->dev, ENABLE );

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






      //EV6










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





void I2C1_EV_IRQHandler( void )
{
	I2C_FSM();
}
void I2C1_ER_IRQHandler ( void )
{
	I2C_FSM();
}
void  I2C2_EV_IRQHandler( void )
{
	I2C_FSM();
}
void I2C2_ER_IRQHandler ( void )
{
	I2C_FSM();
}


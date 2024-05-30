/*
 * keyboard.c
 *
 *  Created on: 25 февр. 2020 г.
 *      Author: igor.dymov
 */
/*----------------------- Includes ------------------------------------------------------------------*/
#include "inputs.h"
#include "init.h"
#include "hal_adc.h"
#include "HW_API.h"
#include "CO_ODinterface.h"
#include "OD.h"
#include "hal_dma.h"
#include "hal_adc.h"
#include "hw_lib_din.h"
#include "hal_timers.h"
#include "hal_gpio.h"


/*
 * Внутрение переменные модуля
 */
static TaskHandle_t pInputsTaskHandle;
static uint8_t *OD_DIN_flagsPDO = NULL;
static uint8_t *OD_AIN_flagsPDO = NULL;


TaskHandle_t * getInputsTaskHandle()
{
    return (&pInputsTaskHandle);
}


void ADC1_Event( void )
{

    static portBASE_TYPE xHigherPriorityTaskWoken;
    ADC_Cmd(ADC1, DISABLE);
    xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyIndexedFromISR(pInputsTaskHandle, 2, ADC1_DATA_READY, eSetValueWithOverwrite, &xHigherPriorityTaskWoken  );
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}
/*
 *
 */
void ADC1_Init()
{
    uint8_t ADC1_CHANNEL[5] = { ADC_CH_0,  ADC_CH_1, ADC_CH_2, ADC_CH_3,  ADC_CH_6};
    HAL_ADC_ContiniusScanCinvertionDMA( ADC_1 ,  5 ,  ADC1_CHANNEL);
  //  HAL_ADC_AWDT_IT_Init( ADC_1, ADC_CH_6 );
    HAL_DMAInitIT( DMA1_CH1,PTOM, DMA_HWORD , (u32)&ADC1->RDATAR, (u32)getADC1Buffer(), 0, 1, 3, &ADC1_Event  );
    vAINInit();
}





static uint16_t ADC_OLD_RAW[ADC1_CHANNELS  ];
static float OurVData[ADC1_CHANNELS ];
static u16 ViewData[ADC1_CHANNELS];

void ADC_FSM()
{
   uint16_t * pBuffer = getADC1Buffer();

      for (u16 i = 0; i<ADC1_CHANNELS  * ADC_FRAME_SIZE ;i++)
          pBuffer[i]= Get_ConversionVal(pBuffer[i]);
      for (u8 i = 0; i< ADC1_CHANNELS ;i++)
      {
          u32 ADC_Buffer = 0;
          for (u8 k = 0;k < ADC_FRAME_SIZE;k++)
                  ADC_Buffer += pBuffer[k*ADC1_CHANNELS  + i];
          ADC_Buffer =( ADC_Buffer /ADC_FRAME_SIZE);
          ADC_Buffer = vRCFilter(ADC_Buffer, &ADC_OLD_RAW[i]);
          switch ( i )
          {
              case AIN1:
              case AIN2:
              case AIN3:
              case AIN4:
                  //OurVData[i]= fGetAinCalData( i , (float)( ADC_Buffer*RA)/(4095-  ADC_Buffer) );
                  break;
              case AIN5:
                  OurVData[i]= (float) ADC_Buffer  * AINCOOF1 + INDIOD;
                  break;
              default:
                  break;
          }
      }
}


uint8_t xGetAin( u8 ch, u16 * data)
{
    u8 res = 0;
    if (ViewData[ch] != (u16)(ViewData[ch]))
    {
        ViewData[ch] = (u16)(OurVData[ch] );
        res = 1;
    }
    *data = ViewData[ch];
    return (res);
}

float GetAIN(u8 ch)
{
    return OurVData[ch];
}


FlagStatus fDinState (uint8_t i)
{
    switch ( i)
    {
        case INPUT_3:
            return HAL_GetBit(  Din3_4_5_Port , Din3_Pin);
        case INPUT_4:
            return HAL_GetBit(  Din3_4_5_Port , Din4_Pin);
        default:
            return (RESET);
    }
}

void  vSetDoutState( OUT_NAME_TYPE ucCh, BitAction BitVal )
{
    GPIO_WriteBit(PowerON_Port,PowerON_Pin, BitVal);
}


static void DMA1_Channel4_Callback(void)
{
    RMPDataConvert(INPUT_1);
}

static void DMA1_Channel7_Callback(void)
{
    RMPDataConvert(INPUT_2);
}



static void vDINInit()
{
    DoutCinfig_t  DOUT_CONFIG;



    DinConfig_t DIN_CONFIG;
    DIN_CONFIG.eInputType = DIN_CONFIG_NEGATIVE;
    DIN_CONFIG.ulHighCounter = DEF_H_FRONT;
    DIN_CONFIG.ulLowCounter  = DEF_L_FRONT;
    DIN_CONFIG.getPortCallback = &fDinState;
    eDinConfigWtihStruct(INPUT_3,&DIN_CONFIG);
    eDinConfigWtihStruct(INPUT_4,&DIN_CONFIG);

    DOUT_CONFIG.setPortCallback =&vSetDoutState;
    eDOUTConfigWtihStruct( OUT_1, &DOUT_CONFIG);

    //Конфигурация счетных входо
    eRPMConfig(INPUT_1,RPM_CH1);
    eRPMConfig(INPUT_2,RPM_CH2);



    HAL_DMAInitIT(DMA1_CH4,PTOM, CC_BUFFER_SIZE, HAL_GetTimerCounterRegAdres(TIMER1, TIM_CHANNEL_4), (u32)uGetRPMBuffer(INPUT_1),  0,1,3, &DMA1_Channel4_Callback);
    HAL_DMAInitIT(DMA1_CH7,PTOM, CC_BUFFER_SIZE, HAL_GetTimerCounterRegAdres(TIMER2, TIM_CHANNEL_2), (u32)uGetRPMBuffer(INPUT_2),  0,1,3, &DMA1_Channel7_Callback);
    HAL_TiemrEneblae(TIMER1);
    HAL_TiemrEneblae(TIMER2);


}

static TaskHandle_t  pTaskToNotifykHandle;

void InputsNotifyTaskToStop()
{
    xTaskNotify(pInputsTaskHandle, TASK_STOP_NOTIFY , eSetValueWithOverwrite);
}

void InputsNotifyTaskToInit()
{
    pTaskToNotifykHandle = xTaskGetCurrentTaskHandle();
    xTaskNotify(pInputsTaskHandle, TASK_INIT_NOTIFY , eSetValueWithOverwrite);
}



/*---------------------------------------------------------------------------------------------------*/
/*
 * Задача обработки клавиш
 * */
void vInputsTask( void * argument )
{
  TaskFSM_t  state = STATE_IDLE;
  uint32_t ulNotifiedValue;
  BaseType_t notify;
  uint8_t OD_flag;
  uint8_t OD_Ain_flag;
  //OD_DIN_flagsPDO = OD_getFlagsPDO(OD_ENTRY_H2006);
  //OD_AIN_flagsPDO = OD_getFlagsPDO(OD_ENTRY_H2005);

  //Прежде чем запуститься таск, нужно убедиться что прочитались данные из EEPROM и система проинициализирована
  //xEventGroupWaitBits(xGetSystemEventHeandler(),DATA_MODEL_READY, pdTRUE, pdFALSE, portMAX_DELAY );*/
  for(;;)
  {
    switch (state)
    {
        case  STATE_IDLE:
           xTaskNotifyWait(0,0xFF ,&ulNotifiedValue,portMAX_DELAY);
            if ((ulNotifiedValue & TASK_INIT_NOTIFY) !=0)
            {
                ADC1_Init();
              //  vDINInit();
                state = STATE_INIT;
            }
            break;
        case STATE_INIT:                                                                  //Отправляем вызывающей задаче уведомление что таск запущен
            state = STATE_RUN;
            xTaskNotifyGiveIndexed(pTaskToNotifykHandle,0);
            HAL_ADC_StartDMA(DMA1_CH1,getADC1Buffer(),ADC1_CHANNELS * ADC_FRAME_SIZE);
            break;
        case  STATE_RUN:
            notify = xTaskNotifyWaitIndexed(2, 0, 0xFF, &ulNotifiedValue,0);
            if (notify & ADC1_DATA_READY)
            {
                ADC_FSM();
                u16 data;
                for (u8 i=0; i<4;i++)
                {
                   if ( xGetAin( i , &data) ==1)
                   {
                       OD_set_value(OD_ENTRY_H2005, 0x01+i, &data, 2, true);
                       OD_Ain_flag = SET;
                   }
                }
                HAL_ADC_StartDMA(DMA1_CH1,getADC1Buffer(),ADC1_CHANNELS * ADC_FRAME_SIZE);
            }
          /*  vDinDoutProcess();
            uint8_t din_data;
            //Обработка дискрентого входа датчика давления масла
            if ( xGetDIN(INPUT_3,&din_data) == DIN_CHANGE )
            {
                OD_set_value(OD_ENTRY_H2006, 0x02   , &state, 1, true);
                OD_flag = SET;
            }
            for (u8 i =0;i<2;i++)
            {
                u16 rpm;
                if  (xGetRPM(i ,&rpm) == DIN_CHANGE)
                {
                   OD_set_value(OD_ENTRY_H2005, 0x05 + i   , &rpm, 2, true);
                   OD_Ain_flag = SET;
                }
            }
            if ( uGetDIN(INPUT_4)== SET)
            {
                eSetDUT(OUT_1, SET);
            }
            else
            {
                eSetDUT(OUT_1, RESET);
            }
            if (OD_flag)
            {
               OD_flag = RESET;
               OD_requestTPDO(OD_DIN_flagsPDO,1);
            }
            if (OD_Ain_flag)
            {
               OD_Ain_flag = RESET;
               OD_requestTPDO(OD_AIN_flagsPDO,1);
            }*/
            break;

    }

    vTaskDelay(10);

  }
}




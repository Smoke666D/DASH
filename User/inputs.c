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
#include "DataModel.h"
#include "CO_ODinterface.h"
#include "hw_lib_din.h"
#include "OD.h"
#include "hal_dma.h"
#include "hal_adc.h"
#include "hw_lib_din.h"
#include "hal_timers.h"
#include "hal_gpio.h"
#include "hw_timeout.h"

/*
 * Внутрение переменные модуля
 */

#define AIN_MAX_BUFFER_SIZE 100
static TaskHandle_t pInputsTaskHandle;
//static uint8_t *OD_DIN_flagsPDO = NULL;
//static uint8_t *OD_AIN_flagsPDO = NULL;
static uint16_t ADC_OLD_RAW[ ADC1_CHANNELS  ];
static float    OurVData[ ADC1_CHANNELS ];
static ADC_Conversionl_Buf_t DataBuffer[ 3 ];
static int16_t AIN1Buffer[ AIN_MAX_BUFFER_SIZE ];
static int16_t AIN2Buffer[ AIN_MAX_BUFFER_SIZE ];
static int16_t AIN3Buffer[ AIN_MAX_BUFFER_SIZE ];

/*
 *
 */
TaskHandle_t * getInputsTaskHandle()
{
    return (&pInputsTaskHandle);
}

/*
 *
 */
void ADC1_Event( void )
{
    static portBASE_TYPE xHigherPriorityTaskWoken =pdFALSE;
    ADC_Cmd(ADC1, DISABLE);
    xTaskNotifyIndexedFromISR(pInputsTaskHandle, 2, ADC1_DATA_READY, eSetValueWithOverwrite, &xHigherPriorityTaskWoken  );
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}

/*
 *
 */
INIT_FUNC_LOC void ADC1_Init()
{
    const u16     InitSize[]={10,10,100};
    u16 *   BufName[]={AIN1Buffer,AIN2Buffer,AIN3Buffer};
    uint8_t ADC1_CHANNEL[5] = { ADC_CH_0,  ADC_CH_1, ADC_CH_2, ADC_CH_6,  ADC_CH_3};
    HAL_ADC_ContiniusScanCinvertionDMA( ADC_1 ,  5 ,  ADC1_CHANNEL);
    HAL_DMAInitIT( DMA1_CH1,PTOM, DMA_HWORD , (u32)&ADC1->RDATAR, (u32)getADC1Buffer(),  ADC_PRIOR , ADC_SUB_PRIOR, &ADC1_Event  );
    //Инициализация буффера зажержки
    for (uint8_t i =0; i<3;i++)
    {
        DataBuffer[i].ConversionalSize  = InitSize[i];
        DataBuffer[i].pIndex = 0;
        DataBuffer[i].offset =0;
        DataBuffer[i].pBuff = BufName[i];
        vHW_INIT_TIMEOUT(i,getReg16(CH1_TIME_AVER + i*sizeof(u16)));
    }
    HAL_ADC_StartDMA(DMA1_CH1,ADC1_CHANNELS * ADC_FRAME_SIZE);
}





/*
 *
 */
void ADC_FSM( BaseType_t time, u8 * init_flag )
{
   u32 ADC_Buffer[ADC1_CHANNELS ];
   uint16_t * pBuffer = getADC1Buffer();
   //Получаем данные из буфеера DMA и вносим коректировочную поправку
   for (u16 i = 0; i<ADC1_CHANNELS  * ADC_FRAME_SIZE ;i++)
       pBuffer[i]= Get_ConversionVal(pBuffer[i]);
   for (u8 i = 0; i < ADC1_CHANNELS; i++ )
   {
       u32 ADCB = 0;
       for (u8 k = 0;k < ADC_FRAME_SIZE;k++)
              ADCB = ADCB + pBuffer[k*ADC1_CHANNELS  + i ];
       ADC_Buffer[i] =( ADCB /ADC_FRAME_SIZE);
       ADC_Buffer[i] = vRCFilterConfig(ADC_Buffer[i], &ADC_OLD_RAW[i],(i < AIN4)? 230: 100 );
   }
   OurVData[AIN4] = (float)((double) ADC_Buffer[AIN4]  * AINCOOF3)+DIOD;
   OurVData[AIN5]=  (float) ADC_Buffer[AIN5]*VADD_COOF*K;
    if (*init_flag )
    {   for (u8 i = 0; i< AIN4 ;i++)
        {
            for (uint8_t k = 0; k<DataBuffer[i].ConversionalSize;k++  )
            {
                AddBufferData(&DataBuffer[i],ADC_Buffer[i]);
            }
        }
        *init_flag = 0;
    }
    else
    {
              for (u8 i = 0; i< AIN4 ;i++)
              {
                 if (vHW_PROCESS_TIMEOUT(i,time) )
                 {
                     float Vx =0;
                     AddBufferData(&DataBuffer[i],ADC_Buffer[i]);
                     ADC_Buffer[i] = GetConversional(&DataBuffer[i]);
                     Vx = (float)((double)ADC_Buffer[i]*AIN_COOF*K);
                     switch ( i )
                     {
                         case AIN1:
                         case AIN2:
                             OurVData[i]= (Vx*Rpup)/(OurVData[AIN5]-Vx);
                             break;
                         case AIN3:
                            OurVData[i]= (Vx*RpupAIN3)/(OurVData[AIN5]-Vx);
                             if ( (OurVData[AIN5]-Vx) < 0.2 )
                                 OurVData[i]  = 0;
                             break;
                         default:
                             break;
                     }
                 }
              }
    }
}

/*
 *
 */
float GetAIN(u8 ch)
{
    return OurVData[ch];
}

/*
 *
 */
uint8_t fDinStateCallback (uint8_t i)
{
    switch ( i )
    {
        case INPUT_3:
            return HAL_GetBit(  Din3_4_5_Port , Din3_Pin);
        case INPUT_4:
            return HAL_GetBit(  Din3_4_5_Port , Din5_Pin);
        default:
            return (RESET);
    }
}
/*
 *
*/
 void CaptureDMACallBack(  )
{
   HAL_DMA_Disable(DMA1_CH4);
   HAL_DMA_SetCounter(DMA1_CH4,  CC_BUFFER_SIZE);
   RMPDataConvert(INPUT_1);
   HAL_DMA_Enable(DMA1_CH4);
}

 void CaptureDMACallBack_1(  )
{
   HAL_DMA_Disable(DMA1_CH7);
   HAL_DMA_SetCounter(DMA1_CH7,  CC_BUFFER_SIZE);
   RMPDataConvert(INPUT_2);
   HAL_DMA_Enable(DMA1_CH7);
}

/*
 *
 */
 INIT_FUNC_LOC static void vDINInit()
{
    DinConfig_t DIN_CONFIG;
    DIN_CONFIG.eInputType = DIN_CONFIG_POSITIVE;
    DIN_CONFIG.ulHighCounter = DEF_H_FRONT;
    DIN_CONFIG.ulLowCounter  = DEF_L_FRONT;
    DIN_CONFIG.getPortCallback = &fDinStateCallback;
    eDinConfigWtihStruct(INPUT_4,&DIN_CONFIG);
    DIN_CONFIG.eInputType = (getReg8(DIN_ACTIVE_STATE)==1) ? DIN_CONFIG_POSITIVE : DIN_CONFIG_NEGATIVE;
    eDinConfigWtihStruct(INPUT_3,&DIN_CONFIG);
    DIN_CONFIG.eInputType = DIN_CONFIG_POSITIVE;
    //Конфигурация счетных входов
    eRPMConfig(INPUT_1,RPM_CH1);
    eRPMConfig(INPUT_2,RPM_CH2);
    HAL_TimeInitCaptureDMA( TIMER1 , 30000, 60000, TIM_CHANNEL_4);
    HAL_TimeInitCaptureDMA( TIMER2 , 30000, 60000, TIM_CHANNEL_2);
    HAL_DMAInitIT( DMA1_CH4,PTOM, DMA_HWORD , (u32)&TIM1->CH4CVR, (u32) getCaputreBuffer(INPUT_1),  TIM1_DMA_PRIOR , TIM1_DMA_SUBPRIOR, &CaptureDMACallBack );
    HAL_DMAInitIT( DMA1_CH7,PTOM, DMA_HWORD , (u32)&TIM2->CH2CVR, (u32) getCaputreBuffer(INPUT_2),  TIM1_DMA_PRIOR , TIM1_DMA_SUBPRIOR, &CaptureDMACallBack_1 );
    HAL_DMA_SetCouterAndEnable(DMA1_CH7,  CC_BUFFER_SIZE);
    HAL_DMA_SetCouterAndEnable(DMA1_CH4,  CC_BUFFER_SIZE);
    HAL_TiemrEneblae(TIMER1);
    HAL_TiemrEneblae(TIMER2);
}


/*---------------------------------------------------------------------------------------------------*/
/*
 * Задача обработки клавиш
 * */
void vInputsTask( void * argument )
{
  uint32_t last_tick;
  uint8_t din_counter = 0;
  u8 init_flag = 0;
  INPUTS_FSM_t InitState = START_UP_STATE;
  uint32_t ulNotifiedValue;
  last_tick =  xTaskGetTickCount();
  ADC1_Init();
  vDINInit();
  for(;;)
  {
       vDataModelRegDelayWrite();
       vTaskDelay(1);
       if (++din_counter> 10)
       {
           vDinDoutProcess();
           din_counter = 0;
       }
       if (xTaskNotifyWaitIndexed(2, 0, 0xFF, &ulNotifiedValue,0) )
       {
            u32 cur_tick = xTaskGetTickCount();
            ADC_FSM( cur_tick- last_tick, &init_flag);
            last_tick = cur_tick;
            HAL_ADC_StartDMA(DMA1_CH1,ADC1_CHANNELS * ADC_FRAME_SIZE);
            if (  InitState  == START_UP_STATE)
            {
                    if  (uGetDIN(INPUT_4) && (GetAIN(AIN4)>= 9.0 ))
                    {
                        HAL_SetBit(PowerOn_Port, PowerOn_Pin);
                        vSetBrigth( RGB_CHANNEL,    getReg8(RGB_BRIGTH_ADR) );
                        vSetBrigth( WHITE_CHANNEL,  getReg8(WHITE_BRIGTH_ADR));
                        init_flag = 1;
                        InitState = RUN_STATE;
                    }
            }
             else
             {
                 if ((GetAIN(AIN5) < 4.9) || (uGetDIN(INPUT_4)== RESET))
                 {
                     vSystemStop();
                      HardwareDeinit();
                      vSaveData();
                      vTaskDelay(10);
                      HAL_ResetBit(PowerON_Port,PowerON_Pin);
                      vTaskDelay(1);
                      SoftwareReset();
                 }
              }
         }
  }
}







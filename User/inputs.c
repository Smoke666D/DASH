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

#include "CO_ODinterface.h"
#include "hw_lib_din.h"
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
static TaskHandle_t  pTaskToNotifykHandle;
static uint8_t *OD_DIN_flagsPDO = NULL;
static uint8_t *OD_AIN_flagsPDO = NULL;
static uint16_t ADC_OLD_RAW[ ADC1_CHANNELS  ];
static float    OurVData[ ADC1_CHANNELS ];
static median_filter_data_t      RPM_MIDIAN_FILTER_STRUC[2] __SECTION(RAM_SECTION_CCMRAM);
static ab_filter_data_t          RPM_AB_FILTER_STRUC  [2] __SECTION(RAM_SECTION_CCMRAM);
static aver_filter_data_t        RPM_AVER_FILTER_STRUC  [2] __SECTION(RAM_SECTION_CCMRAM);
static void SaveFromISR();

uint16_t vSetVBATLow( float vref)
{
    uint16_t data;
    data = (uint16_t)((vref -DIOD)/AINCOOF3);
    return (data);

}

void fcal()
{
    printf("low %i\r\n",(uint16_t)(GetAIN(AIN5)*10));
   // SaveFromISR();

}
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
void InputsNotifyTaskToStop()
{
    xTaskNotify(pInputsTaskHandle, TASK_STOP_NOTIFY , eSetValueWithOverwrite);
}
/*
 *
 */
void InputsNotifyTaskToInit()
{
    pTaskToNotifykHandle = xTaskGetCurrentTaskHandle();
    xTaskNotify(pInputsTaskHandle, TASK_INIT_NOTIFY , eSetValueWithOverwrite);
}
/*
 *
 */
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
    uint8_t ADC1_CHANNEL[5] = { ADC_CH_0,  ADC_CH_1, ADC_CH_2, ADC_CH_6,  ADC_CH_3};
    HAL_ADC_ContiniusScanCinvertionDMA( ADC_1 ,  5 ,  ADC1_CHANNEL);
    HAL_DMAInitIT( DMA1_CH1,PTOM, DMA_HWORD , (u32)&ADC1->RDATAR, (u32)getADC1Buffer(),  ADC_PRIOR , ADC_SUB_PRIOR, &ADC1_Event  );

}
/*
 *
 */
void ADC_FSM()
{
   uint16_t * pBuffer = getADC1Buffer();
   float Vx =0;
      for (u16 i = 0; i<ADC1_CHANNELS  * ADC_FRAME_SIZE ;i++)
          pBuffer[i]= Get_ConversionVal(pBuffer[i]);
      for (u8 i = 0; i< ADC1_CHANNELS ;i++)
      {
          u32 ADC_Buffer = 0;
          for (u8 k = 0;k < ADC_FRAME_SIZE;k++)
                  ADC_Buffer += pBuffer[k*ADC1_CHANNELS  + i];
          ADC_Buffer =( ADC_Buffer /ADC_FRAME_SIZE);
          ADC_Buffer = vRCFilterConfig(ADC_Buffer, &ADC_OLD_RAW[i],230);
          switch ( i )
          {
              case AIN1:
              case AIN2:
                  Vx = (float)((double)ADC_Buffer*AIN_COOF*K);
                  OurVData[i]= (Vx*Rpup)/(OurVData[AIN5]-Vx);
                  break;
              case AIN3:
                  Vx = (float)((double)ADC_Buffer*AIN_COOF*K);
                 OurVData[i]= (Vx*RpupAIN3)/(OurVData[AIN5]-Vx);
                  if ( (OurVData[AIN5]-Vx) < 0.2 )
                      OurVData[i]  = 0;
                  break;
              case AIN5:
                  OurVData[i]= (float)ADC_Buffer*VADD_COOF*K;

                  break;
              case AIN4:
                  OurVData[i]= (float)((double) ADC_Buffer  * AINCOOF3)+DIOD;
                  break;
              default:
                  break;
          }
      }
}



/*
 *
 */
/*uint8_t xGetAin( u8 ch, float * data)
{
    u8 res = 0;
    if (ViewData[ch] != (u16)(OurVData[ch]))
    {
        ViewData[ch] = (u16)(OurVData[ch] );
        res = 1;
    }
    *data = ViewData[ch];
    return (res);
}/*
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
void  vSetDoutState( OUT_NAME_TYPE ucCh, u8 BitVal )
{
  if ( BitVal == RESET)
      HAL_SetBit(PowerON_Port,PowerON_Pin);
  else
      HAL_ResetBit(PowerON_Port,PowerON_Pin);

}




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
    DoutCinfig_t  DOUT_CONFIG;
    DinConfig_t DIN_CONFIG;
    DIN_CONFIG.eInputType = DIN_CONFIG_POSITIVE;
    DIN_CONFIG.ulHighCounter = DEF_H_FRONT;
    DIN_CONFIG.ulLowCounter  = DEF_L_FRONT;
    DIN_CONFIG.getPortCallback = &fDinStateCallback;
    eDinConfigWtihStruct(INPUT_4,&DIN_CONFIG);
    DIN_CONFIG.eInputType = (getReg8(DIN_ACTIVE_STATE)==1) ? DIN_CONFIG_POSITIVE : DIN_CONFIG_NEGATIVE;
    eDinConfigWtihStruct(INPUT_3,&DIN_CONFIG);
    DIN_CONFIG.eInputType = DIN_CONFIG_POSITIVE;
    DOUT_CONFIG.setPortCallback =&vSetDoutState;
    eDOUTConfigWtihStruct( OUT_1, &DOUT_CONFIG);
    //Конфигурация счетных входо
    vInitMedianFilter(&RPM_MIDIAN_FILTER_STRUC[0]);
    vInitMedianFilter(&RPM_MIDIAN_FILTER_STRUC[1]);
    vInitABFilter(&RPM_AB_FILTER_STRUC[0],0.90);
    vInitABFilter(&RPM_AB_FILTER_STRUC[1],0.90);
    vInitRunAverga(&RPM_AVER_FILTER_STRUC[0],0.5);
    vInitRunAverga(&RPM_AVER_FILTER_STRUC[1],0.5);
    eRPMConfig(INPUT_1,RPM_CH1);
    eRPMConfig(INPUT_2,RPM_CH2);
    HAL_TimeInitCaptureDMA( TIMER1 , 20000, 60000, TIM_CHANNEL_4);
    HAL_TimeInitCaptureDMA( TIMER2 , 20000, 60000, TIM_CHANNEL_2);
    HAL_DMAInitIT( DMA1_CH4,PTOM, DMA_HWORD , (u32)&TIM1->CH4CVR, (u32) getCaputreBuffer(INPUT_1),  TIM1_DMA_PRIOR , TIM1_DMA_SUBPRIOR, &CaptureDMACallBack );
    HAL_DMAInitIT( DMA1_CH7,PTOM, DMA_HWORD , (u32)&TIM2->CH2CVR, (u32) getCaputreBuffer(INPUT_2),  TIM1_DMA_PRIOR , TIM1_DMA_SUBPRIOR, &CaptureDMACallBack_1 );

    HAL_DMA_SetCouterAndEnable(DMA1_CH7,  CC_BUFFER_SIZE);
    HAL_DMA_SetCouterAndEnable(DMA1_CH4,  CC_BUFFER_SIZE);

    HAL_TiemrEneblae(TIMER1);
    HAL_TiemrEneblae(TIMER2);

}

u16 BufAIN[4]={0};
static void SaveData();
/*---------------------------------------------------------------------------------------------------*/
/*
 * Задача обработки клавиш
 * */
void vInputsTask( void * argument )
{
  TaskFSM_t  state = STATE_IDLE;
  INPUTS_FSM_t InitState = START_UP_STATE;
  uint32_t ulNotifiedValue;
  u16 data;
  uint8_t OD_Ain_flag;
 //OD_DIN_flagsPDO = OD_getFlagsPDO(OD_ENTRY_H2006);
  OD_AIN_flagsPDO = OD_getFlagsPDO(OD_ENTRY_H2005);
  for(;;)
  {

    switch (state)
    {
        case  STATE_SAVE_DATA:
            printf("save_data\r\n");
            SaveData();
            state = STATE_IDLE;
            InitState = START_UP_STATE;
            break;
        case  STATE_IDLE:
                ADC1_Init();
                vDINInit();
                HAL_ADC_StartDMA(DMA1_CH1,ADC1_CHANNELS * ADC_FRAME_SIZE);
                state = STATE_RUN;
            break;

        case  STATE_RUN:
            vDataModelRegDelayWrite();
            vTaskDelay(1);
           if (xTaskNotifyWaitIndexed(2, 0, 0xFF, &ulNotifiedValue,0) & ADC1_DATA_READY)
            {
                ADC_FSM();
                HAL_ADC_StartDMA(DMA1_CH1,ADC1_CHANNELS * ADC_FRAME_SIZE);
                vDinDoutProcess();
                switch (  InitState  )
                {
                    case START_UP_STATE:

                        if  (uGetDIN(INPUT_4) && (GetAIN(3)>= 9.0 ))

                            InitState = RUN_STATE_INIT;
                        break;
                    case RUN_STATE_INIT:

                        vSetBrigth( RGB_CHANNEL,    getReg8(RGB_BRIGTH_ADR) );
                        vSetBrigth( WHITE_CHANNEL,  getReg8(WHITE_BRIGTH_ADR));
                        HAL_SetBit(PowerON_Port,PowerON_Pin);
                        eSetDUT(OUT_1, SET);
                        InitState = RUN_STATE;
                        break;
                    case RUN_STATE:
                        //printf("run\r\n");
                        for (u8 i=0; i<4;i++)
                        {
                            data = getODValue( chAIN1 + i,1);
                           // OD_set_value(OD_ENTRY_H2000_digitalInputModuleKeysStates,0x01,&data,1,true);
                            if (BufAIN[i]!= data)
                            {
                                BufAIN[i] = data;
                                OD_Ain_flag = SET;
                            }
                        }
                        if (GetAIN(AIN4) > 8.5)
                        {

                            if ( uGetDIN(INPUT_4)== RESET)
                            {
                                state = STATE_SAVE_DATA;

                                break;
                            }
                            for (u8 i =0;i<2;i++)
                            {
                                u16 rpm;
                                if  (xGetRPM(i ,&rpm) == DIN_CHANGE)
                                {
                                  OD_Ain_flag = SET;
                                }
                            }

                             if ((OD_Ain_flag))// || (data_send_dealy==0))
                             {
                                  OD_Ain_flag = RESET;
                                 // OD_requestTPDO(OD_AIN_flagsPDO,1);
                             }
                        }
                        else
                        {

                            SaveData();
                            state = STATE_IDLE;
                            InitState = START_UP_STATE;
                        }
                        break;

                }

            }
            break;
    }
  }
}


static void SaveData()
{

    vSystemStop();
    HardwareDeinit();
    vSaveData();
    vTaskDelay(10);
    HAL_ResetBit(PowerON_Port,PowerON_Pin);
    vTaskDelay(1);
    SoftwareReset();
}


static void SaveFromISR()
{
    HardwareDeinit();
    vSaveData();
    HAL_ResetBit(PowerON_Port,PowerON_Pin);
    SoftwareReset();

}


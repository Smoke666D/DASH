/*
 * DataModel.c
 *
 *  Created on: Feb 23, 2024
 *      Author: i.dymov
 */


#include "DataModel.h"
#include "301/CO_NMT_Heartbeat.h"
#include "CO_driver_target.h"
#include "OD.h"
#include "dash_draw.h"
#include "hw_lib_eeprom_i2c.h"
#include "hw_data_model.h"
#include "hal_wdt.h"
#include "hal_flash.h"


 static const uint16_t CalPoint[18][2] = {
                                  {1700,89},
                                  {1600,113},
                                  {1500,110},
                                  {1400,187},
                                  {1300,243},
                                  {1200,323},
                                  {1100,436},
                                  {1000,596},
                                  {900,834},
                                  {800,1175},
                                  {700,1707},
                                  {600,2500},
                                  {500,3792},
                                  {400,5896},
                                  {300,9397},
                                  {200,15462},
                                  {100,26114},
                                  {00,45313}

};


#define FUEL_SENSOR_CAL_POINT_COUNT 6

 static const uint16_t CalPoint1[FUEL_SENSOR_CAL_POINT_COUNT][2] = {
             {280,11},
             {230,61},
             {160,112},
             {90,160},
             {50,185},
             {0,300}};


static u16 secondcounter;
static QueueHandle_t    pDataRegQueue;


QueueHandle_t * xDataRegQueue( void )
{
  return  (&pDataRegQueue);
}

void vSetBitrate( uint8_t data);
void vSetNodeID( uint8_t data);


u16 DataModelGetSecCounter()
{
    return (secondcounter);
}

void vDataModelRegDelayWrite()
{
    if ( uxQueueMessagesWaiting(pDataRegQueue) != 0)
    {
        EEPROM_REG_Q_t reg_data;
        xQueueReceive( pDataRegQueue, &reg_data,portMAX_DELAY );
        switch(reg_data.addr )
        {
            case BITRATE:
                vSetBitrate(getReg8(BITRATE ));
                break;
            case NODE_ID:
                vSetNodeID(getReg8(NODE_ID));
                break;
            default:
                eEEPROMWr(reg_data.addr, GetRegisterAddr(reg_data.addr),reg_data.len,1);
                break;
        }
    }
}






INIT_FUNC_LOC  void DataModel_Init()
{

     printf("EEPROM Init...");
    if ( eEEPROMRd(0x00 ,GetDataRegister() , EEPROM_REGISER_COUNT,2) == EEPROM_OK)
    {
         printf("OK!\r\n");
         if (getReg8(VALID_CODE_ADDRES)!=VALID_CODE )
         {
             ClearDataModel();
             setReg8 (VALID_CODE_ADDRES ,VALID_CODE);
             setReg8 (BITRATE_ADR,2 | 0x80);
             setReg8 (RGB_BRIGTH_ADR,10);
             setReg8 (WHITE_BRIGTH_ADR,10);
             vSetNodeID( 0x20);
             HAL_WDTReset();
             vSetBitrate(2);
             HAL_WDTReset();
             setReg8 (BAR_MODE ,1);
             setReg32(HOUR_COUNTER_ADR,      1046);
             setReg16(BAR_VALUE_HIGH        ,39000);
             setReg16(BAR_VALUE_LOW         ,0);
             setReg16(BAR_VALUE_RED_HIGH    ,39000);
             setReg16(BAR_VALUE_RED_LOW     ,30000);
             setReg16(BAR_VALUE_GREEN_HIGH  ,36000);
             setReg16(BAR_VALUE_GREEN_LOW   ,0);
             setReg16(RGB1_VALUE_GREEN_HIGH ,0);
             setReg16(RGB1_VALUE_GREEN_LOW  ,0);
             setReg16(RGB1_VALUE_RED_HIGH   ,1);
             setReg16(RGB1_VALUE_RED_LOW    ,1);
             setReg16(RGB1_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB1_VALUE_BLUE_LOW   ,0);
             setReg16(RGB2_VALUE_GREEN_HIGH ,1);
             setReg16(RGB2_VALUE_GREEN_LOW  ,1);
             setReg16(RGB2_VALUE_RED_HIGH   ,1);
             setReg16(RGB2_VALUE_RED_LOW    ,1);
             setReg16(RGB2_VALUE_BLUE_HIGH  ,3);
             setReg16(RGB2_VALUE_BLUE_LOW   ,1);
             setReg16(RGB3_VALUE_GREEN_HIGH ,0 );
             setReg16(RGB3_VALUE_GREEN_LOW  ,0 );
             setReg16(RGB3_VALUE_RED_HIGH   ,0 );
             setReg16(RGB3_VALUE_RED_LOW    ,0 );
             setReg16(RGB3_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB3_VALUE_BLUE_LOW   ,0);
             setReg16(RGB4_VALUE_GREEN_HIGH ,0);
             setReg16(RGB4_VALUE_GREEN_LOW  ,0);
             setReg16(RGB4_VALUE_RED_HIGH   ,0);
             setReg16(RGB4_VALUE_RED_LOW    ,0);
             setReg16(RGB4_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB4_VALUE_BLUE_LOW   ,0);
             setReg16(RGB5_VALUE_GREEN_HIGH ,0);
             setReg16(RGB5_VALUE_GREEN_LOW  ,0);
             setReg16(RGB5_VALUE_RED_HIGH   ,120);
             setReg16(RGB5_VALUE_RED_LOW    ,160);
             setReg16(RGB5_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB5_VALUE_BLUE_LOW   ,0);
             setReg16(RGB6_VALUE_GREEN_HIGH ,1);
             setReg16(RGB6_VALUE_GREEN_LOW  ,1);
             setReg16(RGB6_VALUE_RED_HIGH   ,1);
             setReg16(RGB6_VALUE_RED_LOW    ,1);
             setReg16(RGB6_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB6_VALUE_BLUE_LOW   ,0);
             setReg16(RGB7_VALUE_GREEN_HIGH ,0 );
             setReg16(RGB7_VALUE_GREEN_LOW  ,0 );
             setReg16(RGB7_VALUE_RED_HIGH   ,1000);
             setReg16(RGB7_VALUE_RED_LOW    ,950 );
             setReg16(RGB7_VALUE_BLUE_HIGH  ,400);
             setReg16(RGB7_VALUE_BLUE_LOW   ,1);
             setReg16(RGB8_VALUE_GREEN_HIGH ,3);
             setReg16(RGB8_VALUE_GREEN_LOW  ,1);
             setReg16(RGB8_VALUE_RED_HIGH   ,3);
             setReg16(RGB8_VALUE_RED_LOW    ,1);
             setReg16(RGB8_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB8_VALUE_BLUE_LOW   ,0);
             setReg16(RGB9_VALUE_GREEN_HIGH ,3);
             setReg16(RGB9_VALUE_GREEN_LOW  ,2);
             setReg16(RGB9_VALUE_RED_HIGH   ,3);
             setReg16(RGB9_VALUE_RED_LOW    ,2);
             setReg16(RGB9_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB9_VALUE_BLUE_LOW   ,0);
             setReg16(RGB12_VALUE_GREEN_HIGH,110);
             setReg16(RGB12_VALUE_GREEN_LOW ,50);
             setReg16(RGB12_VALUE_RED_HIGH  ,110);
             setReg16(RGB12_VALUE_RED_LOW   ,1);
             setReg16(RGB12_VALUE_BLUE_HIGH ,0);
             setReg16(RGB12_VALUE_BLUE_LOW  ,0);
             setReg16(RGB10_VALUE_GREEN_HIGH,0);
             setReg16(RGB10_VALUE_GREEN_LOW ,0);
             setReg16(RGB10_VALUE_RED_HIGH  ,0);
             setReg16(RGB10_VALUE_RED_LOW   ,0 );
             setReg16(RGB10_VALUE_BLUE_HIGH ,0);
             setReg16(RGB10_VALUE_BLUE_LOW  ,0);
             setReg16(RGB11_VALUE_GREEN_HIGH,4);
             setReg16(RGB11_VALUE_GREEN_LOW ,3);
             setReg16(RGB11_VALUE_RED_HIGH  ,4);
             setReg16(RGB11_VALUE_RED_LOW   ,3);
             setReg16(RGB11_VALUE_BLUE_HIGH ,0);
             setReg16(RGB11_VALUE_BLUE_LOW  ,0);
             setReg16(RGB13_VALUE_GREEN_HIGH,1);
             setReg16(RGB13_VALUE_GREEN_LOW ,1);
             setReg16(RGB13_VALUE_RED_HIGH  ,0);
             setReg16(RGB13_VALUE_RED_LOW   ,0);
             setReg16(RGB13_VALUE_BLUE_HIGH ,0);
             setReg16(RGB13_VALUE_BLUE_LOW  ,0);
             setReg16(RGB14_VALUE_GREEN_HIGH,1);
             setReg16(RGB14_VALUE_GREEN_LOW ,1);
             setReg16(RGB14_VALUE_RED_HIGH  ,0);
             setReg16(RGB14_VALUE_RED_LOW   ,0);
             setReg16(RGB14_VALUE_BLUE_HIGH ,0);
             setReg16(RGB14_VALUE_BLUE_LOW  ,0);
             setReg8(RGBMAP1                , vCHANNEL6) ;
             setReg8(RGBMAP2                , vCHANNEL2);
             setReg8(RGBMAP3                , 0);
             setReg8(RGBMAP4                , 0);
             setReg8(RGBMAP5                , chAKB );
             setReg8(RGBMAP6                , vCHANNEL1 ) ;
             setReg8(RGBMAP8                , 0);
             setReg8(RGBMAP7                , vCHANNEL16 );
             setReg8(RGBMAP9                , vCHANNEL3 ) ;
             setReg8(RGBMAP12               , chAIN3 );
             setReg8(RGBMAP10               , 0 );
             setReg8(RGBMAP11               , 0 );
             setReg8(RGBMAP13               , vCHANNEL4 );
             setReg8(RGBMAP14               , vCHANNEL3 ) ;
             setReg8(BARMAP                 , vCHANNEL15 );

             static const u16 seg_const[]={0x336, 0x03F, 0x2F3 , 0x0F3, 0x0f6, 0x038 , 0x0CF , 0x0E6 , 0x0ED};
             for (u8 i=0; i<9;i++)
                 setReg16(BIG_SEGVAL1 + i*sizeof (u16), seg_const[i]);

             setReg8(ODOMETR_MAP            , chRPM2 );
             setReg32(ODOMETR_ADR         ,1161200);

             setReg8( AIN1_CAL_POINT_COUNT  ,18 );
             setReg32(AIN1_SETTING ,10<<16 | 400 );
             setReg8( AIN2_CAL_POINT_COUNT  ,18);
             setReg32(AIN2_SETTING ,10<<16 | 400 );
             setReg32(AIN3_SETTING ,10<<16  );
             setReg8(AIN3_CAL_POINT_COUNT       , FUEL_SENSOR_CAL_POINT_COUNT);
             for (u8 i=0; i< 18;i++)
             {
                 setReg16(AIN1_CAL_POINT_BEGIN + i*4    , CalPoint[i][0]);
                 setReg16(AIN1_CAL_POINT_BEGIN + i*4 + 2, CalPoint[i][1]);
                 setReg16(AIN2_CAL_POINT_BEGIN + i*4    , CalPoint[i][0]);
                 setReg16(AIN2_CAL_POINT_BEGIN + i*4 + 2, CalPoint[i][1]);
             }
             for (u8 i=0; i<FUEL_SENSOR_CAL_POINT_COUNT;i++)
             {
                  setReg16(AIN3_CAL_POINT_BEGIN + i*4    , CalPoint1[i][0]);
                  setReg16(AIN3_CAL_POINT_BEGIN + i*4 + 2, CalPoint1[i][1]);
             }
             setReg16(RPM1_COOF,1);
             setReg16(RPM2_COOF,8);
             setReg32( MENU1_MAP , 0x50730000 | vCHANNEL15);
             setReg32( MENU2_MAP , 0x3E000000  | chAKB );
             setReg32( MENU3_MAP , 0x76000000  | chHOUR );
             setReg32( MENU4_MAP , 0x71000000  | chAIN3);
             setReg32( MENU5_MAP , 0x78790000  | vCHANNEL16);
             setReg32( MENU6_MAP , 0x6D000000  | chRPM2);
             setReg32( MENU7_MAP , 0x3F000000  | chODOMETR);
             setReg32( MENU8_MAP , 0x3F060000  | chTRIP);
             //setReg32( MENU9_MAP                        , 0);
             //setReg32( MENU10_MAP                       , 0);
             setReg8(MENU_DEF_POS                       , 0);
             setReg8(MENU_HOME_BACK_TIME                , 10);
             setReg8(DIN_ACTIVE_STATE                   , 0);
             setReg8(KEY_CONTROL_REG                    , 1);
             setReg16(CH1_TIME_AVER,10);
             setReg16(CH2_TIME_AVER,10);
             setReg16(CH3_TIME_AVER,300);
             setReg32(VERSION_REG,10);
             eEEPROMWr(VALID_CODE_ADDRES,GetDataRegister(),EEPROM_REGISER_COUNT,2);
             ClearDataModel();
             vTaskDelay(10);
             eEEPROMRd(0x00 ,GetDataRegister() , EEPROM_REGISER_COUNT,2);

         }

         static const u16 cal_point_index[]={AIN1_CAL_POINT_BEGIN,AIN2_CAL_POINT_BEGIN,AIN3_CAL_POINT_BEGIN};
         POINT_t point[2];
         for (u8 k = 0; k < 3 ;k++)
         {
            u8 cal_point_count  = getReg8(AIN1_CAL_POINT_COUNT + k *3 );
            if ( eAinCalDataConfig(AIN1+ k,cal_point_count -1 ) == CAL_SUCCESS)
            {
                for (u8 i = 0; i< cal_point_count - 1 ;i++)
                {
                     int16_t data16  = (int16_t)getReg16(cal_point_index[k] + i*4);
                     point[0].Y = (float)data16;
                     u16 udata16 = getReg16(cal_point_index[k] + i*4 + 2);
                     point[0].X = (float)udata16;
                     data16  = (int16_t)getReg16(cal_point_index[k] + i*4 + 4);
                     point[1].Y = (float)data16;
                     udata16 = getReg16(cal_point_index[k] + i*4 + 6);
                     point[1].X = (float)udata16;
                     eSetAinCalPoint( AIN1+k ,point, i);
                }
            }
         }

         if  ( vGetBitrate()==0xFF)  vSetBitrate(2);
         if (( vGetNodeId() ==0x00)|| ( vGetNodeId() ==0xFF) ) vSetNodeID( 0x20);
         HAL_WDTReset();

    }
    else {
        printf("fail\r\n");
    }
    secondcounter = 0;
}


//§¶§å§ß§Ü§è§Ú§ñ §Ù§Ñ§á§Ú§ã§Ú §Ó EEPROM §é§Ö§â§Ö§Ù §à§é§Ö§â§Ö§Õ§î §à§á§Ö§â§Ñ§è§Ú§ß§ß§à§Û §ã§Ú§ã§ä§Ö§Þ§í.
//§¶§å§ß§Ü§è§Ú§ñ §Ù§Ñ§á§Ú§ã§í§Ó§Ñ§Ö§ä §ß§à§Ó§í§Ö §Õ§Ñ§ß§ß§í§Ö §Ó §â§Ö§Ô§Ú§ã§ä§â, §Ú §Ö§ã§Ý§Ú §â§Ö§Ô§Ú§ã§ä§â §ß§Ñ§ç§à§Õ§Ú§ä§î§ã§ñ §Ó ROM
//§³§Ü§Ú§Õ§í§Ó§Ñ§Ö§ä §Õ§Ñ§ß§ß§í§Ö §à §ß§Ö§Þ §Ó §à§é§Ö§â§Ö§Õ§î
//§°§é§Ö§â§Ö§Õ§î §à§Ò§â§Ñ§Ò§Ñ§ä§í§Ó§Ñ§Ö§ä§ã§ñ §Ó §á§à§ä§à§Ü§Ö vInputsTask
//§´§Ñ§Ü§à§Û §Þ§Ö§ç§ß§Ú§Ù§Þ §ß§å§Ø§Ö§ß §Õ§Ý§ñ CanOpen, §á§ã§à§Ü§à§Ý§î§Ü§å §â§Ö§Ô§Ú§ã§ä§â§à§Ó§Ñ§ñ §Þ§à§Õ§Ö§Ý§î §à§Ò§â§Ñ§Ò§Ñ§ä§í§Ó§Ñ§Ö§ä§ã§ñ §Ó §á§Ö§â§Ö§í§Ó§Ñ§ß§Ú§Ú
//§ª §Ù§Ñ§Ó§Ú§ã§Ñ§ä§î §Ó §ß§Ö§Þ §ß§Ñ §à§Ø§Ú§Õ§Ñ§ß§Ú§Ö §Ù§Ñ§á§Ú§ã§Ú EEPROM §ß§Ö §Ý§å§é§Ñ§ñ §Ú§Õ§Ö§ñ.
void WriteRegAfterDelay( u16 reg_adress, void * data, u8 len)
{
    u8 Buffer[4];
    memcpy(Buffer,data,len);
    switch (len)
    {
        default:
            setReg8(reg_adress, Buffer[0]);
            break;
        case 2:
            setReg16(reg_adress, *((u16 *)Buffer));
            break;
        case 4:
            setReg32(reg_adress, *((u32 *)Buffer));
            break;
    }
    if ((reg_adress < EEPROM_REGISER_COUNT) || (reg_adress==BITRATE) || (reg_adress==NODE_ID))
    {
        EEPROM_REG_Q_t reg_data;
        reg_data.addr = reg_adress;
        reg_data.len = len;
        xQueueSend(  pDataRegQueue, &reg_data, portMAX_DELAY );
    }
}
//§¶§å§ß§Ü§è§Ú§ñ §Ñ§ß§Ñ§Ý§à§Ô§Ú§é§ß§Ñ §á§â§Ö§Õ§Ú§Õ§å§ë§Ö§Û, §ä§à§Ý§î§Ü§à §á§â§à§Ú§Ù§Ó§à§Õ§Ú§ä §Ù§Ñ§á§Ú§ã§î §â§Ö§Ô§Ú§ã§ä§â§Ñ §Ó §ã§Ó§à§Ö§Þ §Ó§í§Ù§à§Ó§Ö.
//§°§ã§ä§Ñ§ß§à§Ó§Ñ§Ý§Ú§Ó§Ñ§Ö§ä §â§Ñ§Ò§à§ä§å §á§â§à§è§Ö§ã§ã§Ñ, §Õ§à §ä§Ö§ç §á§à§â, §á§à§Ü§Ñ §ß§Ö §Ù§Ñ§Ó§Ö§â§ê§Ú§ä§î§ã§ñ §Ù§Ñ§á§Ú§ã§î §Ó §â§Ö§Ô§Ú§ã§ä§â.
void WriteReg( u16 reg_adress, void * data, u8 len)
{
    u8 Buffer[4];
    memcpy(Buffer,data,len);
    switch (len)
    {
        default:
            setReg8(reg_adress, Buffer[0]);
            break;
        case 2:
            setReg16(reg_adress, *((u16 *)Buffer));
            break;
        case 4:
            setReg32(reg_adress, *((u32 *)Buffer));
            break;
    }
    if (reg_adress < EEPROM_REGISER_COUNT)
        eEEPROMWr(reg_adress,Buffer,len,2);
}


/*
 * §£§à§Ù§Ó§â§Ñ§ë§Ñ§Ö§Þ §Ù§ß§Ñ§é§Ö§ß§Ú§Ö §ã§Ü§à§â§à§ã§ä§Ú CAN §Ú§Ù EEPROM
 */
uint16_t vGetBitrate()
{
   return (OB->Data0 & 0xFF);
}

uint16_t vFDGetNMTState( void )
{
    return (CO_NMT_STARTUP_TO_OPERATIONAL);
}

uint8_t vGetNodeId( void )
{
  return ( OB->Data1 & 0xFF );
}

void vSetBitrate( uint8_t data)
{
    ProgramOptionByteData(0,data) ;
}

void vSetNodeID( uint8_t data)
{
    ProgramOptionByteData(1,data) ;
}

/*
 * §°§Ò§â§Ñ§Ò§à§ä§é§Ú§Ü §á§â§Ö§â§í§Ó§Ñ§ß§Ú§ñ §à§ä §ã§Ö§Ü§å§ß§Õ§ß§à§Ô§à §ä§Ñ§Û§Þ§Ö§â§Ñ RTC
 */
void vIncrementSystemCounters()
{
    u32 temp_odometr;
    if (++secondcounter >=  360 )
    {
        setReg32(HOUR_COUNTER_ADR,  (uint32_t)(getReg32(HOUR_COUNTER_ADR) + 1) );
        secondcounter = 0;
    }
    u32 distance = ((float)getODValue( getReg8(ODOMETR_MAP),0))/10.0/3.6;
    temp_odometr = getReg32(ODOMETR_ADR)  + distance;
    if ( temp_odometr > 9999990 )  temp_odometr = 0;
    setReg32(ODOMETR_ADR,  temp_odometr );
    temp_odometr = getReg32(ODOMETR1_ADR) + distance;
    if ( temp_odometr > 999990 ) temp_odometr = 0;
    setReg32(ODOMETR1_ADR, temp_odometr);
    return;
}

void vSaveData()
{
    eEEPROMWrFast(HOUR_COUNTER_ADR,GetRegisterAddr(HOUR_COUNTER_ADR),12);
}

u32 getOdometr()
{
    return (getReg32(ODOMETR_ADR)/100);
}

u32 getOdometr1()
{
    return (getReg32(ODOMETR1_ADR)/100);
}

void ResrtOdometr1()
{
    setReg32(ODOMETR1_ADR,0);
}

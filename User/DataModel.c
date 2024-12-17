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


__attribute__((section(".stext"))) static const uint16_t CalPoint[18][2] = {
                                  {130,89},
                                  {120,113},
                                  {110,110},
                                  {100,187},
                                  {90,243},
                                  {80,323},
                                  {70,436},
                                  {60,596},
                                  {50,834},
                                  {40,1175},
                                  {30,1707},
                                  {20,2500},
                                  {10,3792},
                                  {0,5896},
                                  {-10,9397},
                                  {-20,15462},
                                  {-30,26114},
                                  {-40,45313}

};


/*__attribute__((section(".stext"))) static const uint16_t CalPoint1[8][2] = {
                            //      {35,1},
                                  {32,18},
                                  {22,90},
                                  {17,159},
                                  {5,250},
                                  {1,380}};

*/
__attribute__((section(".stext"))) static const uint16_t CalPoint1[8][2] = {
                            //      {35,1},
                                  {32,163},
                                  {30,134},
                                  {25,96},
                                  {20,79},
                                  {15,62},
                                  {10,51},
                                  {5,35},
                                  {0,32}};


static u16 secondcounter;
static u32 odometr;
static uint8_t DATA_MODEL_REGISTER[TOTAL_REGISTER_COUNT];
static QueueHandle_t    pDataRegQueue;


QueueHandle_t * xDataRegQueue( void )
{
  return  (&pDataRegQueue);
}


void vDataModelRegDelayWrite()
{
    if ( uxQueueMessagesWaiting(pDataRegQueue) != 0)
    {
        EEPROM_REG_Q_t reg_data;
        xQueueReceive( pDataRegQueue, &reg_data,portMAX_DELAY );
        eEEPROMWr(reg_data.addr, &DATA_MODEL_REGISTER[reg_data.addr],reg_data.len,2);
    }
}

__attribute__((section(".stext"))) static const u8 default_data[]= { VALID_CODE, 3, 10, 10, 0x20 ,1};
__attribute__((section(".stext"))) static const u16 cal_point_index[]={AIN1_CAL_POINT_BEGIN,AIN2_CAL_POINT_BEGIN,AIN3_CAL_POINT_BEGIN};
//__attribute__((section(".stext"))) static const u16 cal_point_count_index[]={AIN1_CAL_POINT_COUNT,AIN2_CAL_POINT_COUNT,AIN3_CAL_POINT_COUNT};
__attribute__((section(".stext"))) static const u16 seg_const[]={0x336, 0x03F, 0x2F3 , 0x0F3, 0x0f6, 0x038 , 0x0CF , 0x0E6 , 0x0ED};



 void DataModel_Init()
{



    if ( eEEPROMRd(0x00 ,DATA_MODEL_REGISTER , EEPROM_REGISER_COUNT,2) == EEPROM_OK)
    {
         if (DATA_MODEL_REGISTER[VALID_CODE_ADDRES]!=VALID_CODE )
         {
             memset(DATA_MODEL_REGISTER,0,TOTAL_REGISTER_COUNT);
             memcpy(DATA_MODEL_REGISTER,default_data,6);
             DATA_MODEL_REGISTER[BITRATE_ADR ]                = 3;
             setReg16(BAR_VALUE_HIGH        ,320);
             setReg16(BAR_VALUE_LOW         ,0);
             setReg16(BAR_VALUE_RED_HIGH    ,100);
             setReg16(BAR_VALUE_RED_LOW     ,0);
             setReg16(BAR_VALUE_GREEN_HIGH  ,320);
             setReg16(BAR_VALUE_GREEN_LOW   ,50);
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
             setReg16(RGB7_VALUE_GREEN_HIGH ,1000 );
             setReg16(RGB7_VALUE_GREEN_LOW  ,950 );
             setReg16(RGB7_VALUE_RED_HIGH   ,1);
             setReg16(RGB7_VALUE_RED_LOW    ,1000 );
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
             setReg16(RGB12_VALUE_GREEN_HIGH,380);
             setReg16(RGB12_VALUE_GREEN_LOW ,50);
             setReg16(RGB12_VALUE_RED_HIGH  ,380);
             setReg16(RGB12_VALUE_RED_LOW   ,1);
             setReg16(RGB12_VALUE_BLUE_HIGH ,380);
             setReg16(RGB12_VALUE_BLUE_LOW  ,100);
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
           //  setReg16(RGB13_VALUE_RED_HIGH  ,0);
            //setReg16(RGB13_VALUE_RED_LOW   ,0);
             //setReg16(RGB13_VALUE_BLUE_HIGH ,0);
            // setReg16(RGB13_VALUE_BLUE_LOW  ,0);
             setReg16(RGB14_VALUE_GREEN_HIGH,1);
             setReg16(RGB14_VALUE_GREEN_LOW ,1);
            // setReg16(RGB14_VALUE_RED_HIGH  ,0);
           //  setReg16(RGB14_VALUE_RED_LOW   ,0);
           //  setReg16(RGB14_VALUE_BLUE_HIGH ,0);
          //  setReg16(RGB14_VALUE_BLUE_LOW  ,0);
             DATA_MODEL_REGISTER[RGBMAP1]  =vCHANNEL6;
             DATA_MODEL_REGISTER[RGBMAP2]  =vCHANNEL2;
             DATA_MODEL_REGISTER[RGBMAP3]  =0;
             DATA_MODEL_REGISTER[RGBMAP4]  =0;
             DATA_MODEL_REGISTER[RGBMAP5]  =chAKB;
             DATA_MODEL_REGISTER[RGBMAP6]  =vCHANNEL1 ;
             DATA_MODEL_REGISTER[RGBMAP8]  =0;
             DATA_MODEL_REGISTER[RGBMAP7]  =vCHANNEL16;
             DATA_MODEL_REGISTER[RGBMAP9]  =vCHANNEL3 ;
             DATA_MODEL_REGISTER[RGBMAP12] =chAIN3;
             DATA_MODEL_REGISTER[RGBMAP10] =0;
             DATA_MODEL_REGISTER[RGBMAP11] =0;
             DATA_MODEL_REGISTER[RGBMAP13] =vCHANNEL4;
             DATA_MODEL_REGISTER[RGBMAP14] =vCHANNEL3 ;
             DATA_MODEL_REGISTER[BARMAP]   =chAIN3;
             for (u8 i=0; i<9;i++)
                 setReg16(BIG_SEGVAL1 + i*sizeof (u16), seg_const[i]);

             DATA_MODEL_REGISTER[ODOMETR_MAP] = chRPM2;
             setReg32(ODOMETR_ADR       ,0x1000);
             DATA_MODEL_REGISTER[AIN1_CAL_POINT_COUNT] = 18;
             setReg16(AIN1_OFFSET,AIN_OFFSET );
             DATA_MODEL_REGISTER[AIN2_CAL_POINT_COUNT] = 18;
             setReg16(AIN2_OFFSET,AIN_OFFSET );
             DATA_MODEL_REGISTER[AIN3_CAL_POINT_COUNT] = 8;
             setReg16(AIN3_OFFSET,0 );
             for (u8 i=0; i< 18;i++)
             {
                 setReg16(AIN1_CAL_POINT_BEGIN + i*4    , CalPoint[i][0]);
                 setReg16(AIN1_CAL_POINT_BEGIN + i*4 + 2, CalPoint[i][1]);
                 setReg16(AIN2_CAL_POINT_BEGIN + i*4    , CalPoint[i][0]);
                 setReg16(AIN2_CAL_POINT_BEGIN + i*4 + 2, CalPoint[i][1]);
             }
             for (u8 i=0; i<8;i++)
             {
                  setReg16(AIN3_CAL_POINT_BEGIN + i*4    , CalPoint1[i][0]);
                  setReg16(AIN3_CAL_POINT_BEGIN + i*4 + 2, CalPoint1[i][1]);
             }
             setReg16(RPM1_COOF,1);
             setReg16(RPM2_COOF,10);
             setReg32( MENU2_MAP , 0x3E000000 | chAKB );
             setReg32( MENU3_MAP , 0x76000000 | chHOUR );
             //setReg32( MENU4_MAP , 0x783F0000 | chAIN2);
             setReg32( MENU4_MAP , 0x71000000 | chAIN3);
             setReg32( MENU5_MAP , 0x78790000 | vCHANNEL16);
             setReg32( MENU1_MAP ,  0x50730000 | vCHANNEL15);
             setReg32( MENU6_MAP , 0x6D000000 | chRPM2);
             setReg32( MENU7_MAP , 0x3F000000 | chODOMETR);
             setReg32( MENU8_MAP , chErrorRegister);
              setReg32( MENU9_MAP , 0);
             setReg32( MENU10_MAP , 0);
             DATA_MODEL_REGISTER[MENU_DEF_POS]             = 0;
             DATA_MODEL_REGISTER[MENU_HOME_BACK_TIME]      = 10;
             DATA_MODEL_REGISTER[DIN_ACTIVE_STATE]         = 0;
             DATA_MODEL_REGISTER[KEY_CONTROL_REG]     =1;
             eEEPROMWr(VALID_CODE_ADDRES,DATA_MODEL_REGISTER,EEPROM_REGISER_COUNT,2);
             memset(DATA_MODEL_REGISTER,0,EEPROM_REGISER_COUNT);
             vTaskDelay(10);
             eEEPROMRd(0x00 ,DATA_MODEL_REGISTER , EEPROM_REGISER_COUNT,2);
         }

         POINT_t point[2];
         for (u8 k = 0; k < 3 ;k++)
         {
            u8 cal_point_count  = DATA_MODEL_REGISTER[AIN1_CAL_POINT_COUNT + k *3 ];
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
         odometr =  getReg32(ODOMETR_ADR);

    }
    secondcounter = 0;
}

 void setReg32( u16 reg_adress, u32 data)
 {
     DATA_MODEL_REGISTER[ reg_adress]     = (u8)( data & 0xFF);
     DATA_MODEL_REGISTER[ reg_adress + 1] = (u8)( data>>8 & 0xFF);
     DATA_MODEL_REGISTER[ reg_adress + 2] = (u8)( data>>16 & 0xFF);
     DATA_MODEL_REGISTER[ reg_adress + 3] = (u8)( data>>24 & 0xFF);
 }

void setReg16( u16 reg_adress, u16 data)
{

    DATA_MODEL_REGISTER[ reg_adress] = (u8)( data & 0xFF);
    DATA_MODEL_REGISTER[ reg_adress + 1] =(u8)( data>>8 & 0xFF);
}

void setReg8( u16 reg_adress, u8 data)
{
    DATA_MODEL_REGISTER[ reg_adress] = (u8)( data );
}


void SaveReg16(u16 reg_adress, u8 notyfy_index )
{
    eEEPROMWr(reg_adress, &DATA_MODEL_REGISTER[reg_adress],2,notyfy_index );
}


u16 getReg16(u16 reg_adress )
{
    uint16_t  data =  (u16)DATA_MODEL_REGISTER[reg_adress] | (u16)(DATA_MODEL_REGISTER[reg_adress+1])<<8;
    return  data;
}

u32 getReg32(u16 reg_adress )
{
    u32 data = (u32)DATA_MODEL_REGISTER[reg_adress] | (u32)(DATA_MODEL_REGISTER[reg_adress+1])<<8 |
            (u32)DATA_MODEL_REGISTER[reg_adress+2]<<16 | (u32)(DATA_MODEL_REGISTER[reg_adress+3])<<24;
    return  (data);
}

u8 getReg8( u16 reg_adress)
{
    return DATA_MODEL_REGISTER[reg_adress];
}


void WriteRegAfterDelay( u16 reg_adress, void * data, u8 len)
{
    u8 Buffer[4];
    memcpy(Buffer,data,len);
    switch (len)
    {
        case 1:
            DATA_MODEL_REGISTER[reg_adress] = Buffer[0];
            break;
        case 2:
            setReg16(reg_adress, *((u16 *)Buffer));
            break;
        case 4:
            setReg32(reg_adress, *((u32 *)Buffer));
            break;
    }
    if (reg_adress < EEPROM_REGISER_COUNT)
    {
        EEPROM_REG_Q_t reg_data;
        reg_data.addr = reg_adress;
        reg_data.len = len;
        xQueueSend(  pDataRegQueue, &reg_data, portMAX_DELAY );
    }
}

void WriteReg( u16 reg_adress, void * data, u8 len)
{
    u8 Buffer[4];
    memcpy(Buffer,data,len);
    switch (len)
    {
        case 1:
            DATA_MODEL_REGISTER[reg_adress] = Buffer[0];
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

#define MAX_BITRATE_INDEX 8
static const u16 bitrate_table[MAX_BITRATE_INDEX]={1000,125,250,250,125,125,50,20};
/*
 * §£§à§Ù§Ó§â§Ñ§ë§Ñ§Ö§Þ §Ù§ß§Ñ§é§Ö§ß§Ú§Ö §ã§Ü§à§â§à§ã§ä§Ú CAN §Ú§Ù EEPROM
 */
uint16_t vGetBitrate()
{
   u8 index = bReadEEPROM( BITRATE_ADR,2 );
   return (index <= MAX_BITRATE_INDEX ) ? bitrate_table[index] : 500;
}

uint16_t vFDGetNMTState( void )
{
    return (CO_NMT_STARTUP_TO_OPERATIONAL);
}


uint8_t vGetNodeId( void )
{
  return ( getReg8( NODE_ID) );
}

/*
 * §°§Ò§â§Ñ§Ò§à§ä§é§Ú§Ü §á§â§Ö§â§í§Ó§Ñ§ß§Ú§ñ §à§ä §ã§Ö§Ü§å§ß§Õ§ß§à§Ô§à §ä§Ñ§Û§Þ§Ö§â§Ñ RTC
 */
void vIncrementSystemCounters()
{
    if (++secondcounter >= 360 )
    {
        setReg32(HOUR_COUNTER_ADR,  getReg32(HOUR_COUNTER_ADR) + 1 );
        secondcounter = 0;
    }
    setReg32(ODOMETR_ADR, getReg32(ODOMETR_ADR) + ((float)getODValue( DATA_MODEL_REGISTER[ODOMETR_MAP],0))/10.0/3.6);
    return;
}

void vSaveData()
{
  //  setReg32(ODOMETR_ADR, odometr/100);
    eEEPROMWrFast(HOUR_COUNTER_ADR,&DATA_MODEL_REGISTER[HOUR_COUNTER_ADR],8);
}

u32 getOdometr()
{
    return (getReg32(ODOMETR_ADR)/100);
}




/*
 * DataModel.c
 *
 *  Created on: Feb 23, 2024
 *      Author: i.dymov
 */

#include "DataModel.h"
#include "301/CO_NMT_Heartbeat.h"
#include "OD.h"
#include "dash_draw.h"
#include "hw_lib_eeprom.h"

const uint16_t CalPoint[20][2] = {{0,32742},
                                 {5,25451},
                                 {10,19936},
                                 {15,15731},
                                 {17,14337},
                                 {18,13693},
                                 {20,12500},
                                 {21,11948},
                                 {22,11423},
                                 {23,10925},
                                 {25,10000},
                                 {26,9570},
                                 {27,9162},
                                 {28,8773},
                                 {29,8403},
                                 {30,8051},
                                 {35,6523},
                                 {40,5315},
                                 {45,4355},
                                 {50,3593}
};
//static u32 hourcounter;
static u16 secondcounter;
static u32 odometr;
static u8 data_init = 0;






uint8_t DATA_MODEL_REGISTER[TOTAL_REGISTER_COUNT];
void InitDataModel()
{
    memset(DATA_MODEL_REGISTER,0,TOTAL_REGISTER_COUNT);
    if ( eEEPROMRd(0x00 ,DATA_MODEL_REGISTER , EEPROM_REGISER_COUNT,0) == EEPROM_OK)
    {
         if (DATA_MODEL_REGISTER[VALID_CODE_ADDRES]!=VALID_CODE )
         {
             DATA_MODEL_REGISTER[BITRATE_ADR ]                     = 2;
             DATA_MODEL_REGISTER[VALID_CODE_ADDRES]                = VALID_CODE;
             DATA_MODEL_REGISTER[WHITE_BRIGTH_ADR]                 = MAX_BRIGTH;
             DATA_MODEL_REGISTER[RGB_BRIGTH_ADR]                   = MAX_BRIGTH;
             *((u16*)&(DATA_MODEL_REGISTER[ BAR_VALUE_HIGH]))   =  36;
             *((u16*)&(DATA_MODEL_REGISTER[BAR_VALUE_LOW]))     =  0;
             *((u16*)&(DATA_MODEL_REGISTER[ BAR_VALUE_RED_HIGH]))  = 5;
             *((u16*)&(DATA_MODEL_REGISTER[BAR_VALUE_RED_LOW]))    = 0;
             *((u16*)&(DATA_MODEL_REGISTER[BAR_VALUE_GREEN_HIGH])) = 36;
             *((u16*)&(DATA_MODEL_REGISTER[BAR_VALUE_GREEN_LOW])) =  5;
             *((u16*)&(DATA_MODEL_REGISTER[BITRATE_ADR ])) = 2;
             *((u16*)&(DATA_MODEL_REGISTER[NODE_ID_ADR])) = 0x16;
             *((u16*)&(DATA_MODEL_REGISTER[RGB1_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB1_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB1_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB1_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB1_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB1_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB2_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB2_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB2_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB2_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB2_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB2_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB3_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB3_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB3_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB3_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB3_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB3_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB4_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB4_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB4_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB4_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB4_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB4_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB5_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB5_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB5_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB5_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB5_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB5_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB6_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB6_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB6_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB6_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB6_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB6_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB7_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB7_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB7_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB7_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB7_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB7_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB8_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB8_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB8_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB8_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB8_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB8_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB9_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB9_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB9_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB9_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB9_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB9_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB10_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB10_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB10_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB10_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB10_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB10_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB11_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB11_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB11_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB11_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB11_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB11_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB12_VALUE_GREEN_HIGH])) = 0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB12_VALUE_GREEN_LOW]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB12_VALUE_RED_HIGH]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB12_VALUE_RED_LOW]))     =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB12_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB12_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB13_VALUE_GREEN_HIGH])) = 2;
             *((u16*)&(DATA_MODEL_REGISTER[RGB13_VALUE_GREEN_LOW]))   =1;
             *((u16*)&(DATA_MODEL_REGISTER[RGB13_VALUE_RED_HIGH]))    =2;
             *((u16*)&(DATA_MODEL_REGISTER[RGB13_VALUE_RED_LOW]))     =2;
             *((u16*)&(DATA_MODEL_REGISTER[RGB13_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB13_VALUE_BLUE_LOW]))    =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB14_VALUE_GREEN_HIGH])) = 2;
             *((u16*)&(DATA_MODEL_REGISTER[RGB14_VALUE_GREEN_LOW]))   =1;
             *((u16*)&(DATA_MODEL_REGISTER[RGB14_VALUE_RED_HIGH]))    =2;
             *((u16*)&(DATA_MODEL_REGISTER[RGB14_VALUE_RED_LOW]))     =2;
             *((u16*)&(DATA_MODEL_REGISTER[RGB14_VALUE_BLUE_HIGH]))   =0;
             *((u16*)&(DATA_MODEL_REGISTER[RGB14_VALUE_BLUE_LOW]))    =0;
             DATA_MODEL_REGISTER[RGBMAP1]  =0;
             DATA_MODEL_REGISTER[RGBMAP2]  =0;
             DATA_MODEL_REGISTER[RGBMAP3]  =0;
             DATA_MODEL_REGISTER[RGBMAP4]  =0;
             DATA_MODEL_REGISTER[RGBMAP5]  =0;
             DATA_MODEL_REGISTER[RGBMAP6]  =0;
             DATA_MODEL_REGISTER[RGBMAP7]  =0;
             DATA_MODEL_REGISTER[RGBMAP8]  =0;
             DATA_MODEL_REGISTER[RGBMAP9]  =0;
             DATA_MODEL_REGISTER[RGBMAP10] =0;
             DATA_MODEL_REGISTER[RGBMAP11] =0;
             DATA_MODEL_REGISTER[RGBMAP12] =0;
             DATA_MODEL_REGISTER[RGBMAP13] =1;
             DATA_MODEL_REGISTER[RGBMAP14] =2;
             DATA_MODEL_REGISTER[BARMAP] =0;
             *((u16*)&(DATA_MODEL_REGISTER[BIG_SEGVAL1 ])) =0;
             *((u16*)&(DATA_MODEL_REGISTER[BIG_SEGVAL2 ])) =0;
             *((u16*)&(DATA_MODEL_REGISTER[BIG_SEGVAL3 ])) =0;
             *((u16*)&(DATA_MODEL_REGISTER[BIG_SEGVAL4 ])) =0;
             *((u16*)&(DATA_MODEL_REGISTER[BIG_SEGVAL5 ])) =0;
             *((u16*)&(DATA_MODEL_REGISTER[BIG_SEGVAL6 ])) =0;
             *((u16*)&(DATA_MODEL_REGISTER[BIG_SEGVAL7 ])) =0;
             *((u16*)&(DATA_MODEL_REGISTER[BIG_SEGVAL8 ])) =0;
             *((u16*)&(DATA_MODEL_REGISTER[BIG_SEGVAL9 ])) =0;
             *((u32 *)(&DATA_MODEL_REGISTER[HOUR_COUNTER_ADR])) = 0x00;
             *((u32 *)(&DATA_MODEL_REGISTER[ODOMETR_ADR])) = 0x00;
             DATA_MODEL_REGISTER[AIN1_CAL_POINT_COUNT] = 19;
             DATA_MODEL_REGISTER[AIN2_CAL_POINT_COUNT] = 19;
             DATA_MODEL_REGISTER[AIN3_CAL_POINT_COUNT] = 19;
             for (u8 i=0; i< 19;i++)
             {
                 *((u16*)&(DATA_MODEL_REGISTER[AIN1_CAL_POINT_BEGIN + i*4])) =  CalPoint[i][0]*10;
                 *((u16*)&(DATA_MODEL_REGISTER[AIN1_CAL_POINT_BEGIN + i*4 + 2 ])) =  CalPoint[i][1];
                 *((u16*)&(DATA_MODEL_REGISTER[AIN2_CAL_POINT_BEGIN + i*4])) =  CalPoint[i][0]*10;
                 *((u16*)&(DATA_MODEL_REGISTER[AIN2_CAL_POINT_BEGIN + i*4 + 2 ])) =  CalPoint[i][1];
                 *((u16*)&(DATA_MODEL_REGISTER[AIN3_CAL_POINT_BEGIN + i*4])) =  CalPoint[i][0]*10;
                 *((u16*)&(DATA_MODEL_REGISTER[AIN3_CAL_POINT_BEGIN + i*4 + 2 ])) =  CalPoint[i][1];
             }
             *((u16*)&(DATA_MODEL_REGISTER[RPM1_COOF ])) = 1000;
             *((u16*)&(DATA_MODEL_REGISTER[RPM2_COOF ])) = 1000;

             *((u32*)&(DATA_MODEL_REGISTER[ MENU1_MAP ])) =0;
             *((u32*)&(DATA_MODEL_REGISTER[ MENU2_MAP ])) =0;
             *((u32*)&(DATA_MODEL_REGISTER[ MENU3_MAP ])) =0;
             *((u32*)&(DATA_MODEL_REGISTER[ MENU4_MAP ])) =0;
             *((u32*)&(DATA_MODEL_REGISTER[ MENU5_MAP ])) =0;
             *((u32*)&(DATA_MODEL_REGISTER[ MENU6_MAP ])) =0;
             *((u32*)&(DATA_MODEL_REGISTER[ MENU7_MAP ])) =0;
             *((u32*)&(DATA_MODEL_REGISTER[ MENU8_MAP ])) =0;
             *((u32*)&(DATA_MODEL_REGISTER[ MENU9_MAP ])) =0;
             *((u32*)&(DATA_MODEL_REGISTER[ MENU10_MAP ])) =0;
             DATA_MODEL_REGISTER[MENU_DEF_POS]             =0;
             DATA_MODEL_REGISTER[MENU_HOME_BACK_TIME]      =1;
             eEEPROMWr(VALID_CODE_ADDRES,DATA_MODEL_REGISTER,EEPROM_REGISER_COUNT,0);
             memset(DATA_MODEL_REGISTER,0,EEPROM_REGISER_COUNT);
             eEEPROMRd(0x00 ,DATA_MODEL_REGISTER , EEPROM_REGISER_COUNT,0);
         }
         data_init  = 1;
         OD_set_value(OD_ENTRY_H2024,0x00 ,&DATA_MODEL_REGISTER[ BITRATE_ADR],1, true);
         //§¥§Ñ§ß§ß§í§Ö §Ò§à§Ý§î§ê§à§Ô§à §ã§Ö§Ô§Þ§Ö§ß§ä§ß§Ú§Ü§Ñ
         for (int j = 0; j< 9;j++)
         {
             OD_set_value(OD_ENTRY_H2007, j+2 ,&DATA_MODEL_REGISTER[BIG_SEGVAL1+j*2], 2, true);
         }
         OD_set_value(OD_ENTRY_H2019,0x06 ,&DATA_MODEL_REGISTER[ BAR_VALUE_HIGH],2, true);
         OD_set_value(OD_ENTRY_H2019,0x05 ,&DATA_MODEL_REGISTER[BAR_VALUE_LOW], 2, true);
         OD_set_value(OD_ENTRY_H2019,0x01 ,&DATA_MODEL_REGISTER[ BAR_VALUE_RED_HIGH],2, true);
         OD_set_value(OD_ENTRY_H2019,0x02 ,&DATA_MODEL_REGISTER[BAR_VALUE_RED_LOW], 2, true);
         OD_set_value(OD_ENTRY_H2019,0x03 ,&DATA_MODEL_REGISTER[BAR_VALUE_GREEN_HIGH],2, true);
         OD_set_value(OD_ENTRY_H2019,0x04 ,&DATA_MODEL_REGISTER[BAR_VALUE_GREEN_LOW], 2, true);


             for (int j= 0; j<RGB_DIOD_COUNT; j++)
             {
                 OD_set_value(OD_ENTRY_H2008, j+1 ,&DATA_MODEL_REGISTER[RGBMAP1 +j], 1, true);
                 for (int i = 0; i < 6; i++ )
                     OD_set_value(&OD->list[34+j], i+1 ,&DATA_MODEL_REGISTER[RGB1_VALUE_GREEN_HIGH +i*2], 2, true);
             }
             OD_set_value(OD_ENTRY_H2008, 15 ,&DATA_MODEL_REGISTER[BARMAP], 1, true);
             vSetInitBrigth(RGB_CHANNEL,DATA_MODEL_REGISTER[RGB_BRIGTH_ADR] );
             vSetInitBrigth(WHITE_CHANNEL,DATA_MODEL_REGISTER[WHITE_BRIGTH_ADR] );
             u32 data32 = getReg32(HOUR_COUNTER_ADR);
             OD_set_value(OD_ENTRY_H2004,0x02,&data32,4,true);
             odometr     = getReg32(ODOMETR_ADR);
             OD_set_value(OD_ENTRY_H2004,0x01,&odometr,4,true);
             odometr     = odometr * 100;
             POINT_t point;
             u8 cal_point_count  = DATA_MODEL_REGISTER[AIN1_CAL_POINT_COUNT];
             data32 = (u32) cal_point_count;
             OD_set_value(OD_ENTRY_H2030, 1 ,&data32, 4, true);
             if ( eAinCalDataConfig(AIN1,cal_point_count ) == CAL_SUCCESS)
             {
                 for (u8 i = 1; i<= cal_point_count;i++)
                 {
                     u16 data16  = *((u16*)&(DATA_MODEL_REGISTER[AIN1_CAL_POINT_BEGIN + i*4]));
                     point.X = (float)data16;
                     OD_set_value(OD_ENTRY_H2030, 2+i*2 ,&data16, 2, true);
                     data16 = (*((u16*)&(DATA_MODEL_REGISTER[AIN1_CAL_POINT_BEGIN + i*4 + 2 ])));
                     point.Y = (float)data16/10;
                     OD_set_value(OD_ENTRY_H2030, 3+i*2 ,&data16, 2, true);
                     eSetAinCalPoint(AIN1,&point, i);
                 }
             }
             cal_point_count  = DATA_MODEL_REGISTER[AIN2_CAL_POINT_COUNT];
             data32 = (u32) cal_point_count;
             OD_set_value(OD_ENTRY_H2031, 1 ,&data32, 4, true);
             if ( eAinCalDataConfig(AIN2,cal_point_count ) == CAL_SUCCESS)
             {
                    for (u8 i = 1; i<= cal_point_count;i++)
                    {
                        u16 data16  = *((u16*)&(DATA_MODEL_REGISTER[AIN2_CAL_POINT_BEGIN + i*4]));
                        point.X = (float)data16;
                        OD_set_value(OD_ENTRY_H2031, 2+i*2 ,&data16, 2, true);
                        data16 = (*((u16*)&(DATA_MODEL_REGISTER[AIN2_CAL_POINT_BEGIN + i*4 + 2 ])));
                        point.Y = (float)data16/10;
                        OD_set_value(OD_ENTRY_H2031, 3+i*2 ,&data16, 2, true);
                       eSetAinCalPoint(AIN2,&point, i);
                     }

               }
              cal_point_count  = DATA_MODEL_REGISTER[AIN3_CAL_POINT_COUNT];
              data32 = (u32) cal_point_count;
              OD_set_value(OD_ENTRY_H2032, 1 ,&data32, 4, true);
              if ( eAinCalDataConfig(AIN2,cal_point_count ) == CAL_SUCCESS)
              {
                    for (u8 i = 1; i<= cal_point_count;i++)
                    {
                        u16 data16  = *((u16*)&(DATA_MODEL_REGISTER[AIN3_CAL_POINT_BEGIN + i*4]));
                        point.X = (float)data16;
                        OD_set_value(OD_ENTRY_H2031, 2+i*2 ,&data16, 2, true);
                        data16 = (*((u16*)&(DATA_MODEL_REGISTER[AIN3_CAL_POINT_BEGIN + i*4 + 2 ])));
                        point.Y = (float)data16/10;
                        OD_set_value(OD_ENTRY_H2032, 3+i*2 ,&data16, 2, true);
                        eSetAinCalPoint(AIN3,&point, i);
                    }
               }
              OD_set_value(OD_ENTRY_H2033, 1 ,&DATA_MODEL_REGISTER[MENU_DEF_POS], 1, true);
              OD_set_value(OD_ENTRY_H2033, 2 ,&DATA_MODEL_REGISTER[MENU_HOME_BACK_TIME], 1, true);
              OD_set_value(OD_ENTRY_H201B, 2 ,&DATA_MODEL_REGISTER[RPM2_COOF], 2, true);
              OD_set_value(OD_ENTRY_H201B, 3 ,&DATA_MODEL_REGISTER[RPM2_COOF], 2, true);

              for (u8 i = 0; i <10; i++)
              {
                  u32 data32  = *((u32*)&(DATA_MODEL_REGISTER[ MENU1_MAP + i*4]));
                  OD_set_value(OD_ENTRY_H201A, 1+i*4 ,&data32, 4, true);
              }
              data_init = 0;

    }
    xEventGroupSetBits(xGetSystemEventHeandler(),DATA_MODEL_READY);
    secondcounter = 0;
}




u16 setReg(u16 reg_adress, void * data, u8 len)
{
    u8 Buffer[4];
     switch (len)
     {
            case 1:
                Buffer[0] = *((u8 *)data);
                DATA_MODEL_REGISTER[reg_adress] = Buffer[0];
                break;
            case 2:
                *((u16 *)Buffer) = *((u16 *)data);
                *((u16 *)&DATA_MODEL_REGISTER[reg_adress]) = *((u16 *)Buffer);
                break;
            case 4:
                *((u32 *)Buffer) = *((u32 *)data);
                *((u32 *)&DATA_MODEL_REGISTER[reg_adress]) = *((u32 *)Buffer);
                break;
      }
}

u16 getReg16(u16 reg_adress )
{

    return  *((u16 *)&DATA_MODEL_REGISTER[reg_adress]);
}

u32 getReg32(u16 reg_adress )
{

    return  *((u32 *)&DATA_MODEL_REGISTER[reg_adress]);
}

u8 getReg8( u16 reg_adress)
{
    return DATA_MODEL_REGISTER[reg_adress];
}

void WriteReg( u16 reg_adress, void * data, u8 len)
{
    u8 Buffer[4];
    switch (len)
    {
        case 1:
            Buffer[0] = *((u8 *)data);
            DATA_MODEL_REGISTER[reg_adress] = Buffer[0];
            break;
        case 2:
            *((u16 *)Buffer) = *((u16 *)data);
            *((u16 *)&DATA_MODEL_REGISTER[reg_adress]) = *((u16 *)Buffer);
            break;
        case 4:
            *((u32 *)Buffer) = *((u32 *)data);
            *((u32 *)&DATA_MODEL_REGISTER[reg_adress]) = *((u32 *)Buffer);
            break;
    }
    if ((reg_adress < EEPROM_REGISER_COUNT) && (data_init == 0))
        eEEPROMWr(reg_adress,Buffer,len,0);
}


uint16_t vGetBitrate()
{
   uint16_t data = 0;
   switch( bReadEEPROM( BITRATE_ADR,0 ) )
    {
        case 0x00:
            data = 1000;
            break;
        case 0x02:
            data = 500;
            break;
        case 0x03:
            data = 250;
            break;
        case 0x04:
            data = 125;
            break;
        case 0x06:
            data =50;
            break;
        case 0x07:
            data = 20;
            break;
        default:
            data = 125;
            break;
    }
    return data;
}

uint16_t vFDGetNMTState( void )
{

     return (CO_NMT_STARTUP_TO_OPERATIONAL);
}


uint8_t vGetNodeId( void )
{
  return ( bReadEEPROM( NODE_ID_ADR,0) );
}

void vIncrementSystemCounters()
{
    if (++secondcounter>=360)
    {
        (*((u32 *)&DATA_MODEL_REGISTER[HOUR_COUNTER_ADR])) ++;
        secondcounter = 0;
    }
    odometr = odometr + getODValue( DATA_MODEL_REGISTER[ODOMETR_MAP])/3.6;
    return;
}

void vSaveData()
{
    *((u32 *)(&DATA_MODEL_REGISTER[ODOMETR_ADR])) = odometr/100;
    eEEPROMWr(HOUR_COUNTER_ADR,&DATA_MODEL_REGISTER[HOUR_COUNTER_ADR],8,0);
}

u32 getOdometr()
{
    return (odometr/100);
}




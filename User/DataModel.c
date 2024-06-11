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
#include "hw_lib_eeprom.h"

const uint16_t CalPoint[18][2] = {
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
//static u32 hourcounter;
static u16 secondcounter;
static u32 odometr;
//static u8 data_init = 0;

static uint8_t DATA_MODEL_REGISTER[TOTAL_REGISTER_COUNT];




 void DataModel_Init()
{
    memset(DATA_MODEL_REGISTER,0,TOTAL_REGISTER_COUNT);
    if ( eEEPROMRd(0x00 ,DATA_MODEL_REGISTER , EEPROM_REGISER_COUNT,2) == EEPROM_OK)
    {
         if (DATA_MODEL_REGISTER[VALID_CODE_ADDRES]!=VALID_CODE )
         {
             DATA_MODEL_REGISTER[BITRATE_ADR ]                = 2;
             DATA_MODEL_REGISTER[NODE_ID]                     = 0x20;
             DATA_MODEL_REGISTER[VALID_CODE_ADDRES]           = VALID_CODE;
             DATA_MODEL_REGISTER[WHITE_BRIGTH_ADR]            = 11;
             DATA_MODEL_REGISTER[RGB_BRIGTH_ADR]              = 14;
             DATA_MODEL_REGISTER[BAR_MODE]   = 1;
             setReg16(BAR_VALUE_HIGH        ,36);
             setReg16(BAR_VALUE_LOW         ,0);
             setReg16(BAR_VALUE_RED_HIGH    ,5);
             setReg16(BAR_VALUE_RED_LOW     ,0);
             setReg16(BAR_VALUE_GREEN_HIGH  ,36);
             setReg16(BAR_VALUE_GREEN_LOW   ,5);
             setReg16(RGB1_VALUE_GREEN_HIGH ,0);
             setReg16(RGB1_VALUE_GREEN_LOW  ,0);
             setReg16(RGB1_VALUE_RED_HIGH   ,1);
             setReg16(RGB1_VALUE_RED_LOW    ,1);
             setReg16(RGB1_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB1_VALUE_BLUE_LOW   ,0);
             setReg16(RGB2_VALUE_GREEN_HIGH ,0);
             setReg16(RGB2_VALUE_GREEN_LOW  ,0);
             setReg16(RGB2_VALUE_RED_HIGH   ,0);
             setReg16(RGB2_VALUE_RED_LOW    ,0);
             setReg16(RGB2_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB2_VALUE_BLUE_LOW   ,0);
             setReg16(RGB3_VALUE_GREEN_HIGH ,650+AIN_OFFSET );
             setReg16(RGB3_VALUE_GREEN_LOW  ,600+AIN_OFFSET );
             setReg16(RGB3_VALUE_RED_HIGH   ,1);
             setReg16(RGB3_VALUE_RED_LOW    ,650+AIN_OFFSET );
             setReg16(RGB3_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB3_VALUE_BLUE_LOW   ,0);
             setReg16(RGB4_VALUE_GREEN_HIGH ,1);
             setReg16(RGB4_VALUE_GREEN_LOW  ,1);
             setReg16(RGB4_VALUE_RED_HIGH   ,1);
             setReg16(RGB4_VALUE_RED_LOW    ,1);
             setReg16(RGB4_VALUE_BLUE_HIGH  ,3);
             setReg16(RGB4_VALUE_BLUE_LOW   ,1);
             setReg16(RGB5_VALUE_GREEN_HIGH ,0);
             setReg16(RGB5_VALUE_GREEN_LOW  ,0);
             setReg16(RGB5_VALUE_RED_HIGH   ,90);
             setReg16(RGB5_VALUE_RED_LOW    ,160);
             setReg16(RGB5_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB5_VALUE_BLUE_LOW   ,0);
             setReg16(RGB6_VALUE_GREEN_HIGH ,1);
             setReg16(RGB6_VALUE_GREEN_LOW  ,1);
             setReg16(RGB6_VALUE_RED_HIGH   ,1);
             setReg16(RGB6_VALUE_RED_LOW    ,1);
             setReg16(RGB6_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB6_VALUE_BLUE_LOW   ,0);
             setReg16(RGB7_VALUE_GREEN_HIGH ,1);
             setReg16(RGB7_VALUE_GREEN_LOW  ,1);
             setReg16(RGB7_VALUE_RED_HIGH   ,1);
             setReg16(RGB7_VALUE_RED_LOW    ,1);
             setReg16(RGB7_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB7_VALUE_BLUE_LOW   ,0);
             setReg16(RGB8_VALUE_GREEN_HIGH ,1000+AIN_OFFSET );
             setReg16(RGB8_VALUE_GREEN_LOW  ,950+AIN_OFFSET );
             setReg16(RGB8_VALUE_RED_HIGH   ,1);
             setReg16(RGB8_VALUE_RED_LOW    ,1000+AIN_OFFSET );
             setReg16(RGB8_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB8_VALUE_BLUE_LOW   ,0);
             setReg16(RGB9_VALUE_GREEN_HIGH ,3);
             setReg16(RGB9_VALUE_GREEN_LOW  ,2);
             setReg16(RGB9_VALUE_RED_HIGH   ,3);
             setReg16(RGB9_VALUE_RED_LOW    ,2);
             setReg16(RGB9_VALUE_BLUE_HIGH  ,0);
             setReg16(RGB9_VALUE_BLUE_LOW   ,0);
             setReg16(RGB10_VALUE_GREEN_HIGH,0);
             setReg16(RGB10_VALUE_GREEN_LOW ,0);
             setReg16(RGB10_VALUE_RED_HIGH  ,0);
             setReg16(RGB10_VALUE_RED_LOW   ,0);
             setReg16(RGB10_VALUE_BLUE_HIGH ,0);
             setReg16(RGB10_VALUE_BLUE_LOW  ,0);
             setReg16(RGB11_VALUE_GREEN_HIGH,0);
             setReg16(RGB11_VALUE_GREEN_LOW ,0);
             setReg16(RGB11_VALUE_RED_HIGH  ,0);
             setReg16(RGB11_VALUE_RED_LOW   ,0);
             setReg16(RGB11_VALUE_BLUE_HIGH ,0);
             setReg16(RGB11_VALUE_BLUE_LOW  ,0);
             setReg16(RGB12_VALUE_GREEN_HIGH,2);
             setReg16(RGB12_VALUE_GREEN_LOW ,2);
             setReg16(RGB12_VALUE_RED_HIGH  ,2);
             setReg16(RGB12_VALUE_RED_LOW   ,2);
             setReg16(RGB12_VALUE_BLUE_HIGH ,0);
             setReg16(RGB12_VALUE_BLUE_LOW  ,0);
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
             DATA_MODEL_REGISTER[RGBMAP1]  =chDIN1;
             DATA_MODEL_REGISTER[RGBMAP2]  =0;
             DATA_MODEL_REGISTER[RGBMAP3]  =chAIN1;
             DATA_MODEL_REGISTER[RGBMAP4]  =vCHANNEL2;
             DATA_MODEL_REGISTER[RGBMAP5]  =chAKB;
             DATA_MODEL_REGISTER[RGBMAP6]  =vCHANNEL1 ;
             DATA_MODEL_REGISTER[RGBMAP7]  =vCHANNEL5;
             DATA_MODEL_REGISTER[RGBMAP8]  =chAIN2;
             DATA_MODEL_REGISTER[RGBMAP9]  =vCHANNEL3 ;
             DATA_MODEL_REGISTER[RGBMAP10] =0;
             DATA_MODEL_REGISTER[RGBMAP11] =0;
             DATA_MODEL_REGISTER[RGBMAP12] =vCHANNEL5;
             DATA_MODEL_REGISTER[RGBMAP13] =vCHANNEL4;
             DATA_MODEL_REGISTER[RGBMAP14] =vCHANNEL3 ;
             DATA_MODEL_REGISTER[BARMAP]   =1;
             setReg16(BIG_SEGVAL1       , 0x336);
             setReg16(BIG_SEGVAL2       , 0x03F);
             setReg16(BIG_SEGVAL3       , 0x2F3);
             setReg16(BIG_SEGVAL4       , 0x0F3);
             setReg16(BIG_SEGVAL5       , 0x006);
             setReg16(BIG_SEGVAL6       , 0x0DB);
             setReg16(BIG_SEGVAL7       , 0x0CF);
             setReg16(BIG_SEGVAL8       , 0x0E6);
             setReg16(BIG_SEGVAL9       , 0x0ED);
             setReg32(HOUR_COUNTER_ADR  , 0x100);
             setReg32(ODOMETR_ADR       ,0x00);
             DATA_MODEL_REGISTER[AIN1_CAL_POINT_COUNT] = 18;
             setReg16(AIN1_OFFSET,AIN_OFFSET );
             DATA_MODEL_REGISTER[AIN2_CAL_POINT_COUNT] = 18;
             setReg16(AIN2_OFFSET,AIN_OFFSET );
             DATA_MODEL_REGISTER[AIN3_CAL_POINT_COUNT] = 18;
             setReg16(AIN3_OFFSET,AIN_OFFSET );
             for (u8 i=0; i< 18;i++)
             {
                 setReg16(AIN1_CAL_POINT_BEGIN + i*4    , CalPoint[i][0]);
                 setReg16(AIN1_CAL_POINT_BEGIN + i*4 + 2, CalPoint[i][1]);
                 setReg16(AIN2_CAL_POINT_BEGIN + i*4    , CalPoint[i][0]);
                 setReg16(AIN2_CAL_POINT_BEGIN + i*4 + 2, CalPoint[i][1]);
                 setReg16(AIN3_CAL_POINT_BEGIN + i*4    , CalPoint[i][0]);
                 setReg16(AIN3_CAL_POINT_BEGIN + i*4 + 2 ,CalPoint[i][1]);
             }
             setReg16(RPM1_COOF, RMP_OFFSET);
             setReg16(RPM2_COOF, RMP_OFFSET);
             setReg32( MENU6_MAP , 0x78790000 | chAIN1);
             setReg32( MENU2_MAP , 0x3E000000 | chAKB );
             setReg32( MENU3_MAP , 0x76000000 | chHOUR );
             setReg32( MENU4_MAP , 0x783F0000 | chAIN2);
             setReg32(MENU5_MAP ,  0x71000000 | chAIN3);;
             setReg32(MENU1_MAP ,  0x50730000 | chRPM1);
             setReg32( MENU7_MAP , 0x6D000000 | chRPM2);
             setReg32( MENU8_MAP ,0);
             setReg32( MENU9_MAP ,0);
             setReg32( MENU10_MAP , 0);
             DATA_MODEL_REGISTER[MENU_DEF_POS]             =0;
             DATA_MODEL_REGISTER[MENU_HOME_BACK_TIME]      =10;
             DATA_MODEL_REGISTER[DIN_ACTIVE_STATE]         = 0;
             eEEPROMWr(VALID_CODE_ADDRES,DATA_MODEL_REGISTER,EEPROM_REGISER_COUNT,2);
             memset(DATA_MODEL_REGISTER,0,EEPROM_REGISER_COUNT);
             vTaskDelay(10);
             eEEPROMRd(0x00 ,DATA_MODEL_REGISTER , EEPROM_REGISER_COUNT,2);
         }
        // data_init  = 1;
         //§¥§Ñ§ß§ß§í§Ö §Ò§à§Ý§î§ê§à§Ô§à §ã§Ö§Ô§Þ§Ö§ß§ä§ß§Ú§Ü§Ñ

       /*  OD_set_value(OD_ENTRY_H2019,0x06 ,&DATA_MODEL_REGISTER[BAR_VALUE_HIGH],2, true);
         OD_set_value(OD_ENTRY_H2019,0x05 ,&DATA_MODEL_REGISTER[BAR_VALUE_LOW], 2, true);
         OD_set_value(OD_ENTRY_H2019,0x01 ,&DATA_MODEL_REGISTER[BAR_VALUE_RED_HIGH],2, true);
         OD_set_value(OD_ENTRY_H2019,0x02 ,&DATA_MODEL_REGISTER[BAR_VALUE_RED_LOW], 2, true);
         OD_set_value(OD_ENTRY_H2019,0x03 ,&DATA_MODEL_REGISTER[BAR_VALUE_GREEN_HIGH],2, true);
         OD_set_value(OD_ENTRY_H2019,0x04 ,&DATA_MODEL_REGISTER[BAR_VALUE_GREEN_LOW], 2, true);


         for (int j= 0; j<RGB_DIOD_COUNT; j++)
         {
             OD_set_value(OD_ENTRY_H2008, j+1 ,&DATA_MODEL_REGISTER[RGBMAP1 +j], 1, true);
             for (int i = 0; i < 6; i++ )
                     OD_set_value(&OD->list[34+j], i+1 ,&DATA_MODEL_REGISTER[RGB1_VALUE_GREEN_HIGH +i*2], 2, true);
         }
     //    OD_set_value(OD_ENTRY_H2008, 15 ,&DATA_MODEL_REGISTER[BARMAP], 1, true);

*
             u32 data32 = getReg32(HOUR_COUNTER_ADR);
             OD_set_value(OD_ENTRY_H2004,0x02,&data32,4,true);
*/

           /*  odometr     = getReg32(ODOMETR_ADR);
            // OD_set_value(OD_ENTRY_H2004,0x01,&odometr,4,true);
             odometr     = odometr * 100;*/
             POINT_t point[2];
             u8 cal_point_count  = DATA_MODEL_REGISTER[AIN1_CAL_POINT_COUNT];
             u32 data32 = (u32) cal_point_count;
             OD_set_value(OD_ENTRY_H2030, 2 ,&data32, 4, true);
             if ( eAinCalDataConfig(AIN1,cal_point_count -1 ) == CAL_SUCCESS)
             {
                 for (u8 i = 0; i< cal_point_count - 1 ;i++)
                 {
                     int16_t data16  = (int16_t)getReg16(AIN1_CAL_POINT_BEGIN + i*4);
                     point[0].Y = (float)data16;
                     u16 udata16 = getReg16(AIN1_CAL_POINT_BEGIN + i*4 + 2);
                     point[0].X = (float)udata16;
                     data16  = (int16_t)getReg16(AIN1_CAL_POINT_BEGIN + i*4 + 4);
                     point[1].Y = (float)data16;
                     udata16 = getReg16(AIN1_CAL_POINT_BEGIN + i*4 + 6);
                     point[1].X = (float)udata16;
                     eSetAinCalPoint(AIN1,&point, i);
                     //OD_set_value(OD_ENTRY_H2030, 2+i*2 ,&data16, 2, true);

                     //OD_set_value(OD_ENTRY_H2030, 3+i*2 ,&data16, 2, true);

                 }
             }
             cal_point_count  = DATA_MODEL_REGISTER[AIN2_CAL_POINT_COUNT];
             data32 = (u32) cal_point_count;
             OD_set_value(OD_ENTRY_H2031, 1 ,&data32, 4, true);
             if ( eAinCalDataConfig(AIN2,cal_point_count ) == CAL_SUCCESS)
             {
                    for (u8 i = 1; i<= cal_point_count;i++)
                    {
                        int16_t data16  = (int16_t)getReg16(AIN2_CAL_POINT_BEGIN + i*4);
                        point[0].Y = (float)data16;
                        u16 udata16 = getReg16(AIN2_CAL_POINT_BEGIN + i*4 + 2);
                        point[0].X = (float)udata16;
                        data16  = (int16_t)getReg16(AIN2_CAL_POINT_BEGIN + i*4 + 4);
                        point[1].Y = (float)data16;
                        udata16 = getReg16(AIN2_CAL_POINT_BEGIN + i*4 + 6);
                        point[1].X = (float)udata16;

                        //OD_set_value(OD_ENTRY_H2031, 2+i*2 ,&data16, 2, true);
                       // OD_set_value(OD_ENTRY_H2031, 3+i*2 ,&data16, 2, true);
                        eSetAinCalPoint(AIN2,&point, i);
                     }

               }
              cal_point_count  = DATA_MODEL_REGISTER[AIN3_CAL_POINT_COUNT];
              data32 = (u32) cal_point_count;
              OD_set_value(OD_ENTRY_H2032, 1 ,&data32, 4, true);
              if ( eAinCalDataConfig(AIN2,cal_point_count ) == CAL_SUCCESS)
              {
                    for (u8 i = 1; i<= cal_point_count;i++)
                    {int16_t data16  = (int16_t)getReg16(AIN3_CAL_POINT_BEGIN + i*4);
                    point[0].Y = (float)data16;
                    u16 udata16 = getReg16(AIN3_CAL_POINT_BEGIN + i*4 + 2);
                    point[0].X = (float)udata16;
                    data16  = (int16_t)getReg16(AIN3_CAL_POINT_BEGIN + i*4 + 4);
                    point[1].Y = (float)data16;
                    udata16 = getReg16(AIN3_CAL_POINT_BEGIN + i*4 + 6);
                    point[1].X = (float)udata16;

                       // OD_set_value(OD_ENTRY_H2031, 2+i*2 ,&data16, 2, true);
                       // OD_set_value(OD_ENTRY_H2032, 3+i*2 ,&data16, 2, true);
                        eSetAinCalPoint(AIN3,&point, i);
                    }
               }

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

u16 setReg(u16 reg_adress, void * data, u8 len)
{
    u8 d8;
    u16 d16;
    u32 d32;
     switch (len)
     {
            case 1:
                d8 = *((u8 *)data);
                DATA_MODEL_REGISTER[reg_adress] = d8;
                break;
            case 2:
                d16 = *((u16 *)data);
                DATA_MODEL_REGISTER[ reg_adress] = d16 & 0xFF;
                DATA_MODEL_REGISTER[ reg_adress + 1] = d16>>8 & 0xFF;
                break;
            case 4:
                d32 = *((u32 *)data);
                DATA_MODEL_REGISTER[ reg_adress]     = (u8)( d32 & 0xFF);
                DATA_MODEL_REGISTER[ reg_adress + 1] = (u8)( d32>>8 & 0xFF);
                DATA_MODEL_REGISTER[ reg_adress + 2] = (u8)( d32>>16 & 0xFF);
                DATA_MODEL_REGISTER[ reg_adress + 3] = (u8)( d32>>24 & 0xFF);
                break;
      }
     return (0);
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
            setReg16(reg_adress, *((u16 *)Buffer));
            break;
        case 4:
            setReg32(reg_adress, *((u32 *)Buffer));
            break;
    }
    if (reg_adress < EEPROM_REGISER_COUNT)
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
  return ( getReg8( NODE_ID) );
}

void vIncrementSystemCounters()
{
    //uint32_t data = getReg32(HOUR_COUNTER_ADR);
    //data++;
   // setReg32(HOUR_COUNTER_ADR,data);
    if (++secondcounter>=360)
    {
        uint32_t data = getReg32(HOUR_COUNTER_ADR);
        data++;
        setReg32(HOUR_COUNTER_ADR,data);
        secondcounter = 0;
    }
   // odometr = odometr + getODValue( DATA_MODEL_REGISTER[ODOMETR_MAP])/3.6;*/
    return;
}

void vSaveData()
{
    //*((u32 *)(&DATA_MODEL_REGISTER[ODOMETR_ADR])) = odometr/100;
    eEEPROMWr(HOUR_COUNTER_ADR,&DATA_MODEL_REGISTER[HOUR_COUNTER_ADR],8,0);
}

u32 getOdometr()
{
    return (odometr/100);
}




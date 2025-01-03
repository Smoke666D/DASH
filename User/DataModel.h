/*
 * DataModel.h
 *
 *  Created on: Feb 23, 2024
 *      Author: i.dymov
 */

#ifndef USER_DATAMODEL_H_
#define USER_DATAMODEL_H_

#include "system_init.h"
#include "hw_lib_adc.h"

#define SW_V                 1
#define SW_V2                0
#define SW_V3                4

#define VALID_CODE            ((SW_V2<<4) | (SW_V3))
#define VALID_CODE_ADDRES     0

#define BITRATE_ADR            (VALID_CODE_ADDRES + 1)
#define RGB_BRIGTH_ADR         (BITRATE_ADR  +1)
#define WHITE_BRIGTH_ADR       (RGB_BRIGTH_ADR + 1)
#define NODE_ID                (WHITE_BRIGTH_ADR + 1)
#define BAR_MODE               (NODE_ID  + 1 )
#define HOUR_COUNTER_ADR       (BAR_MODE +1 )
#define ODOMETR_ADR            (HOUR_COUNTER_ADR + 4 )
#define ODOMETR_MAP            (ODOMETR_ADR  + 4 )
#define BAR_VALUE_HIGH         (ODOMETR_MAP  + 1 )
#define BAR_VALUE_LOW          (BAR_VALUE_HIGH  + 2 )
#define BAR_VALUE_RED_HIGH     (BAR_VALUE_LOW  + 2 )
#define BAR_VALUE_RED_LOW      (BAR_VALUE_RED_HIGH + 2 )
#define BAR_VALUE_GREEN_HIGH   (BAR_VALUE_RED_LOW  + 2 )
#define BAR_VALUE_GREEN_LOW    (BAR_VALUE_GREEN_HIGH  + 2 )
#define RGB1_VALUE_GREEN_HIGH  (BAR_VALUE_GREEN_LOW + 2)
#define RGB1_VALUE_GREEN_LOW   (RGB1_VALUE_GREEN_HIGH + 2)
#define RGB1_VALUE_RED_HIGH    (RGB1_VALUE_GREEN_LOW  + 2)
#define RGB1_VALUE_RED_LOW     (RGB1_VALUE_RED_HIGH  + 2)
#define RGB1_VALUE_BLUE_HIGH   (RGB1_VALUE_RED_LOW  + 2)
#define RGB1_VALUE_BLUE_LOW    (RGB1_VALUE_BLUE_HIGH   + 2)
#define RGB2_VALUE_GREEN_HIGH  (RGB1_VALUE_BLUE_LOW + 2)
#define RGB2_VALUE_GREEN_LOW   (RGB2_VALUE_GREEN_HIGH + 2)
#define RGB2_VALUE_RED_HIGH    (RGB2_VALUE_GREEN_LOW  + 2)
#define RGB2_VALUE_RED_LOW     (RGB2_VALUE_RED_HIGH  + 2)
#define RGB2_VALUE_BLUE_HIGH   (RGB2_VALUE_RED_LOW  + 2)
#define RGB2_VALUE_BLUE_LOW    (RGB2_VALUE_BLUE_HIGH   + 2)
#define RGB3_VALUE_GREEN_HIGH  (RGB2_VALUE_BLUE_LOW + 2)
#define RGB3_VALUE_GREEN_LOW   (RGB3_VALUE_GREEN_HIGH + 2)
#define RGB3_VALUE_RED_HIGH    (RGB3_VALUE_GREEN_LOW  + 2)
#define RGB3_VALUE_RED_LOW     (RGB3_VALUE_RED_HIGH  + 2)
#define RGB3_VALUE_BLUE_HIGH   (RGB3_VALUE_RED_LOW  + 2)
#define RGB3_VALUE_BLUE_LOW    (RGB3_VALUE_BLUE_HIGH   + 2)
#define RGB4_VALUE_GREEN_HIGH  (RGB3_VALUE_BLUE_LOW + 2)
#define RGB4_VALUE_GREEN_LOW   (RGB4_VALUE_GREEN_HIGH + 2)
#define RGB4_VALUE_RED_HIGH    (RGB4_VALUE_GREEN_LOW  + 2)
#define RGB4_VALUE_RED_LOW     (RGB4_VALUE_RED_HIGH  + 2)
#define RGB4_VALUE_BLUE_HIGH   (RGB4_VALUE_RED_LOW  + 2)
#define RGB4_VALUE_BLUE_LOW    (RGB4_VALUE_BLUE_HIGH   + 2)
#define RGB5_VALUE_GREEN_HIGH  (RGB4_VALUE_BLUE_LOW + 2)
#define RGB5_VALUE_GREEN_LOW   (RGB5_VALUE_GREEN_HIGH + 2)
#define RGB5_VALUE_RED_HIGH    (RGB5_VALUE_GREEN_LOW  + 2)
#define RGB5_VALUE_RED_LOW     (RGB5_VALUE_RED_HIGH  + 2)
#define RGB5_VALUE_BLUE_HIGH   (RGB5_VALUE_RED_LOW  + 2)
#define RGB5_VALUE_BLUE_LOW    (RGB5_VALUE_BLUE_HIGH   + 2)
#define RGB6_VALUE_GREEN_HIGH  (RGB5_VALUE_BLUE_LOW + 2)
#define RGB6_VALUE_GREEN_LOW   (RGB6_VALUE_GREEN_HIGH + 2)
#define RGB6_VALUE_RED_HIGH    (RGB6_VALUE_GREEN_LOW  + 2)
#define RGB6_VALUE_RED_LOW     (RGB6_VALUE_RED_HIGH  + 2)
#define RGB6_VALUE_BLUE_HIGH   (RGB6_VALUE_RED_LOW  + 2)
#define RGB6_VALUE_BLUE_LOW    (RGB6_VALUE_BLUE_HIGH   + 2)
#define RGB7_VALUE_GREEN_HIGH  (RGB6_VALUE_BLUE_LOW + 2)
#define RGB7_VALUE_GREEN_LOW   (RGB7_VALUE_GREEN_HIGH + 2)
#define RGB7_VALUE_RED_HIGH    (RGB7_VALUE_GREEN_LOW  + 2)
#define RGB7_VALUE_RED_LOW     (RGB7_VALUE_RED_HIGH  + 2)
#define RGB7_VALUE_BLUE_HIGH   (RGB7_VALUE_RED_LOW  + 2)
#define RGB7_VALUE_BLUE_LOW    (RGB7_VALUE_BLUE_HIGH   + 2)
#define RGB8_VALUE_GREEN_HIGH  (RGB7_VALUE_BLUE_LOW + 2)
#define RGB8_VALUE_GREEN_LOW   (RGB8_VALUE_GREEN_HIGH + 2)
#define RGB8_VALUE_RED_HIGH    (RGB8_VALUE_GREEN_LOW  + 2)
#define RGB8_VALUE_RED_LOW     (RGB8_VALUE_RED_HIGH  + 2)
#define RGB8_VALUE_BLUE_HIGH   (RGB8_VALUE_RED_LOW  + 2)
#define RGB8_VALUE_BLUE_LOW    (RGB8_VALUE_BLUE_HIGH   + 2)
#define RGB9_VALUE_GREEN_HIGH  (RGB8_VALUE_BLUE_LOW + 2)
#define RGB9_VALUE_GREEN_LOW   (RGB9_VALUE_GREEN_HIGH + 2)
#define RGB9_VALUE_RED_HIGH    (RGB9_VALUE_GREEN_LOW  + 2)
#define RGB9_VALUE_RED_LOW     (RGB9_VALUE_RED_HIGH  + 2)
#define RGB9_VALUE_BLUE_HIGH   (RGB9_VALUE_RED_LOW  + 2)
#define RGB9_VALUE_BLUE_LOW    (RGB9_VALUE_BLUE_HIGH   + 2)
#define RGB10_VALUE_GREEN_HIGH  (RGB9_VALUE_BLUE_LOW + 2)
#define RGB10_VALUE_GREEN_LOW   (RGB10_VALUE_GREEN_HIGH + 2)
#define RGB10_VALUE_RED_HIGH    (RGB10_VALUE_GREEN_LOW  + 2)
#define RGB10_VALUE_RED_LOW     (RGB10_VALUE_RED_HIGH  + 2)
#define RGB10_VALUE_BLUE_HIGH   (RGB10_VALUE_RED_LOW  + 2)
#define RGB10_VALUE_BLUE_LOW    (RGB10_VALUE_BLUE_HIGH   + 2)
#define RGB11_VALUE_GREEN_HIGH  ( RGB10_VALUE_BLUE_LOW + 2)
#define RGB11_VALUE_GREEN_LOW   (RGB11_VALUE_GREEN_HIGH + 2)
#define RGB11_VALUE_RED_HIGH    (RGB11_VALUE_GREEN_LOW  + 2)
#define RGB11_VALUE_RED_LOW     (RGB11_VALUE_RED_HIGH  + 2)
#define RGB11_VALUE_BLUE_HIGH   (RGB11_VALUE_RED_LOW  + 2)
#define RGB11_VALUE_BLUE_LOW    (RGB11_VALUE_BLUE_HIGH   + 2)
#define RGB12_VALUE_GREEN_HIGH  (RGB11_VALUE_BLUE_LOW + 2)
#define RGB12_VALUE_GREEN_LOW   (RGB12_VALUE_GREEN_HIGH + 2)
#define RGB12_VALUE_RED_HIGH    (RGB12_VALUE_GREEN_LOW  + 2)
#define RGB12_VALUE_RED_LOW     (RGB12_VALUE_RED_HIGH  + 2)
#define RGB12_VALUE_BLUE_HIGH   (RGB12_VALUE_RED_LOW  + 2)
#define RGB12_VALUE_BLUE_LOW    (RGB12_VALUE_BLUE_HIGH   + 2)
#define RGB13_VALUE_GREEN_HIGH  (RGB12_VALUE_BLUE_LOW + 2)
#define RGB13_VALUE_GREEN_LOW   (RGB13_VALUE_GREEN_HIGH + 2)
#define RGB13_VALUE_RED_HIGH    (RGB13_VALUE_GREEN_LOW  + 2)
#define RGB13_VALUE_RED_LOW     (RGB13_VALUE_RED_HIGH  + 2)
#define RGB13_VALUE_BLUE_HIGH   (RGB13_VALUE_RED_LOW  + 2)
#define RGB13_VALUE_BLUE_LOW    (RGB13_VALUE_BLUE_HIGH   + 2)
#define RGB14_VALUE_GREEN_HIGH  (RGB13_VALUE_BLUE_LOW + 2)
#define RGB14_VALUE_GREEN_LOW   (RGB14_VALUE_GREEN_HIGH + 2)
#define RGB14_VALUE_RED_HIGH    (RGB14_VALUE_GREEN_LOW  + 2)
#define RGB14_VALUE_RED_LOW     (RGB14_VALUE_RED_HIGH  + 2)
#define RGB14_VALUE_BLUE_HIGH   (RGB14_VALUE_RED_LOW  + 2)
#define RGB14_VALUE_BLUE_LOW    (RGB14_VALUE_BLUE_HIGH   + 2)
#define RGBMAP1                 (RGB14_VALUE_BLUE_LOW + 2)
#define RGBMAP2                 (RGBMAP1  + 1)
#define RGBMAP3                 (RGBMAP2  + 1)
#define RGBMAP4                 (RGBMAP3  + 1)
#define RGBMAP5                 (RGBMAP4  + 1)
#define RGBMAP6                 (RGBMAP5  + 1)
#define RGBMAP7                 (RGBMAP6  + 1)
#define RGBMAP8                 (RGBMAP7  + 1)
#define RGBMAP9                 (RGBMAP8  + 1)
#define RGBMAP10                (RGBMAP9  + 1)
#define RGBMAP11                (RGBMAP10 + 1)
#define RGBMAP12                (RGBMAP11  + 1)
#define RGBMAP13                (RGBMAP12  + 1)
#define RGBMAP14                (RGBMAP13  + 1)
#define BARMAP                  (RGBMAP14  + 1)
#define BIG_SEGVAL1             (BARMAP   + 1)
#define BIG_SEGVAL2             (BIG_SEGVAL1   + 2)
#define BIG_SEGVAL3             (BIG_SEGVAL2   + 2)
#define BIG_SEGVAL4             (BIG_SEGVAL3   + 2)
#define BIG_SEGVAL5             (BIG_SEGVAL4   + 2)
#define BIG_SEGVAL6             (BIG_SEGVAL5   + 2)
#define BIG_SEGVAL7             (BIG_SEGVAL6   + 2)
#define BIG_SEGVAL8             (BIG_SEGVAL7   + 2)
#define BIG_SEGVAL9             (BIG_SEGVAL8   + 2)
#define AIN1_CAL_POINT_COUNT    (BIG_SEGVAL9   + 2)
#define AIN1_OFFSET             (AIN1_CAL_POINT_COUNT  + 1 )
#define AIN2_CAL_POINT_COUNT    (AIN1_OFFSET  + 2 )
#define AIN2_OFFSET             (AIN2_CAL_POINT_COUNT  + 1 )
#define AIN3_CAL_POINT_COUNT    (AIN2_OFFSET  + 2 )
#define AIN3_OFFSET             (AIN3_CAL_POINT_COUNT  + 1 )
#define AIN1_CAL_POINT_BEGIN    (AIN3_OFFSET  + 2 )
#define AIN2_CAL_POINT_BEGIN    (AIN1_CAL_POINT_BEGIN  +  MAX_CAL_POINT * 4 )
#define AIN3_CAL_POINT_BEGIN    (AIN2_CAL_POINT_BEGIN  +  MAX_CAL_POINT * 4 )
#define RPM1_COOF               (AIN3_CAL_POINT_BEGIN  +  MAX_CAL_POINT * 4 )
#define RPM2_COOF             ( RPM1_COOF+2 )
#define MENU1_MAP             ( RPM2_COOF+2 )
#define MENU2_MAP             ( MENU1_MAP + 4 )
#define MENU3_MAP             ( MENU2_MAP + 4 )
#define MENU4_MAP             ( MENU3_MAP + 4 )
#define MENU5_MAP             ( MENU4_MAP + 4 )
#define MENU6_MAP             ( MENU5_MAP + 4 )
#define MENU7_MAP             ( MENU6_MAP + 4 )
#define MENU8_MAP             ( MENU7_MAP + 4 )
#define MENU9_MAP             ( MENU8_MAP + 4 )
#define MENU10_MAP            ( MENU9_MAP + 4 )
#define MENU_DEF_POS          ( MENU10_MAP + 4 )
#define MENU_HOME_BACK_TIME   ( MENU_DEF_POS +1 )
#define DIN_ACTIVE_STATE      ( MENU_HOME_BACK_TIME +1)
#define VERSION_REG           ( DIN_ACTIVE_STATE  +1)
#define KEY_CONTROL_REG       ( VERSION_REG   + 4)
#define CH1_TIME_AVER         ( KEY_CONTROL_REG  +1 )
#define CH2_TIME_AVER         ( CH1_TIME_AVER + 2 )
#define CH3_TIME_AVER         ( CH2_TIME_AVER + 2 )
#define EEPROM_REGISER_COUNT  ( CH3_TIME_AVER + 2 )


#define BIG_SEG                 ( EEPROM_REGISER_COUNT)
#define V1                      ( BIG_SEG + 2 )
#define V2                      ( V1 + 1 )
#define V3                      ( V2 + 1 )
#define V4                      ( V3 + 1 )
#define V5                      ( V4 + 1 )
#define V6                      ( V5 + 1 )
#define V7                      ( V6 + 1 )
#define V8                      ( V7 + 1 )
#define V9                      ( V8 + 1 )
#define V10                     ( V9 + 1 )
#define V11                     ( V10 + 1 )
#define V12                     ( V11 + 1 )
#define V13                     ( V12 + 1 )
#define V14                     ( V13 + 1 )
#define V15                     ( V14 + 1 )
#define V16                     ( V15 + 2 )
#define V17                     ( V16 + 2 )
#define KEY_CODE                 (V17 +  2 )

#define AIN_OFFSET                400
#define RMP_OFFSET                1000

#define TOTAL_REGISTER_COUNT  (KEY_CODE +1 )


typedef struct
{
    u8 len;
    u16 addr;
} EEPROM_REG_Q_t;


QueueHandle_t * xDataRegQueue( void );
void DataModel_Init();
void vDataModelRegDelayWrite();
void setReg32( u16 reg_adress, u32 data);
void setReg16( u16 reg_adress, u16 data);
void setReg8( u16 reg_adress, u8 data);
u32 getReg32(u16 reg_adress );
u16 getReg16(u16 reg_adress );
u8 getReg8( u16 reg_adress);
void WriteReg( u16 reg_adress, void * data, u8 len);
uint16_t vGetBitrate();
void vIncrementSystemCounters();
void WriteRegAfterDelay( u16 reg_adress, void * data, u8 len);
uint8_t vGetNodeId( void );
void vSaveData();
u32 getOdometr();
void SaveReg16(u16 reg_adress, u8 notyfy_index );
#endif /* USER_DATAMODEL_H_ */

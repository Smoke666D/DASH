/*
 * dash_draw.h
 *
 *  Created on: Feb 27, 2024
 *      Author: i.dymov
 */

#ifndef USER_DASH_DRAW_H_
#define USER_DASH_DRAW_H_


#include "system_init.h"
#include "filters.h"
#include "types.h"

#define RGB_DIOD_COUNT 14
#define MAX_MENU_COUNT 9
typedef enum
{
  MENU_ORDINARY = 0,
  LAST_ITEM     = 1,

} MENU_CHECK_CHANNEL_t;

typedef enum
{
    vCHANNEL1       = 1,
    vCHANNEL2       = 2,
    vCHANNEL3       = 3,
    vCHANNEL4       = 4,
    vCHANNEL5       = 5,
    vCHANNEL6       = 6,
    vCHANNEL7       = 7,
    vCHANNEL8       = 8,
    vCHANNEL9       = 9,
    vCHANNEL10      = 10,
    vCHANNEL11      = 11,
    vCHANNEL12      = 12,
    vCHANNEL13      = 13,
    vCHANNEL14      = 14,
    vCHANNEL15      = 15,
    vCHANNEL16      = 16,
    vCHANNEL17      = 17,
    chAIN1          = 18,
    chAIN2          = 19,
    chAIN3          = 20,
    chAKB           = 21,
    chRPM1          = 22,
    chRPM2          = 23,
    chDIN1          = 24,
    chKEY           = 25,
    chODOMETR       = 26,
    chHOUR          = 27,
    chErrorRegister = 28,
} VIRTUAL_CHANNEL_t;

typedef struct
{
  u32 menu_draw[ MAX_MENU_COUNT];
  u8 current_menu;
  u8 home_menu;
  u8 home_menu_back_time_s;
  u32 current_timer_ms;
  u8 error_reg_index;
  u8 show_error_flag;
  u32 buffer_error_register;
  u8 max_menu_index;
  u8 cur_dispaly_error;
} Menu_Object_t;


typedef enum
{
  SYSTEM_IDLE,
  SYSTEM_EDIT,
  SYSTEM_ENTER,
  SYSTEM_EXIT,
} KeyDelayState_t;

typedef enum
{
  WORK_MENU_STATE,
  SYS_MENU_STATE,
  RPM1_UP_MENU_STATE,
  RPM2_UP_MENU_STATE,
  RPM1_DOWN_MENU_STATE,
  RPM2_DOWN_MENU_STATE,

} MenuState_t;

TaskHandle_t * xProcessTaskHandle ();
void RedrawNotifyTaskToInit();
u8 GetCurMenuHome();
void vSetErrorReg( u32 data);
int32_t getODValue( VIRTUAL_CHANNEL_t virtualchannel, uint8_t offset_enable);
void IncMenuIndex();
u8 SetCurrentMenu( u8 menu_item);
u8 SetDefault( u8 menu_item);
void vRedrawTask( void * argument );

#endif /* USER_DASH_DRAW_H_ */

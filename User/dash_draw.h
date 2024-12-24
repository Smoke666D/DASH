/*
 * dash_draw.h
 *
 *  Created on: Feb 27, 2024
 *      Author: i.dymov
 */

#ifndef USER_DASH_DRAW_H_
#define USER_DASH_DRAW_H_


#include "system_init.h"
#include "types.h"

#define KEY_ON_STATE       ( HAL_BIT_RESET  )
#define KEY_OFF_STATE      ( HAL_BIT_SET )


#define RGB_DIOD_COUNT 14
#define MAX_MENU_COUNT 10
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
    chVERSION       = 29,
    chTRIP          = 30
} VIRTUAL_CHANNEL_t;


typedef enum
{
    MENU_NOT_BLINK,
    MENU_BLINK,
} MENU_BLINK_t;

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
  MENU_BLINK_t blink;
  u8 blink_counter;

} Menu_Object_t;

typedef enum
{
    KEY_NOT_CHANGED = 0,
    KEY_CHANGE_STATE = 1
} KEY_PRESS_t;

typedef enum
{
   KEY_STATUS_IDLE = 0,
   KEY_STATUS_PRESS = 1,
   KEY_STATUS_HOLD  = 2,
} KEY_STATUS_t;


#define SERVICE_MODE_TIME_OUT 600
#define SERVICE_MODE_EXIT     400
#define SERVICE_MODE_ENTER    200

typedef enum
{
  SYSTEM_IDLE =  0,
  SYSTEM_ENTER = 1,
  SYSTEM_EXIT  = 2,
  SYSTEM_EDIT =  3,
} KeyDelayState_t;

typedef struct
{
    KEY_PRESS_t key_press_state;
    KEY_STATUS_t key_status;
    u16          key_counter;
    KeyDelayState_t SystemDelayState;
} KeyState_t;

#define RMP1_UP_MASK  (RPM1_UP_MENU_STATE & RPM2_UP_MENU_STATE)

typedef enum
{
  WORK_MENU_STATE = 0,
  SYS_MENU_STATE  = 1,
  ERROR_MENU_STATE = 2,
  RPM1_UP_MENU_STATE = 3,
  RPM1_DOWN_MENU_STATE= 4,
  RPM2_UP_MENU_STATE  = 5,
  RPM2_DOWN_MENU_STATE = 6,
  AIN1_VIEW_STATE  = 7,
  AIN2_VIEW_STATE = 8,
  AIN3_VIEW_STATE = 9,
  RPMCOOF1      =10,
  RPMCOOF2     = 11,
} MenuState_t;




void TestProcedure();
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

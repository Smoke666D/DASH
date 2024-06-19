/*
 * dash_draw.c
 *
 *  Created on: Feb 27, 2024
 *      Author: i.dymov
 */

#include "dash_draw.h"
#include "CO_ODinterface.h"
#include "OD.h"
#include "hw_lib_din.h"
#include "hw_lib_keyboard.h"
#include "inputs.h"
#include "HW_API.h"

static Menu_Object_t menu;
static u32 ErrorRegister = 0;
static u8 keystate = 0;
static median_filter_data_t      AIN_MIDIAN_FILTER_STRUC[1];

static TaskHandle_t  pProcessTaskHandle ;


TaskHandle_t * xProcessTaskHandle ()
{
    return  &pProcessTaskHandle ;
}

void vSetErrorReg( u32 data)
{

    ErrorRegister = data;
}
int32_t getODValue( VIRTUAL_CHANNEL_t virtualchannel, uint8_t offset_enable)
{
  u16 data16 = 0;
  int32_t out_data;
  switch (virtualchannel)
  {
    case vCHANNEL1:
    case vCHANNEL2:
    case vCHANNEL3:
    case vCHANNEL4:
    case vCHANNEL5:
    case vCHANNEL6:
    case vCHANNEL7:
    case vCHANNEL8:
    case vCHANNEL9:
    case vCHANNEL10:
    case vCHANNEL11:
    case vCHANNEL12:
    case vCHANNEL13:
    case vCHANNEL14:
        return ( (int32_t) getReg8(V1 + virtualchannel -1 ) );
    case vCHANNEL15:
    case vCHANNEL16:
    case vCHANNEL17:
        return ( (u32) getReg16(V1 + virtualchannel -1 ) );
    case chAIN1 :
    case chAIN2 :
    case chAIN3 :
        out_data= fGetAinCalData( 0 , GetAIN(virtualchannel -chAIN1 ))*10;
        if (offset_enable) out_data= out_data + getReg16(AIN1_OFFSET);
        return  (out_data);
    case chAKB  :
        return ( (int32_t)( GetAIN(AIN4 ) * 10 ));
    case chRPM1  :
        data16 = GetRPM(INPUT_1);
        float coof1 = (float)getReg16(RPM1_COOF)/RMP_OFFSET;
        return ( (u32)((data16 *coof1)*10.0) );
    case chRPM2  :
        data16 = GetRPM(INPUT_2);
        float coof2 = (float)getReg16(RPM2_COOF)/RMP_OFFSET;
        return ( (u32)((data16 *coof2)*10.0) );
      case chKEY  :
          return ((u32) keystate);
      case chDIN1   :
          return ( (u32) uGetDIN(INPUT_3) );
      case chODOMETR:
          return ( getOdometr() );
      case  chHOUR:
          return ( getReg32(HOUR_COUNTER_ADR) );
      case chErrorRegister:
          return ( ErrorRegister );
      case chVERSION:
          out_data = getReg32(VERSION_REG);
          return (out_data & 0xFF) + ((out_data>>8) & 0xFF)*100+ ((out_data>>16) & 0xFF)*10000;
      default:
          return (0);
  }
}


static u8 getErrorCode()
{
    while (1)
    {
        if ((menu.buffer_error_register & (1<<menu.cur_dispaly_error)) !=0) break;
        if (++menu.cur_dispaly_error > 32)
        {
            menu.cur_dispaly_error = 0;
        }
        if (menu.buffer_error_register == 0) break;
    }
    return (menu.cur_dispaly_error);
}


/*
 * API для работы с меню
 */
void IncMenuIndex( )
{
   if ((menu.menu_draw[menu.current_menu] == chErrorRegister) &&  (menu.cur_dispaly_error)) //Если текущие отобржаемый пункт меню - ошибки
   {
      if ( menu.buffer_error_register !=0 )                 //Если ошибки все таки есть.
      {
          if (menu.show_error_flag )
          {
              menu.cur_dispaly_error =0;
              menu.show_error_flag = 0;

          }
           while (1)
           {
              if (++menu.cur_dispaly_error > 32)
              {
                  menu.cur_dispaly_error =0;
                   menu.show_error_flag = 0;
                  break;
              }
              else
              {
                  if ((menu.buffer_error_register & (1<<menu.cur_dispaly_error)) !=0) return;

              }
           }
      }
   }
   if (++menu.current_menu >=  menu.max_menu_index )  menu.current_menu = 0;

   menu.current_timer_ms = 0;
}

void GoToHome()
{
    menu.current_timer_ms = 0;
    menu.current_menu = menu.home_menu;
}

void SetCurMenuHome()
{
    menu.home_menu = menu.current_menu;
    WriteReg( MENU_DEF_POS  ,&menu.home_menu,1);

}

u8 GetCurMenuHome()
{
   return ( menu.current_menu);
}

u8 SetCurrentMenu( u8 menu_item)
{
   if (menu_item <= MAX_MENU_COUNT )
   {
       menu.current_menu =  menu_item;
       return 0;
   }
   return 1;
}

u8 SetDefault( u8 menu_item)
{
   if (menu_item <= MAX_MENU_COUNT )
   {
       menu.home_menu  =  menu_item;
       WriteReg( MENU_DEF_POS  ,&menu.home_menu,1);
       return 0;
   }
   return 1;
}

void SetBackHomeTime( u8 time)
{
   menu.home_menu_back_time_s = time;
}

void MenuBackHomeCheck( u8 time_increment)
{
    if (( menu.current_menu!= menu.home_menu ) && (menu.show_error_flag == 0 ))
    {
           menu.current_timer_ms += time_increment;
           if ((menu.current_timer_ms)>= (menu.home_menu_back_time_s*1000))
           {
               GoToHome();
           }
    }
}


MENU_CHECK_CHANNEL_t  CheckMenuChannel( u8 menu_item, u8 index)
{
    switch (menu_item)
    {
        case 0:
            menu.max_menu_index  =  index;
            return (LAST_ITEM );
        case chErrorRegister:
            menu.error_reg_index  = index;
            break;
        default:
            if ( index >=(MAX_MENU_COUNT-1))
            {
                menu.max_menu_index  =  index;
                return (LAST_ITEM );
            }
            break;
    }
    return ( MENU_ORDINARY);
}

void vDashDrawInit()
{
    vInitMedianFilter(&AIN_MIDIAN_FILTER_STRUC[0]);
    menu.home_menu = getReg8(MENU_DEF_POS);
    menu.home_menu_back_time_s = getReg8(MENU_HOME_BACK_TIME );
    menu.current_menu = menu.home_menu;
    menu.max_menu_index  = 0;
    //Проверяем скокльо в меню индекосв
    for (u8 i=0;i< MAX_MENU_COUNT;i++)
    {
        u32 menu_mask =  getReg32( MENU1_MAP + i*4);
        menu.menu_draw[i] = menu_mask;
        if ( CheckMenuChannel( (menu_mask & 0xFF ),i) == LAST_ITEM)
        {
            break;
        }
    }
    menu.buffer_error_register = 0;
    menu.cur_dispaly_error = 0;
    return;
}

void vAcceptError()
{
   if (menu.show_error_flag)
   {
        menu.show_error_flag = 0;
        SetCurMenuHome();
   }
}

void SetErrorRegiter( u32 error)
{
  if ((error != menu.buffer_error_register ) && ( menu.error_reg_index!=0))
  {
      u32 temp_mask               = error & (~menu.buffer_error_register);
      menu.cur_dispaly_error      = 0;
      menu.buffer_error_register  = error;
      for ( u8 i=0;i<32;i++)
      {
        if ((1<<menu.cur_dispaly_error) & temp_mask) break;
        menu.cur_dispaly_error++;
      }
      if (temp_mask )
          menu.show_error_flag = 1;
      else
          menu.show_error_flag = 0;

  }
}

u32 uGetCurrMenu()
{
    if ( menu.show_error_flag == 1)  menu.current_menu = menu.error_reg_index;
    return  ( menu.menu_draw[menu.current_menu] );
}




/*
 * Конец API для работыс меню
 */

void vRGBOff( u8 ch)
{
    SetRGB( ch, GREEN_COLOR, STATE_OFF);
    SetRGB( ch, BLUE_COLOR, STATE_OFF);
    SetRGB( ch, RED_COLOR, STATE_OFF);
}


/*
 *
 */
void vGetEdgeData(u16 addr,  u16 *high, u16 * low)
{
    *high = getReg16(addr );
    *low  = getReg16(addr + 2 );
}

void vRGBMode( u8 i,  u8 index )
{
    if (index ==0 )
    {
       vRGBOff( i);
       return;
    }
    u16 bd = getODValue(index,1);
    u16 low_edge, high_edge;
    LED_STATE_t state;
    u16 offset = RGB1_VALUE_GREEN_HIGH + i*6*2;
    vGetEdgeData( offset, &high_edge,&low_edge);
    if ((low_edge ==0) && (high_edge ==0)) state = STATE_OFF;
    else
    if (low_edge <= high_edge)   //Обычный режим, проверяем на попадание в окно.
    {
         state = ((bd >= low_edge) && (bd <= high_edge)) ? STATE_ON : STATE_OFF;
    }
    else  // инвесный режим, попадаем на непопадание в окно
    {
         state = ((bd >= low_edge) || (bd <= high_edge)) ? STATE_ON : STATE_OFF;
    }
    SetRGB( i, GREEN_COLOR, state);
    vGetEdgeData( offset +4 , &high_edge,&low_edge);
    if ((low_edge ==0) && (high_edge ==0)) state = STATE_OFF;
    else
    if (low_edge <= high_edge)   //Обычный режим, проверяем на попадание в окно.
    {
         state = ((bd >= low_edge) && (bd <= high_edge)) ? STATE_ON : STATE_OFF;
    }
    else  // инвесный режим, попадаем на непопадание в окно
    {
         state = ((bd >= low_edge) || (bd <= high_edge)) ? STATE_ON : STATE_OFF;
    }
    SetRGB( i, RED_COLOR, state);
    vGetEdgeData( offset +8, &high_edge,&low_edge);
    if ((low_edge ==0) && (high_edge ==0)) state = STATE_OFF;
    else
    if (low_edge <= high_edge)   //Обычный режим, проверяем на попадание в окно.
    {
        state = ((bd >= low_edge) && (bd <= high_edge)) ? STATE_ON : STATE_OFF;
    }
    else  // инвесный режим, попадаем на непопадание в окно
    {
        state = ((bd >= low_edge) || (bd <= high_edge)) ? STATE_ON : STATE_OFF;
    }
    SetRGB( i, BLUE_COLOR, state);
}


void vBarColorMode(u16   low_edge_g, u16  high_edge_g, u16  low_edge_r,u16  high_edge_r, u8 * startG, u8 * countG, u8 * startR, u8 * countR, float delta, u16 bd )
{
    u16 max_value,min_value;
    vGetEdgeData( BAR_VALUE_HIGH, &max_value ,&min_value);
    delta = (float)(max_value - min_value)/16.0;
    if (bd >= low_edge_r)
    {
        *startR =(u8)(( float)(low_edge_r - min_value)/delta);
        u16 val_delta = (bd<= high_edge_r) ? (bd - low_edge_r ) : (high_edge_r - low_edge_r );
        *countR = (u8)(( float)(val_delta )/delta );
    }
    if (bd >= low_edge_g)
    {
         *startG =(u8)(( float)(low_edge_g - min_value)/delta);
         u16 val_delta = (bd<= high_edge_g) ? (bd - low_edge_g ) : (high_edge_g - low_edge_g );
         *countG = (u8)(( float)(val_delta )/delta) ;
     }
}

/*
 *  Режим бара - оконный, одноцветный
 */
void vBarWindowMode(u16   low_edge_g, u16  high_edge_g, u16  low_edge_r,u16  high_edge_r, u8 * startG, u8 * countG, u8 * startR, u8 * countR, u8 bar_count, u16 bd )
{
    if (low_edge_g  >  high_edge_g)
    {
          if (  ((  bd < low_edge_g) && (bd > high_edge_r) )  || (( bd < high_edge_g ) && ( bd > low_edge_r  )) )
          {
               *countR = bar_count;
               *countG = bar_count;
          }
          else
          if ((  bd < high_edge_r) || ( bd > low_edge_r ) )   *countR = bar_count;
          else                                                *countG = bar_count;

    }
    else
    {
          if (  ((  bd > low_edge_r) && (bd < high_edge_g) )  || (( bd < high_edge_r ) && ( bd >low_edge_g  )) )
          {
                *countR = bar_count;
                *countG = bar_count;
          }
          else
          if ((  bd < high_edge_g) && ( bd > low_edge_g ) )  *countG = bar_count;
          else                                               *countR = bar_count;
     }
}



/*
 *  Режим бара - оконный, одноцветный
 */
void vBarMode(u16   low_edge_g, u16  high_edge_g, u16  low_edge_r,u16  high_edge_r,  u8 * countG,  u8 * countR, u8 bar_count, u16 bd )
{
    u16 max_value,min_value;
    vGetEdgeData( BAR_VALUE_HIGH, &max_value ,&min_value);
    if ( high_edge_g > high_edge_r)
    {
         if ( ( low_edge_g > high_edge_r) || ( ( high_edge_r >= low_edge_g ) && ( (  bd < low_edge_g)  || ( bd > high_edge_r ))) )
         {
              if (bd > high_edge_r)  *countG = bar_count; else  *countR = bar_count;
         }
         else
         {
              *countG = bar_count;
              *countR = bar_count;
         }
     }
     else
     {
         if ( ( low_edge_r > high_edge_g) || ( ( high_edge_g >= low_edge_r ) && ( (  bd < low_edge_r)  || ( bd > high_edge_g ))) )
         {
             if (bd > high_edge_g)  *countR = bar_count; else *countG = bar_count;
         }
         else
         {
             *countG = bar_count;
             *countR = bar_count;
        }
     }
}


static TaskHandle_t  pTaskToNotifykHandle;

void RedrawNotifyTaskToStop()
{
    xTaskNotify(pProcessTaskHandle, TASK_STOP_NOTIFY , eSetValueWithOverwrite);
}

void RedrawNotifyTaskToInit()
{
    pTaskToNotifykHandle = xTaskGetCurrentTaskHandle();
    xTaskNotify(pProcessTaskHandle, TASK_INIT_NOTIFY , eSetValueWithOverwrite);
}



//static TaskHandle_t  pKeybardTaskHandle ;
static uint8_t  STATUS = 0;


BitState_t fPortStateKey (uint8_t i)
{

     return HAL_GetBit( Din3_4_5_Port ,Din4_Pin );

}
#define SERVICE_MODE_TIME_OUT 600
#define SERVICE_MODE_EXIT     400
#define SERVICE_MODE_ENTER    200

static void SegClear()
{
    for (u8 i = 0;i<7;i++)
    {
        SetSegDirect(i,0x00);
    }
}
static void SegPrint(u8 s1,u8 s2,u8 s3,u8 s4,u8 s5,u8 s6,u8 s7)
{
    SetSegDirect(6,s1);
    SetSegDirect(5,s2);
    SetSegDirect(4,s3);
    SetSegDirect(3,s4);
    SetSegDirect(2,s5);
    SetSegDirect(1,s6);
    SetSegDirect(0,s7);
}

static void SeriveceMenuDraw( u8 * servece_menu_state)
{
    switch (*servece_menu_state )
    {
                     case 0:
                         SegPrint(0x6D,0x6E,0x6D,0,0,0,0);
                         break;
                     case 1:
                         SegPrint(0x50,0x73,0x06,0,0,0,0);
                         break;
                    case 2:
                         SegPrint(0x50,0x73,0x5B,0,0,0,0);
                         break;
                    case 3:
                         SegPrint(0x77,0x06,0x54,0x06,0,0,0);
                         break;
                    case 4:
                        SegPrint(0x77,0x06,0x54,0x5B,0,0,0);
                         break;
                    case 5:
                         SegPrint(0x77,0x06,0x54,0x4F,0,0,0);
                         break;
                    case 6:
                         SegPrint(0x6D,0x77,0x3E,0x79,0,0,0);
                         break;
                    case 7:
                         SetSEG( (u16)0x5000, getODValue(chVERSION,0));
                         break;
                    case 8:
                         SegPrint(0x79,0x76,0x06,0x78,0,0,0);
                         break;
                    default:
                         *servece_menu_state = 1;
                         break;
    }
}

static MenuState_t  MenuSatate = WORK_MENU_STATE;
static u8           ServieModeFSM = 0;
static u16          ServiceModeCounter = 0;
static u8           MenuViewBlink = 0;

static void SystemMenuDraw(u8 key_press_flag, KeyDelayState_t SystemDelayState)
{
    u32 buffer32;
    u8 data;
    if ( MenuSatate == WORK_MENU_STATE )
    {
        MenuViewBlink = 0;
        MenuBackHomeCheck( 10);
        if (key_press_flag )
        {
           switch (SystemDelayState)
           {
               case SYSTEM_EDIT:
                    MenuSatate = SYS_MENU_STATE;
                    break;
              case SYSTEM_EXIT:
              case SYSTEM_ENTER:
                    SetCurMenuHome();
                    break;
              default:
                    IncMenuIndex();
                    break;
          }
        }
       SetErrorRegiter(ErrorRegister);
       buffer32 = uGetCurrMenu();
       if ((buffer32 & 0xFF) == chErrorRegister )
       {
           if  (ErrorRegister!=0)
           {
               u8 code = (getErrorCode() + 1);
               SegPrint(0x79,0x50,0x50,0x00,0x00,DigitMask[code/10],DigitMask[code%10]);
               SetSegPoint( RESET);
               if (menu.show_error_flag)
               MenuViewBlink = 1;


           }
           else
           {
               IncMenuIndex();
           }
        }
        else
        {
            SetSEG( (u16)((buffer32 >>16) & 0xFFFF),  getODValue((u8)(buffer32 & 0xFF),0)  );

        }
    }
    else if (MenuSatate ==SYS_MENU_STATE )
    {
        MenuViewBlink = 1;
        if ( key_press_flag )
        {
              if ( SystemDelayState == SYSTEM_IDLE )ServieModeFSM++;
              else
              {
                 switch (ServieModeFSM)
                 {
                                  case 1:
                                     MenuSatate= RPM1_UP_MENU_STATE;
                                     break;
                                 case 2:
                                     MenuSatate= RPM2_UP_MENU_STATE;
                                     break;
                                 case 3:
                                     MenuSatate =AIN1_VIEW_STATE;
                                     break;
                                 case 4:
                                     MenuSatate =AIN2_VIEW_STATE;
                                     break;
                                 case 5:
                                     MenuSatate =AIN3_VIEW_STATE;
                                     break;
                                case 6:
                                     SaveReg16(RPM1_COOF, 2);
                                     SaveReg16(RPM2_COOF, 2);
                                     ServieModeFSM = 0;
                                     break;
                                case 8:
                                    GoToHome(); MenuSatate = WORK_MENU_STATE;
                                    break;
                              }
                       }
            }
            SeriveceMenuDraw(&ServieModeFSM );
    }
    else
    {
        if (key_press_flag)
        {
            if ((SystemDelayState == SYSTEM_EDIT) || (SystemDelayState == SYSTEM_EXIT))
            {
                MenuSatate = SYS_MENU_STATE;
            }
        }
        switch (MenuSatate)
          {

             case AIN1_VIEW_STATE:
                 SetSEG( (u16)0x0600, (int32_t) GetAIN(0 )*10);
                 break;
             case AIN2_VIEW_STATE:
                 SetSEG( (u16)0x05B00, (int32_t) GetAIN(1)*10);
                 break;
             case  AIN3_VIEW_STATE:
                 SetSEG( (u16)0x4F00, (int32_t) GetAIN(2)*10);
                 break;
             case RPM1_UP_MENU_STATE:
             case RPM2_UP_MENU_STATE:
                 if (MenuSatate == RPM1_UP_MENU_STATE)
                      SetSEG( (u16)0x2306,  getODValue(chRPM1,0) );
                 else
                      SetSEG( (u16)0x635B,  getODValue(chRPM2,0) );
                  if ((key_press_flag) && (SystemDelayState == SYSTEM_ENTER))
                  {
                      MenuSatate = (MenuSatate == RPM1_UP_MENU_STATE) ? RPM1_DOWN_MENU_STATE: RPM2_DOWN_MENU_STATE;
                  }
                  if ((key_press_flag) && (SystemDelayState == SYSTEM_IDLE))
                  {
                      data =  getReg16((MenuSatate == RPM1_UP_MENU_STATE) ? RPM1_COOF :  RPM2_COOF ) + 1;
                      setReg16((MenuSatate == RPM1_UP_MENU_STATE) ? RPM1_COOF :  RPM2_COOF, data);
                   }
                   break;
              case RPM1_DOWN_MENU_STATE:
              case RPM2_DOWN_MENU_STATE:
                  if (MenuSatate == RPM1_DOWN_MENU_STATE)
                      SetSEG( (u16)0x1C06,  getODValue(chRPM1,0) );
                  else
                      SetSEG( (u16)0x3F5B,  getODValue(chRPM2,0) );
                  if ((key_press_flag) && (SystemDelayState == SYSTEM_ENTER))
                  {
                      MenuSatate = (MenuSatate == RPM1_DOWN_MENU_STATE) ? RPM1_UP_MENU_STATE: RPM2_UP_MENU_STATE;
                  }
                  if ((key_press_flag) && (SystemDelayState == SYSTEM_IDLE))
                  {
                     data =  getReg16((MenuSatate == RPM1_DOWN_MENU_STATE) ? RPM1_COOF :  RPM2_COOF ) - 1;
                     setReg16((MenuSatate == RPM1_DOWN_MENU_STATE) ? RPM1_COOF :  RPM2_COOF,data);
                  }
                  break;
           }
    }
      if (MenuViewBlink)
      {
           if (++ServiceModeCounter>40) ServiceModeCounter = 0;
            if (ServiceModeCounter>21)  SegClear();
      }
}

static uint16_t COUNTER = 0;
/*
 *
 */
void vRedrawTask( void * argument )
{
    uint32_t ulNotifiedValue;
    TaskFSM_t  state = STATE_IDLE;
    u16 low_edge_g, high_edge_g, low_edge_r, high_edge_r,bd;
    u8 data;
    uint8_t key_press_flag = 0;
    KeyDelayState_t SystemDelayState = SYSTEM_IDLE;
    while(1)
    {
        switch(state)
        {
            case STATE_IDLE:
                xTaskNotifyWait(0,0xFF ,&ulNotifiedValue,portMAX_DELAY);
                if ((ulNotifiedValue & TASK_INIT_NOTIFY) !=0)
                {
                    vDashDrawInit();
                    state = STATE_INIT;
                }
                break;
            case STATE_INIT:
                state = STATE_RUN;
                xTaskNotifyGiveIndexed(pTaskToNotifykHandle,0);
                break;
            case STATE_RUN:
                 vTaskDelay(10);
                 if ( HAL_GetBit( Din3_4_5_Port ,Din4_Pin ) == KEY_OFF_STATE)
                 {
                     if  (STATUS!=0)
                     {
                         key_press_flag = 1;
                         STATUS = 0;
                         COUNTER = 0;
                     }
                 }
                 else
                 {
                     COUNTER++;
                     if (( STATUS == 0) && (COUNTER >= 5))
                     {
                         STATUS = 1;
                     }
                     if ( STATUS == 1 )
                     {
                         if ( COUNTER >= SERVICE_MODE_TIME_OUT )
                         {
                             SystemDelayState = SYSTEM_EDIT;
                             key_press_flag = 1;
                             STATUS = 2;
                         }
                         else if ( COUNTER >= SERVICE_MODE_EXIT  )
                         {
                             SystemDelayState = SYSTEM_EXIT;

                         }
                         else if ( COUNTER >= SERVICE_MODE_ENTER   )
                         {
                             SystemDelayState = SYSTEM_ENTER;
                         }
                     }
                 }
                 //Отрисовываем RGB пикторграммы
                 for ( u8 i = 0; i < RGB_DIOD_COUNT; i++ )
                 {
                     vRGBMode( i,  getReg8( RGBMAP1 + i));
                 }
                 //Вывод данных в бар
                 data =  getReg8(BARMAP);
                 u8 startR = 0;
                 u8 countR = 0;
                 u8 startG = 0;
                 u8 countG = 0;
                 if (data!=0)
                 {
                     bd = getODValue(data,1);
                     u16 max_value,min_value;
                     vGetEdgeData( BAR_VALUE_HIGH, &max_value ,&min_value);
                     vGetEdgeData( BAR_VALUE_RED_HIGH, &high_edge_r,&low_edge_r);
                     vGetEdgeData( BAR_VALUE_GREEN_HIGH, &high_edge_g,&low_edge_g);
                     float delta = (float)(max_value - min_value)/16.0;
                     if ( getReg8(BAR_MODE) == 0 )
                     {
                         if ((low_edge_g  >  high_edge_g) ||  (low_edge_r  >  high_edge_r ))
                         {
                             vBarColorMode(low_edge_g, high_edge_g,  low_edge_r, high_edge_r, &startG, &countG, &startR, &countR, delta,  bd );
                         }
                     }
                     else
                     {
                         u8 bar_count = (u8)(( float)(bd /delta));
                         if ((low_edge_g  >  high_edge_g) ||  (low_edge_r  >  high_edge_r ))
                         {
                             vBarWindowMode(low_edge_g, high_edge_g,  low_edge_r, high_edge_r, &startG, &countG, &startR, &countR, bar_count,  bd );
                         }
                         else
                         {
                             vBarMode(low_edge_g, high_edge_g,  low_edge_r, high_edge_r, &countG,  &countR, bar_count,  bd );
                         }
                     }
                 }
                 SetBarState( startG, countG, startR, countR );
                 //Конец вывода данных в бар

                 // Отображение меню
                 SystemMenuDraw(key_press_flag ,SystemDelayState);
                 if ( key_press_flag )
                 {
                      key_press_flag = 0;
                      SystemDelayState = SYSTEM_IDLE;
                 }

                  //Отображение большого сегменета
                  data = getReg16(BIG_SEG);
                  u16 seg_view = 0;
                  if (data!=0)
                  {
                      seg_view = getReg16(BIG_SEGVAL1 + (--data)*2 );
                  }
                  SetBigSeg(seg_view);
                  vLedProcess( );
                  break;
            }
        }
}

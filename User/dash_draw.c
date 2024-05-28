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

static Menu_Object_t menu;
static QueueHandle_t     pKeyboard        = NULL;
static u32 ErrorRegister = 0;
static u8 keystate = 0;


static TaskHandle_t  pProcessTaskHandle ;


TaskHandle_t * xProcessTaskHandle ()
{
    return  &pProcessTaskHandle ;
}

void vSetErrorReg( u32 data)
{
    ErrorRegister = data;
}
u32 getODValue( VIRTUAL_CHANNEL_t virtualchannel)
{
  u8 data8;
  u16 data16;
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
        return ((u32) getReg8(V1 + virtualchannel -1 ));
    case vCHANNEL15:
    case vCHANNEL16:
    case vCHANNEL17:
        return ((u32) getReg16(V1 + virtualchannel -1 ));
    case chAIN1 :
    case chAIN2 :
    case chAIN3 :
    case chAKB  :
        data16 = (u16)( GetAIN(virtualchannel -chAIN1 )/10);
        return ((u32) data16);
    case chRPM1  :
        xGetRPM(INPUT_1 ,&data16);
        float coof1 = (float)getReg16(RPM1_COOF)/1000;
        data16 = (u16)((data16 *coof1)*10.0);
        return ((u32) data16);
    case chRPM2  :
        xGetRPM(INPUT_2 ,&data16);
        float coof2 = (float)getReg16(RPM2_COOF)/1000;
        data16 = (u16)((data16 *coof2)*10.0);
        return ((u32) data16);
      case chKEY  :
          return ((u32) keystate);
      case chDIN1   :
          xGetDIN(INPUT_3,&data8);
          return ((u32) data8);
      case chODOMETR:
          return getOdometr();
          break;
      case  chHOUR:
          return  getReg32(HOUR_COUNTER_ADR);
          break;
      case chErrorRegister:
          return ( ErrorRegister);
          break;

  }
  return 0;
}

/*
 * API §Õ§Ý§ñ §â§Ñ§Ò§à§ä§í §ã §Þ§Ö§ß§ð
 */
void IncMenuIndex( )
{
   if (menu.menu_draw[menu.current_menu] == chErrorRegister)   //§¦§ã§Ý§Ú §ä§Ö§Ü§å§ë§Ú§Ö §à§ä§à§Ò§â§Ø§Ñ§Ö§Þ§í§Û §á§å§ß§Ü§ä §Þ§Ö§ß§ð - §à§ê§Ú§Ò§Ü§Ú
   {
      if ( menu.buffer_error_register !=0 )                 //§¦§ã§Ý§Ú §à§ê§Ú§Ò§Ü§Ú §Ó§ã§Ö §ä§Ñ§Ü§Ú §Ö§ã§ä§î.
      {
          while (1)
          {
              if (menu.buffer_error_register & (1>>menu.cur_dispaly_error) !=0)
              {
                  menu.cur_dispaly_error++;
                  return;  //§¦§Ý§ã§Ú §Ö§ã§ä§î §é§ä§à §à§ä§à§ð§â§Ñ§Ø§Ñ§ä§î
              }
              if (++menu.cur_dispaly_error > 32)  //§¦§ã§Ý§Ú §á§â§à§Ý§Ú§ã§ä§Ñ§Ý§Ú §Ó§ã§Ö §à§ê§Ú§Ò§Ü§Ú, §ä§à §ã§Ò§â§Ñ§ã§í§Ó§Ñ§Ö§Þ §ã§é§ä§Ö§é§Ú§Ü §Ú §á§Ö§â§Ö§ç§à§Õ§Ú§Þ §Ó §ã§Ý§Ö§Õ§å§ð§Ú§ë§Ö§Û §á§å§ß§Ü§ä §Þ§Ö§ß§ð
              {
                 menu.cur_dispaly_error =0;
                 break;
              }
          }
      }
   }
   if (++menu.current_menu >= MAX_MENU_COUNT )  menu.current_menu = 1;
}

void SetCurMenuHome()
{
    menu.home_menu = menu.current_menu;
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
           if ((menu.current_timer_ms/1000)>= (menu.home_menu_back_time_s))
           {
               menu.current_timer_ms = 0;
               menu.current_menu = menu.home_menu;
           }
    }
}


MENU_CHECK_CHANNEL_t  CheckMenuChannel( u8 menu_item)
{
    switch (menu_item)
    {
        case 0:
            menu.max_menu_index  =  menu_item;
            return (LAST_ITEM );
        case chErrorRegister:
            menu.error_reg_index = menu_item;
            break;
        default:
            break;
    }
    return ( MENU_ORDINARY);
}

void vDashDrawInit()
{
    menu.home_menu = getReg8(MENU_DEF_POS);
    menu.home_menu_back_time_s = getReg8(MENU_HOME_BACK_TIME );
    menu.current_menu = menu.home_menu;
  //  pKeyboard = pGetKeyboardQueue();
    //§±§â§à§Ó§Ö§â§ñ§Ö§Þ §ã§Ü§à§Ü§Ý§î§à §Ó §Þ§Ö§ß§ð §Ú§ß§Õ§Ö§Ü§à§ã§Ó
    for (u8 i=0;i< MAX_MENU_COUNT;i++)
    {
        u32 menu_mask =  getReg32( MENU1_MAP + i*4);
        menu.menu_draw[i] = menu_mask;
        if ( CheckMenuChannel( (menu_mask & 0xFF )) == LAST_ITEM)
                return;
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
  if ((error > menu.buffer_error_register ) && ( menu.error_reg_index!=0))
  {
      menu.buffer_error_register  = error;
      menu.show_error_flag = 1;
  }
}

u32 uGetCurrMenu()
{
    return ( menu.menu_draw[menu.current_menu]);
}



u8 getCurrErrorCode()
{
    return (menu.cur_dispaly_error);
}

/*
 * §¬§à§ß§Ö§è API §Õ§Ý§ñ §â§Ñ§Ò§à§ä§í§ã §Þ§Ö§ß§ð
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
    *low  = getReg16(addr+1 );
}
/*
 *
 */
void vRedrawTask( void * argument )
{
    LED_STATE_t state;
    u32 buffer32;
    u16 low_edge, high_edge;
    u8 brakecode_no_valid = 0;
   /* KeyEvent TempEvent;
    u8 data;
    u16 bd;
    vDashDrawInit();
    xEventGroupWaitBits(xGetSystemEventHeandler(),DATA_MODEL_READY, pdTRUE, pdFALSE, portMAX_DELAY );
    while(1)
    {
        vTaskDelay(10);
        if ( xQueueReceive( pKeyboard, &TempEvent,0 ) != errQUEUE_EMPTY )
        {
            switch (TempEvent.KeyCode)
            {
                case KEY_ON_REPEAT:
                    SetCurMenuHome();
                    brakecode_no_valid =1;
                    break;
                case BRAKECODE:
                    keystate = 0;
                    if (brakecode_no_valid)
                        brakecode_no_valid = 0;
                    else
                        IncMenuIndex();
                     break;
                case MAKECODE:
                    keystate  = 1;
                    vAcceptError();
                    break;
            }
        }
        //§±§â§à§Ó§Ö§â§ñ§Ö§Þ, §ß§Ö §ß§å§Ø§ß§à §Ý§Ú §Ó§Ö§â§ß§å§ä§î§ã§ñ §Ó §Õ§à§Þ§Ñ§ê§ß§Ö§Ö §Þ§Ö§ß§ð
        MenuBackHomeCheck(10);
        //§±§â§à§Ó§Ö§â§ñ§Ö§Þ §â§Ö§Ô§Ú§ã§ä§â §à§ê§Ú§Ò§à§Ü
        SetErrorRegiter(ErrorRegister);
        //§°§ä§â§Ú§ã§à§Ó§í§Ó§Ñ§Ö§Þ RGB §á§Ú§Ü§ä§à§â§Ô§â§Ñ§Þ§Þ§í
        for (u8 i = 0;i < RGB_DIOD_COUNT; i++)
        {
            data =  getReg8( RGBMAP1 + i);
            if (data==0 )
            {
                vRGBOff( i);
            }
            else
            {
                bd = getODValue(data);
                u16 offset = RGB1_VALUE_GREEN_HIGH + i*6;
                vGetEdgeData( offset, &high_edge,&low_edge);
                state = ((bd >= low_edge) && (bd <= high_edge)) ? STATE_ON : STATE_OFF;
                SetRGB( i, GREEN_COLOR, state);
                vGetEdgeData( offset +2 , &high_edge,&low_edge);
                state = ((bd >= low_edge) && (bd <= high_edge)) ? STATE_ON : STATE_OFF;
                SetRGB( i, RED_COLOR, state);
                vGetEdgeData( offset +4, &high_edge,&low_edge);
                state = ((bd >= low_edge) && (bd <= high_edge)) ? STATE_ON : STATE_OFF;
                SetRGB( i, BLUE_COLOR, state);
            }

        }
        //§£§í§Ó§à§Õ §Õ§Ñ§ß§ß§í§ç §Ó §Ò§Ñ§â
        data =  getReg8( BARMAP);
        u8 startR = 0;
        u8 countR = 0;
        u8 startG = 0;
        u8 countG = 0;
        if (data!=0)
        {
            bd = getODValue(data);
            u16 max_value,min_value;
            vGetEdgeData( BAR_VALUE_HIGH, &high_edge,&low_edge);
            float delta = (max_value - min_value)/16;
            vGetEdgeData( BAR_VALUE_RED_HIGH, &high_edge,&low_edge);
            if (bd >= low_edge)
            {
                startR =(u8)( float)(low_edge - min_value)/delta;
                u16 val_delta = (bd<= high_edge) ? (bd - low_edge ) : (high_edge - low_edge );
                countR = (u8)( float)(val_delta )/delta ;
            }
            vGetEdgeData( BAR_VALUE_GREEN_HIGH, &high_edge,&low_edge);
            if (bd >= low_edge)
            {
                 startG =(u8)( float)(low_edge - min_value)/delta;
                 u16 val_delta = (bd<= high_edge) ? (bd - low_edge ) : (high_edge - low_edge );
                 countG = (u8)( float)(val_delta )/delta ;
             }
        }
        SetBarState(  startR, countR, RED_COLOR);
        SetBarState(  startG, countG, GREEN_COLOR);
        //§¬§à§ß§Ö§è §Ó§í§Ó§à§Õ§Ñ §Õ§Ñ§ß§ß§í§ç §Ó §Ò§Ñ§â

        //§°§ä§à§Ò§â§Ñ§Ø§Ö§ß§Ú§Ö §Þ§Ö§ß§ð
        buffer32 = uGetCurrMenu();
       //
        if ((buffer32 & 0xFF) == chErrorRegister )
        {   u8 code = getCurrErrorCode();
            SetSegDirect(6,0x79);
            SetSegDirect(5,0x58);
            SetSegDirect(4,0x58);
            SetSegPoint( RESET);
            SetSegDirect(3,0x00);
            SetSegDirect(2,DigitMask[code/10]);
            SetSegDirect(1,DigitMask[code%10]);
            SetSegDirect(0,0x00);
        }
        else
        {
            SetSEG( (u16)((buffer32 >>8) & 0xFFFF),  getODValue((u8)(buffer32 & 0xFF))  );
        }
        //§°§ä§à§Ò§â§Ñ§Ø§Ö§ß§Ú§Ö §Ò§à§Ý§î§ê§à§Ô§à §ã§Ö§Ô§Þ§Ö§ß§Ö§ä§Ñ
        data = getReg16(BIG_SEG);
        u8 seg_view = 0;
        if (data!=0)
        {
            seg_view = getReg16(BIG_SEGVAL1 + data -1 );
        }
        SetBigSeg(seg_view);
    }*/
}

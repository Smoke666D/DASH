/*
 * led.c
 *
 *  Created on: Nov 12, 2021
 *      Author: igor.dymov
 */
#include "led.h"
#include <math.h>
#include "init.h"
#include "hal_dma.h"
#include "hal_timers.h"
#include "hal_spi.h"

/*                              0     1    2    3    4   5    6    7    8   9*/
const u8 DigitMask[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6E,0x7D,0x07,0x3F,0x6F};
static const u16 Brigth[MAX_BRIGTH] = { 0, 2, 3, 5,8,13,21,34,55,89,144,233,256,610,PWM_TIM_PERIOD};
static u8 LED_CHANELL_BRIGTH[2];
static uint16_t SPI1_DATA[SPI1_CHIP_COUNT];
static uint16_t SPI2_DATA[SPI2_CHIP_COUNT];



void SetBarState( u8 start, u8 count, LED_COLOR_t color)
{
    u8 offest = (color == GREEN_COLOR) ? 0 : 1;
    if (count > 0)
       SPI1_DATA[offest] = (0xFFFF << 16-count) >> (start - 1);
   else
       SPI1_DATA[offest] = 0x0000;
   return;
}


void vSetInitBrigth(BRIGTH_CHANNEL_t ch, u8 brigth)
{
    switch (ch)
    {
      case RGB_CHANNEL:
          LED_CHANELL_BRIGTH[0] = brigth <= MAX_BRIGTH ? brigth : MAX_BRIGTH;
        break;
      case WHITE_CHANNEL:
          LED_CHANELL_BRIGTH[1] = brigth <= MAX_BRIGTH ? brigth : MAX_BRIGTH;
          break;
      default:
          break;
    }
    return;
}

void SetRGB(  u8 number, LED_COLOR_t color, LED_STATE_t state)
{
   u8 offset = (color == BLUE_COLOR) ? 2 : ( (color==GREEN_COLOR) ? 3 : 4 );
   if ( state == STATE_ON )
   {
         SPI1_DATA[offset] |= 0x01 >> (number -1);
   }
   else
   {
         SPI1_DATA[offset] &= ~(0x01 >> (number -1));
   }
}
/*
 *
 */

void SetSegDirect( u8 number, u8 mask)
{
    switch (number)
    {
           case 0:
               SPI2_DATA[3] &= 0xFFFC;
               SPI2_DATA[3] |= (mask & 0x03);
               SPI2_DATA[2] &= 0x07FF;
               SPI2_DATA[2] |= ((u16)(mask & 0xF1)<<9);
               break;
           case 1:
               SPI2_DATA[2] &= 0xFC07;
               SPI2_DATA[2] |= (mask << 3 );
               break;
           case 2:
               break;
               SPI2_DATA[2] &= 0xFFF8;
               SPI2_DATA[2] |= (mask & 0x07);
               SPI2_DATA[1] &= 0x0FFF;
               SPI2_DATA[1] |= ((u16)(mask & 0xF1)<<12);
               break;
           case 3:
               SPI2_DATA[1] &= 0xF01F;
               SPI2_DATA[1] |= (mask << 5);
               break;
           case 4:
               SPI2_DATA[1] &= 0xFFE0;
               SPI2_DATA[1] |= (mask & 0x1F);
               SPI2_DATA[0] &= 0x03FF;
               SPI2_DATA[0] |= ((u16)(mask & 0x60)<<13);
               break;
           case 5:
               SPI2_DATA[2] &= 0xC07F;
               SPI2_DATA[2] |= ((u16)mask << 6 );
               break;
           case 6:
               SPI2_DATA[0] &= 0xFFFB;
               SPI2_DATA[0] |= ( mask & 0x0003 );
    }
}

void SetSegPoint( u8 on)
{
    if (on)
        SPI2_DATA[2] |= 0x0400;
    else
        SPI2_DATA[2] &= ~0x0400;
   return;
}

void SetSEG( u16 mask, u32 value)
{
  u32 val = value;
  u8 dc = 2,mask_count = 2;

  if (val%1000000)
  {
      dc = 7;
      mask_count = 0;
  }
  else
      if (val%100000)
      {
          mask_count = 1;
          dc = 6;
      }
       else
          if (val%10000)
              dc = 5;
          else
              if (val%1000)
                dc = 4;
              else
               if (val%100)
                   dc =3;

  for (u8 i = 0;i<dc;i++)
  {
     u8 digit = val % 10;
     SPI2_DATA[2] |= 0x0400; //Ставим точку
     SetSegDirect(i,DigitMask[digit]);
     val = val/10;
  }
  switch(mask_count)
  {
      case 1:
          break;
          SPI2_DATA[0] &= 0xFF80;
          SPI2_DATA[0] |= (mask & 0x007F);
          break;
      case 2:
          SPI2_DATA[0] &= 0xC000;
          SPI2_DATA[0] |=  ( (mask & 0x7F) | (mask & 0x7F00)>> 6);
          break;
      default:
          break;
  }

}



void SetBigSeg( u8 mask)
{
    SPI2_DATA[0] &= 0x0003;
    SPI2_DATA[0] = (mask <<2);
}

/*
 *
 */
void vSetBrigth( BRIGTH_CHANNEL_t ch, u8 brigth)
{
    HAL_TIMER_SetPWMPulse(TIMER2, (ch == RGB_CHANNEL) ? TIM_CHANNEL_3 :  TIM_CHANNEL_4 ,Brigth[brigth]);
    HAL_TIMER_EnablePWMCH(TIMER2,0);
    return;
}


void SPI1_DMA_Callback( void )
{
    HAL_DMA_Disable(DMA1_CH2);
    HAL_SPI_RXOveleyClear(SPI1 );
    while (HAL_SPI_GetBusy(SPI1) == HAL_SET);
    return;
}

void SPI2_DMA_Callback( void )
{
    HAL_DMA_Disable(DMA1_CH5);
    HAL_SPI_RXOveleyClear(SPI2 );
    while (HAL_SPI_GetBusy(SPI2) == HAL_SET);
    return;
}


/*
 *
 */
void vLedDriverStart(void)
{
	HAL_DMAInitIT(DMA1_Channel5,MTOP, SPI2_CHIP_COUNT  ,(u32)&SPI2->DATAR, (u32)SPI2_DATA,0,1,4,&SPI2_DMA_Callback);
	HAL_DMAInitIT(DMA1_Channel3,MTOP, SPI1_CHIP_COUNT  ,(u32)&SPI1->DATAR, (u32)SPI1_DATA,0,1,4,&SPI1_DMA_Callback);
	HAL_TiemrEneblae(TIMER3);
	TIM_Cmd( PWM_TIMER_1, ENABLE );
	vSetBrigth( RGB_CHANNEL,   LED_CHANELL_BRIGTH[0]);
	vSetBrigth( WHITE_CHANNEL, LED_CHANELL_BRIGTH[1]);
	return;
}


/*
 *  Функция вывода данных в SPI, вызывается по прерыванию таймра №4
 */
void vLedProcess( void )
{
   HAL_DMA_SetCounter(DMA1_CH5, SPI2_CHIP_COUNT);
   HAL_DMA_Enable(DMA1_CH5);
   HAL_DMA_SetCounter(DMA1_CH3, SPI1_CHIP_COUNT);
   HAL_DMA_Enable(DMA1_CH3);
   return;
}





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
#include "hal_gpio.h"

/*                        0     1    2    3    4   5    6    7    8   9*/
const u8 DigitMask[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//                                       0  1  2  3 4  5  6  7  8  9 10   11  12 13   14
static const u16 Brigth[MAX_BRIGTH] =  { 0, 2, 3, 5,8,13,21,34,55,89,144,233,350,610,PWM_TIM_PERIOD+1};
static const u16 BrigthR[MAX_BRIGTH] = { 0, 2, 3, 5,8,13,21,150,200,250,300,350,400,450,500};
static const u16 BrigthG[MAX_BRIGTH] = { 0, 2, 3, 5,8,13,21,50,80,100,150,200,250,300,350};
static const u16 BrigthB[MAX_BRIGTH] = { 0, 2, 3, 5,8,13,21,150,200,250,300,350,400,450,500};
static uint16_t SPI1_DATA[SPI1_CHIP_COUNT];
static uint16_t data[SPI1_CHIP_COUNT];
static uint16_t SPI2_DATA[SPI2_CHIP_COUNT];
static u16 counterRGB =0;


void SetBarState( u8 start_g, u8 count_g, u8 start_r, u8 count_r )
{
   u32 bar_led_buffer=0;
   u32 maskr= 0x01;
   u32 maskg =0x02;

   maskr = maskr<<(start_r*2);
   maskg = maskg<<(start_g*2);
   for (u8 i =0;i<count_g;i++)
   {
      bar_led_buffer|= maskg;
      maskg = maskg<<2;
   }
   SPI1_DATA[ 3] = (u16)(bar_led_buffer & 0xFFFF);
   SPI1_DATA[ 4] = (u16)(bar_led_buffer>>16 & 0xFFFF);
   bar_led_buffer = 0;
   for (u8 i =0;i< count_r;i++)
   {
        bar_led_buffer|= maskr;
        maskr = maskr<<2;
   }
   SPI1_DATA[ 3] |= (u16)(bar_led_buffer & 0xFFFF);
   SPI1_DATA[ 4] |= (u16)(bar_led_buffer>>16 & 0xFFFF);
   return;
}


/*
 * Функция вывода в RGB светодиод. Из-за неравномернго распределения
 * светодидов по драйверу, нуобходимо вычилить номер драйвера и биты
 * в драйвере, отвечающие за нужный цвет выбранного светодиода
 */
void SetRGB(  u8 number, LED_COLOR_t color, LED_STATE_t state)
{
   u8 offset;
   u8 step;
   switch (number)
   {
       case 0:
       case 1:
           offset   = 2;
           step     = number*3;
           break;
       case 2:
       case 3:
           offset  = 1;
           step =   (number-2)*3;
           break;
       case 4:
       case 5:
           offset   = 0;
           step     = (number-4)*3;
           break;
       case 6:
           offset   = 2;
           step     = 9;
           break;
       case 7:
           offset   = 2;
           step     = 6;
           break;
       case 8:
           offset   = 1;
           step     = 13;
           break;
       case 9:
           offset   = 1;
           step     = 10;
           break;
       case 12:
       case 10:
            offset   = (number - 10);
            step     = 12;
            break;
       case 11:
           offset   = 0;
           step     = 9;
           break;

       case 13:
           offset   = 0;
           step     = 6;
           break;
   }
   u16 mask = (color == BLUE_COLOR) ? 0x04 : ( (color==GREEN_COLOR) ? 0x02 : 0x01 );
   if ( state == STATE_ON )
   {
         SPI1_DATA[offset]   |= mask << step;
   }
   else
   {
         SPI1_DATA[offset] &= ~(mask << step );
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
               SPI2_DATA[0] &= 0xFFFC;
               SPI2_DATA[0] |= mask>>5;
               SPI2_DATA[1] &= 0x07FF;
               SPI2_DATA[1] |= (mask)<<11;
               break;
           case 1:
               SPI2_DATA[1] &= 0xFC03;
               SPI2_DATA[1] |= (mask << 3 );
               break;
           case 2:
               SPI2_DATA[1] &= 0xFFF8;
               SPI2_DATA[1] |= (mask >> 4);
               SPI2_DATA[2] &= 0x0FFF;
               SPI2_DATA[2] |= (mask <<12);
               break;
           case 3:
               SPI2_DATA[2] &= 0xF01F;
               SPI2_DATA[2] |= (mask << 5);
               break;
           case 4:
               SPI2_DATA[2] &= 0xFFE0;
               SPI2_DATA[2] |= ((mask>>2) & 0x1F);
               SPI2_DATA[3] &= 0x3FFF;
               SPI2_DATA[3] |= ((mask & 0x03) <<14);
               break;
           case 5:
               SPI2_DATA[3] &= 0xC07F;
               SPI2_DATA[3] |= ((u16)mask << 7 );
               break;
           case 6:
               SPI2_DATA[3] &= 0xFF80;
               SPI2_DATA[3] |=  mask ;
    }
}

void SetSegPoint( u8 on)
{
    if (on)
        SPI2_DATA[1] |= 0x0400;
    else
        SPI2_DATA[1] &= ~0x0400;
   return;
}

void SetSEG( u16 mask, u32 value)
{
  int32_t val = value;
  u8 min = 0;
  u8 dc = 2,mask_count = 2;
  if (val <0)
  {
      min = 1;
      val=val*-1;
  }
  if (val/1000000)
  {
      dc = 7;
      mask_count = 0;
  }
  else
      if (val/100000)
      {
          mask_count = 1;
          dc = 6;
      }
       else
          if (val/10000)
              dc = 5;
          else
              if (val/1000)
                dc = 4;
              else
               if (val/100)
                   dc =3;

  for (u8 i = 0;i<dc;i++)
  {
     u8 digit = val % 10;

     SetSegDirect(i,DigitMask[digit]);
     val = val/10;
  }
  SPI2_DATA[1] |= 0x0400; //Ставим точку
  if ( min )
  {
      SetSegDirect(dc,0x40);
      dc++;
  }

  for (u8 i=(dc);i<7;i++)
  {
      SetSegDirect(i,0);
  }
  switch(mask_count)
  {
      case 1:
          break;
          SPI2_DATA[3] &= 0xFF80;
          SPI2_DATA[3] |= ((mask>>8) & 0x7F);
          break;
      case 2:
          SPI2_DATA[3] &= 0xC000;
          SPI2_DATA[3] |=  ( (mask>>8 & 0x7F) | (mask & 0x7F)<<7);
          break;
      default:
          break;
  }

}


void SetBigSeg( u16 mask)
{
    SPI2_DATA[0] &= 0x0003;
    SPI2_DATA[0] |= (mask <<2);
}

/*
 *
 */
void vSetBrigth( BRIGTH_CHANNEL_t ch, u8 brigth)
{
    HAL_TIMER_SetPWMPulse(TIMER3, (ch == RGB_CHANNEL) ? TIM_CHANNEL_3 :  TIM_CHANNEL_4 , Brigth[brigth]);
    HAL_TIMER_EnablePWMCH(TIMER3,0);
    return;
}


void SPI1_DMA_Callback( void )
{
    HAL_DMA_Disable(DMA1_CH3);
    HAL_SPI_RXOveleyClear(SPI1 );
    while (HAL_SPI_GetBusy(SPI1) == HAL_SET);
    HAL_SetBit(  SPI1_Port , SPI1_NSS_Pin);
    return;
}

void SPI2_DMA_Callback( void )
{
    HAL_DMA_Disable(DMA1_CH5);
    HAL_SPI_RXOveleyClear(SPI2 );
    while (HAL_SPI_GetBusy(SPI2) == HAL_SET);
    HAL_SetBit(  SPI2_Port , SPI2_NSS_Pin);
    return;
}


/*
 *
 */
void vLedDriverStart(void)
{
	HAL_DMAInitIT(DMA1_Channel5,MTOP, DMA_HWORD  ,(u32)&SPI2->DATAR, (u32)SPI2_DATA,0,SPI2_DMA_PRIOR,SPI2_DMA_SUBPRIOR ,&SPI2_DMA_Callback);
	HAL_DMAInitIT(DMA1_Channel3,MTOP, DMA_HWORD  ,(u32)&SPI1->DATAR, (u32)data,     0,SPI1_DMA_PRIOR,SPI1_DMA_SUBPRIOR ,&SPI1_DMA_Callback);
	return;
}




/*
 *  Функция вывода данных в SPI, вызывается по прерыванию таймра №4
 */
//uint16_t data1 = 0x1;
void vLedProcess( void )
{
   HAL_ResetBit(  SPI2_Port , SPI2_NSS_Pin);
   HAL_DMA_SetCouterAndEnable(DMA1_CH5, SPI2_CHIP_COUNT);
   return;
}

void vRGBProcess()
{
     memcpy(data,SPI1_DATA,SPI1_CHIP_COUNT*2);
     if (++counterRGB >= PWM_TIM_PERIOD/2) counterRGB = 0;

      if (counterRGB++ >=BrigthR[10])
      {
          data[0]&=0x6DB6;
          data[1]&=0xDBF6;
          data[2]&=0x6DB6;
          data[3]&=0xAAAA;
          data[4]&=0xAAAA;
      }
     if (counterRGB++ >=BrigthG[10])
      {
          data[0]&=0x5B6D;
          data[1]&=0xB7ED;
          data[2]&=0x5B6D;
          data[3]&=0x5555;
          data[4]&=0x5555;

       }
      if (counterRGB >= BrigthG[10])
       {
          data[0]&=0x36DB;
          data[1]&=0x6FDB;
          data[2]&=0x56DB;
       }
    HAL_ResetBit(  SPI1_Port , SPI1_NSS_Pin);
    HAL_DMA_SetCouterAndEnable(DMA1_CH3, SPI1_CHIP_COUNT);
}

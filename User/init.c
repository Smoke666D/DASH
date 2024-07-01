#include "init.h"
#include "main.h"
#include "HW_API.h"
#include "hal_gpio.h"
#include "drivers_config.h"
#include "hal_wdt.h"
#include "hal_rtc.h"
#include "hal_adc.h"
#include "hw_lib_din.h"
#include "hal_timers.h"
#include "hal_spi.h"
#include "hw_lib_eeprom.h"

static void MX_GPIO_Init( void );






/*
Функция инициализации перефирии устройства
*/

void vInit_DeviceConfig( void )
{	
    //Настройка тактирования всех устрйоств
	MX_GPIO_Init( );
	vAINInit();
    HAL_SPI_InitDMA(SPI1, SPI_16bit );
	HAL_SPI_InitDMA(SPI2, SPI_16bit );
	HAL_RTC_IT_Init(&vIncrementSystemCounters,RTC_PRIOR,RTC_SUB_PRIOR);
	HAL_TIMER_InitIt( TIMER4, 1000000, 100, &vRGBProcess ,TIM4_PRIOR,TIM4_SUB_PRIOR);
	HAL_TiemrEneblae( TIMER4);
	HAL_TIMER_PWMTimersInit(TIMER3 , 1000000, 1000, TIM_CHANNEL_3 | TIM_CHANNEL_4  );
	HAL_TiemrEneblae( TIMER3);
	InitI2CDMA(EEPROM_I2C, I2C1_PRIOR ,I2C1_SUB_PRIOR );
	HAL_SetBit(PowerOn_Port, PowerOn_Pin);
	vCanOpenInit(CAN1);;
	return;
}



/*
Функция инициализации портов
*/
static void MX_GPIO_Init(void)
{
  // HAL_InitGpioLib();
  /*Configure GPIO pin Output Level */
   HAL_ResetBit(PORT_A, GPIO_8);
	
  //Конфигурируем порты в

  //Конфигурируем порты выхода
  HAL_InitGpioOut(PowerOn_Port , PowerOn_Pin);
//Конфигурируем порты DIN
  HAL_InitGpioIn( Din3_4_5_Port,Din3_Pin | Din4_Pin | Din5_Pin );
  /*
   * Потры RPM
   */
  HAL_InitGpioAF( Din2_Port , Din2_Pin , GPIO_PartialRemap1_TIM2 ,GPIO_Mode_IN_FLOATING );
  HAL_InitGpioAF( Din1_Port , Din1_Pin , 0 , GPIO_Mode_IN_FLOATING);
  /*
   * Порты яроксти ШИМ
   */
  HAL_InitGpioAF( nOE_Port , nOE1_Pin | nOE2_Pin  , 0 , GPIO_Mode_AF_PP);
/*
 * Порты ADC
 */
  HAL_InitGpioAIN(ADC_Port, ADC0_Pin | ADC1_Pin | ADC2_Pin | ADC3_Pin | ADC6_Pin  );
  /*
   * Порты SPI
   *
   */
  HAL_InitGpioAF(  SPI1_Port , SPI1_SCK_Pin   | SPI1_MOSI_Pin  , 0, GPIO_Mode_AF_PP);
  HAL_InitGpioAF(  SPI2_Port , SPI2_SCK_Pin   | SPI2_MOSI_Pin  , 0, GPIO_Mode_AF_PP );
  HAL_InitGpioOut(  SPI1_Port , SPI1_NSS_Pin);
  HAL_InitGpioOut(  SPI2_Port , SPI2_NSS_Pin);
 /*
  * Порты CAN
  */
  HAL_InitGpioAF(CAN_Port,CAN_TX_Pin,GPIO_Remap1_CAN1,GPIO_Mode_AF_PP);
  HAL_InitGpioAF(CAN_Port,CAN_RX_Pin,GPIO_Remap1_CAN1,GPIO_Mode_IPU);

  //Потры I2C, ремапа не нужно
  HAL_InitGpioAF( I2C1_Port , I2C1_SDA_Pin | I2C1_SCL_Pin   , 0 , GPIO_Mode_AF_OD );
}






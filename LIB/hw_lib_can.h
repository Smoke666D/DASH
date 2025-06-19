#ifndef HW_LIB_CAN_H_
#define HW_LIB_CAN_H_

#include "main.h"
#include "hal_can.h"

#define CAN_FILTER_COUNT              16
#define HALF_CAN_FILTER_COUNT		  (CAN_FILTER_COUNT/2)
#define NORMAL_CAN_ID_FILTER_COUNT   ((HALF_CAN_FILTER_COUNT)*4)
#define EXTEND_CAN_ID_FILTER_COUNT   ((HALF_CAN_FILTER_COUNT)*2)
#define MAILBOXSIZE  (NORMAL_CAN_ID_FILTER_COUNT  + EXTEND_CAN_ID_FILTER_COUNT )


typedef struct {
    uint32_t ident;
    uint16_t filter_id;
    uint8_t DLC;
    uint8_t data[8];
    uint8_t new_data;
    uint8_t extd_id;
} CANRX;

typedef enum 
{
  ANSWER_FILTER = 1,
  INPUT_FILTER  = 0,
} CLIB_FILTER_TYPE;

typedef enum
{
  ERROR_NO  = 0,
  BUFFER_FULL = 1
} ERROR_TYPE_t;


void vResetFilter( int id);
void ConfigNodeID( uint8_t node_id);
uint8_t vCanGetAnsewerMessage(CAN_FRAME_TYPE * RXPacket);
uint8_t vCheckAnswer( void );
void eMailboxFilterReset(uint32_t id) ;
ERROR_TYPE_t eMailboxFilterSet(uint32_t id, CLIB_FILTER_TYPE is_answer_fiter) ;
void vCANBoudInit( uint16_t boudrate );
void vCanRXTask(void *argument);
void APPCANSEND(CAN_TX_FRAME_TYPE *buffer);
uint8_t vCanGetMessage(CAN_FRAME_TYPE * RXPacket);
uint8_t vCanGetRequest(CAN_FRAME_TYPE * RXPacket);
uint8_t vCanChekMessage(uint32_t id);
QueueHandle_t* pCANRXgetQueue ( void );
QueueHandle_t* pCANTXgetQueue ( void );
TaskHandle_t * xGetCanRXTaskHandle ();


#endif
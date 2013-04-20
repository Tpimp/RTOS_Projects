/* 
 * File:   Data_Structs.h
 * Author: christopher.dean
 *
 * Created on April 16, 2013, 4:22 PM
 */

#ifndef DATA_STRUCTS_H
#define	DATA_STRUCTS_H

#ifdef	__cplusplus
extern "C" {
#endif
/* Hardware include. */
#include <xc.h>

/* Standard includes. */
#include <stdint.h>
#include <plib.h>
#include <FreeRTOS.h>
#include "queue.h"
#include "task.h"


    
typedef struct LED_TASK_DATA
{
    unsigned short LED_NUMBER;
    xQueueHandle My_Queue;

}LED_TASK_DATA_t;

typedef struct CONTROL_TASK_DATA
{
    xQueueHandle LED_QUEUE;
    xQueueHandle UART_TX_QUEUE;
    xQueueHandle UART_RX_QUEUE;
    xTaskHandle* NEXT_CONTROL;
    char * UART_STR_PTR;
    char LED_NUMBER;
}CONTROL_TASK_DATA_t;

typedef struct UART_TX_DATA
{
   xQueueHandle My_Queue;
}UART_TX_DATA_t;

typedef struct UART_RX_DATA
{
   xQueueHandle My_Queue;

}UART_RX_DATA_t;

#ifdef	__cplusplus
}
#endif

#endif	/* DATA_STRUCTS_H */


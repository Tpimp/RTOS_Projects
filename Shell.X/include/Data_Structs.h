/* 
 * File:   Data_Structs.h
 * Author: christopher.dean
 *
 * Created on April 16, 2013, 4:22 PM
 */

#ifndef DATA_STRUCTS_H
#define	DATA_STRUCTS_H


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


typedef short bool;


#endif	/* DATA_STRUCTS_H */


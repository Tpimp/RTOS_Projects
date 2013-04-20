/* 
 * File:   led.h
 * Author: christopher.dean
 *
 * Created on April 2, 2013, 3:58 PM
 */

#ifndef LED_H
#define	LED_H

/* Hardware include. */
#include <xc.h>
/* Standard includes. */
#include <stdint.h>
#include <plib.h>
#include "Data_Structs.h"

typedef unsigned short DELAY_MESSAGE;

static const DELAY_MESSAGE INCREASE_DELAY = 1;
static const DELAY_MESSAGE DECREASE_DELAY = 2;

static const unsigned int INVALID_LED_INDEX = 1;
static const unsigned int INVALID_LED_COMMAND = 2;

// Define programmable LED wrapper for SFR Macros
unsigned int led_drive(int lednum, int cmd, int LED_ON);

// Define LED_FlashTask
void LED_FlashTask(void * LED_DATA);
static void StaticLED_FlashTask(void * LED_DATA)
{
    LED_FlashTask(LED_DATA);
}

#endif	/* LED_H */


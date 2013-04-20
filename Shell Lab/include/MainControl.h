/* 
 * File:   SystemControl.h
 * Author: christopher.dean
 *
 * Created on April 9, 2013, 4:07 PM
 */

#ifndef MAINCONTROL_H
#define	MAINCONTROL_H
#include "Data_Structs.h"

//create static char array to store uart message in
static const char * UART_STR = "LED X is now ACTIVE.\r\n";
static short  LED_NUM_POS = 4;
// create worker function
void MainControl(void * CONTROL_DATA);
static void StaticMainControl(void * CONTROL_DATA)
{
    MainControl(CONTROL_DATA);
}

static unsigned short BUTTON_ONE = 64;
static unsigned short BUTTON_TWO = 128;
static unsigned short BUTTON_THREE = 8192;
static unsigned short BUTTON_LOCKED = -1;
static unsigned short BUTTON_DOWN = 0;



#endif	/* SYSTEMCONTROL_H */


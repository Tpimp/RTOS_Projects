/* 
 * File:   shell.h
 * Author: Christopher
 *
 * Created on April 23, 2013, 11:26 AM
 */

#ifndef SHELL_H
#define	SHELL_H

#include "UartDriver.h"
#include "led.h"
#include "simple_stack.h"
typedef enum ShellStates
{
    IOMonitor_Mode,
    Command_Mode,
    Draw_Mode,
    Fetching_Params
}SHELL_STATE;
static const char * PreAmble = "\n\rPlease press x to connect to Shell...";
static const char * CLEAR_SCRN = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r";
typedef struct ShellTaskData_t
{
    unsigned short CURRENT_LED;
    xTaskHandle LED_TASKS[3];
    xQueueHandle LED_QUEUES[3];
    SHELL_STATE CURRENT_STATE;
    SHELL_STATE NEXT_STATE;
    char * SHELL_REPEAT_MESSAGE;
}ShellTaskData;

ShellTaskData SHELL_TASK_DATA;

void ShellMainTask(void * task_data);

void ChangeState();

static void StaticShellMainTask(void * task_data)
{
    ShellMainTask(task_data);
}

void ScanButtons();
static unsigned short BUTTON_ONE = 64;
static unsigned short BUTTON_TWO = 128;
static unsigned short BUTTON_THREE = 8192;
static unsigned short BUTTON_LOCKED = -1;
static unsigned short BUTTON_DOWN = 0;

#endif	/* SHELL_H */


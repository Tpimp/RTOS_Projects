/*
    FreeRTOS V7.1.1 - Copyright (C) 2012 Real Time Engineers Ltd.


 ***************************************************************************
 *                                                                       *
 *    FreeRTOS tutorial books are available in pdf and paperback.        *
 *    Complete, revised, and edited pdf reference manuals are also       *
 *    available.                                                         *
 *                                                                       *
 *    Purchasing FreeRTOS documentation will not only help you, by       *
 *    ensuring you get running as quickly as possible and with an        *
 *    in-depth knowledge of how to use FreeRTOS, it will also help       *
 *    the FreeRTOS project to continue with its mission of providing     *
 *    professional grade, cross platform, de facto standard solutions    *
 *    for microcontrollers - completely free of charge!                  *
 *                                                                       *
 *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
 *                                                                       *
 *    Thank you for using FreeRTOS, and thank you for your support!      *
 *                                                                       *
 ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!
    
 ***************************************************************************
 *                                                                       *
 *    Having a problem?  Start by reading the FAQ "My application does   *
 *    not run, what could be wrong?                                      *
 *                                                                       *
 *    http://www.FreeRTOS.org/FAQHelp.html                               *
 *                                                                       *
 ***************************************************************************

    
    http://www.FreeRTOS.org - Documentation, training, latest information, 
    license and contact details.
    
    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell 
    the code with commercial support, indemnification, and middleware, under 
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under 
    the SafeRTOS brand: http://www.SafeRTOS.com.
 */



/* Hardware include. */
#include <xc.h>

/* Standard includes. */
#include <stdint.h>
#include <plib.h>

/* FreeRTOS includes. */
#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"
#include "Data_Structs.h"
#include "led.h"
#include "UartDriver.h"
#include "shell.h"
/* Hardware configuration. */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_2, CP = OFF, BWP = OFF
#pragma config PWP = OFF /*, UPLLEN = OFF, FSRSSEL = PRIORITY_7 */


/* Performs the hardware initialisation to ready the hardware to run this example */
static void prvSetupHardware(void);


int main(void)
{
    /* Perform any hardware initialisation that may be necessary. */
    prvSetupHardware();
    // set strobe_type
    
    LED_TASK_DATA_t LED_DATA_ONE;
    LED_DATA_ONE.LED_NUMBER = 0;
    LED_DATA_ONE.My_Queue = xQueueCreate(5,sizeof(DELAY_MESSAGE));

    LED_TASK_DATA_t LED_DATA_TWO;
    LED_DATA_TWO.LED_NUMBER = 1;
    LED_DATA_TWO.My_Queue = xQueueCreate(5,sizeof(DELAY_MESSAGE));

    LED_TASK_DATA_t LED_DATA_THREE;
    LED_DATA_THREE.LED_NUMBER = 2;
    LED_DATA_THREE.My_Queue = xQueueCreate(5,sizeof(DELAY_MESSAGE));

    xTaskHandle LED_ONE;
    xTaskHandle LED_TWO;
    xTaskHandle LED_THREE;

    
    // create MY_LED_TASK
    xTaskCreate(StaticLED_FlashTask, "MY_LED_TASK1",
                                configMINIMAL_STACK_SIZE,
                                &LED_DATA_ONE, 2, &LED_ONE);

    xTaskCreate(StaticLED_FlashTask, "MY_LED_TASK2",
                                configMINIMAL_STACK_SIZE,
                                &LED_DATA_TWO, 2, &LED_TWO);
    
    xTaskCreate(StaticLED_FlashTask, "MY_LED_TASK3",
                                configMINIMAL_STACK_SIZE,
                                &LED_DATA_THREE, 2, &LED_THREE);
    
    SHELL_TASK_DATA.LED_QUEUES[0] = LED_DATA_ONE.My_Queue;
    SHELL_TASK_DATA.LED_TASKS[0] = LED_ONE;
    SHELL_TASK_DATA.LED_QUEUES[1] = LED_DATA_TWO.My_Queue;
    SHELL_TASK_DATA.LED_TASKS[1] = LED_TWO;
    SHELL_TASK_DATA.LED_QUEUES[1] = LED_DATA_THREE.My_Queue;
    SHELL_TASK_DATA.LED_TASKS[1] = LED_THREE;
    // first initialize MainControl Static Global str (UART_STR)
   
    xTaskHandle UART_TASK_HANDLE;
    xTaskCreate(StaticUartTask, "MY_UART_TASK", configMINIMAL_STACK_SIZE,
                &ENABLED_MODULE_DATA,3, &UART_TASK_HANDLE);
    ENABLED_MODULE_DATA.UART_TX_QUEUE  = xQueueCreate(5,(sizeof(char)*255));
    ENABLED_MODULE_DATA.PARAMETER_QUEUE = xQueueCreate(5,(sizeof(char)*255));
    
    xTaskHandle Shell;
    xTaskCreate(StaticShellMainTask, "Shell",configMINIMAL_STACK_SIZE, 0,
                1,&Shell);
   
    xQueueReceive(ENABLED_MODULE_DATA.PARAMETER_QUEUE,
                        (void * const)PreAmble,0);
    /* Start the scheduler so the tasks start executing.  This function should not return. */
    vTaskStartScheduler();
}


/*-----------------------------------------------------------*/
static void prvSetupHardware(void)
{
    /* Setup the CPU clocks, and configure the interrupt controller. */
    SYSTEMConfigPerformance(configCPU_CLOCK_HZ);
    mOSCSetPBDIV(OSC_PB_DIV_2);
    INTEnableSystemMultiVectoredInt();

    /* LEDs off. */
    mPORTDClearBits(BIT_0 | BIT_1 | BIT_2);

    /* LEDs are outputs. */
    mPORTDSetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2);
    ConfigCNPullups(CN15_PULLUP_ENABLE |
                    CN16_PULLUP_ENABLE |
                    CN19_PULLUP_ENABLE);

    EnableUart(UART1,9600);
}


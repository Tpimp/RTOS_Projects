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
#include "MainControl.h"
#include "Data_Structs.h"
#include "led.h"
#include "Uart.h"
/* Hardware configuration. */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_2, CP = OFF, BWP = OFF
#pragma config PWP = OFF /*, UPLLEN = OFF, FSRSSEL = PRIORITY_7 */

/* Time is measured in "ticks".  The tick rate is set by the configTICK_RATE_HZ
configuration parameter (defined in FreeRTOSConfig.h).  If configTICK_RATE_HZ
is equal to or less than 1000 (1KHz) then portTICK_RATE_MS can be used to 
convert a time in milliseconds into a time in ticks. */
#define mainTOGGLE_PERIOD ( 200UL / portTICK_RATE_MS )


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

    xTaskHandle CONTROL_ONE;
    xTaskHandle CONTROL_TWO;
    xTaskHandle CONTROL_THREE;
    
    // create MY_LED_TASK
    xTaskCreate(StaticLED_FlashTask, "MY_LED_TASK1",
                                configMINIMAL_STACK_SIZE,
                                &LED_DATA_ONE, 1, &LED_ONE);

    xTaskCreate(StaticLED_FlashTask, "MY_LED_TASK2",
                                configMINIMAL_STACK_SIZE,
                                &LED_DATA_TWO, 1, &LED_TWO);
    
    xTaskCreate(StaticLED_FlashTask, "MY_LED_TASK3",
                                configMINIMAL_STACK_SIZE,
                                &LED_DATA_THREE, 1, &LED_THREE);
    
    // Begin creating Control Tasks 
    
    // creat the UART QUEUE and Task
    UART_TX_DATA_t UART_TX_DATA;
    UART_TX_DATA.My_Queue = xQueueCreate(5,(sizeof(char)*50));
    // creat the UART QUEUE and Task

    UART_RX_DATA_t UART_RX_DATA;
    UART_RX_DATA.My_Queue = xQueueCreate(5,(sizeof(char)*255));
    
    // Create tasls to manage UART I/O
    xTaskHandle UART_TX_HANDLE;
    xTaskHandle UART_RX_HANDLE;

    xTaskCreate(StaticUARTSendQueuedTask, "UART_Tx", configMINIMAL_STACK_SIZE,
                &UART_TX_DATA,1, &UART_TX_HANDLE);
    xTaskCreate(StaticUARTRxPoll, "UART_Rx", configMINIMAL_STACK_SIZE,
                &UART_RX_DATA,1, &UART_RX_HANDLE);

    CONTROL_TASK_DATA_t CONTROL_DATA_ONE;
    CONTROL_DATA_ONE.LED_QUEUE = LED_DATA_ONE.My_Queue;
    CONTROL_DATA_ONE.UART_TX_QUEUE = UART_TX_DATA.My_Queue;
    CONTROL_DATA_ONE.UART_RX_QUEUE = UART_RX_DATA.My_Queue;
    CONTROL_DATA_ONE.LED_NUMBER = '2'; // set on transition to two

    CONTROL_TASK_DATA_t CONTROL_DATA_TWO;
    CONTROL_DATA_TWO.LED_QUEUE = LED_DATA_TWO.My_Queue;
    CONTROL_DATA_TWO.UART_TX_QUEUE = UART_TX_DATA.My_Queue;
    CONTROL_DATA_TWO.UART_RX_QUEUE = UART_RX_DATA.My_Queue;
    CONTROL_DATA_TWO.LED_NUMBER = '3';

    CONTROL_TASK_DATA_t CONTROL_DATA_THREE;
    CONTROL_DATA_THREE.LED_QUEUE = LED_DATA_THREE.My_Queue;
    CONTROL_DATA_THREE.UART_TX_QUEUE = UART_TX_DATA.My_Queue;
    CONTROL_DATA_THREE.UART_RX_QUEUE = UART_RX_DATA.My_Queue;
    CONTROL_DATA_THREE.LED_NUMBER = '1';

    CONTROL_DATA_ONE.NEXT_CONTROL = &CONTROL_TWO;
    CONTROL_DATA_TWO.NEXT_CONTROL = &CONTROL_THREE;
    CONTROL_DATA_THREE.NEXT_CONTROL = &CONTROL_ONE;

    xTaskCreate(StaticMainControl,
                "MainControl",
                configMINIMAL_STACK_SIZE,
                &CONTROL_DATA_ONE,
                1,
                &CONTROL_ONE);

    xTaskCreate(StaticMainControl,
                "MainControl",
                configMINIMAL_STACK_SIZE,
                &CONTROL_DATA_TWO,
                1,
                &CONTROL_TWO);
    vTaskSuspend(CONTROL_TWO);

    xTaskCreate(StaticMainControl,
                "MainControl",
                configMINIMAL_STACK_SIZE,
                &CONTROL_DATA_THREE,
                1,
                &CONTROL_THREE);
    vTaskSuspend(CONTROL_THREE);

    char local_message[50];
    strcpy(local_message, UART_STR);
    local_message[LED_NUM_POS] = '1';

    xQueueSendToBack(CONTROL_DATA_ONE.UART_TX_QUEUE,
                local_message,
                (10 / portTICK_RATE_MS));

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

    initUart(UART1,9600);
}


/* 
 * File:   Uart.h
 * Author: christopher.dean
 *
 * Created on April 19, 2013, 12:08 PM
 */

#ifndef UART_H
#define	UART_H

#include "Data_Structs.h"

// DEFINE Static members of the UART Singleton Structure
static UART_MODULE MODULE_ENABLED = NULL;

static xTaskHandle UART_RX_TASK = NULL;

static xTaskHandle UART_TX_TASK = NULL;

static xQueueHandle UART_RX_QUEUE = NULL;

static xQueueHandle UART_TX_QUEUE = NULL;

static void CreateUartTasksINT(UART_MODULE umPortNum,
                                      xQueueHandle message_rx,
                                      xQueueHandle message_tx)
{
    if(UART_RX_TASK == NULL)
    {
        UART_RX_QUEUE = message_rx;
        UART_TX_QUEUE = message_tx;
        if(umPortNum == UART1)
        {
            xTaskCreate(&UARTRxPoll, "U1_RX_POLL",
                        &UART_RX_QUEUE,1,&UART_RX_TASK);
            vTaskSuspend(UART_RX_TASK);
            xTaskCreate(&UARTSendQueuedTask, "U1_TX_POLL",
                        &UART_TX_QUEUE,1,&UART_TX_QUEUE);
            vTaskSuspend(UART_TX_TASK);
        }
    }
}

void SetPinOutsUart(UART_MODULE umPortNum)
{
    // set the Pns up correctly
    if(umPortNum == UART1)
    {
     // Set the direction for the pin used by the UART as RX and TX pin 
       mPORTFClearBits(BIT_3); 
       mPORTFSetPinsDigitalOut(BIT_3); 
       mPORTFSetPinsDigitalIn(BIT_2);
    }
    else if (umPortNum == UART2)
    {
       mPORTFClearBits(BIT_5); 
       mPORTFSetPinsDigitalOut(BIT_5); 
       mPORTFSetPinsDigitalIn(BIT_4);
    
    }     
} 

void ConfigureInterrupts(UART_MODULE umPortNum)
{
    // Set the interrupt trigger condition for RX and TX
    UARTSetFifoMode(umPortNum, UART_INTERRUPT_ON_TX_NOT_FULL |
                    UART_INTERRUPT_ON_RX_NOT_EMPTY);
    if(umPortNum == UART1)
    {
        // Interrupt enabling for RX and TX section
        INTEnable(INT_U1RX,INT_ENABLED);  // RX Interrupt is enabled
        INTEnable(INT_U1TX,INT_DISABLED);  // TX Interrupt is disabled

        // set up priority level
        SetPriorityIntU1(UART_INT_PR2);
        SetSubPriorityIntU1(UART_INT_SUB_PR0);
    }
    else if(umPortNum == UART2)
    {
         // Interrupt enabling for RX and TX section
        INTEnable(INT_U2RX,INT_ENABLED);  // RX Interrupt is enabled
        INTEnable(INT_U2TX,INT_DISABLED);  // TX Interrupt is disabled
        // set up priority level
        SetPriorityIntU2(UART_INT_PR2);
        SetSubPriorityIntU2(UART_INT_SUB_PR0);
    }
    // configure for multi-vector interrupts
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    // Global Interrupt Enable
    INTEnableInterrupts();


}

static void ConfigureUart(UART_MODULE umPortNum, uint32_t ui32WantedBaud)
{
    // setup baudrate
    UARTSetDataRate(umPortNum,(uint32_t)configPERIPHERAL_CLOCK_HZ,
                    ui32WantedBaud);
    // Set the UART exchange protocol as 8-N-1
    UARTSetLineControl(umPortNum, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE |
                      UART_STOP_BITS_1);
}


 static void EnableUart(UART_MODULE umPortNum, uint32_t ui32WantedBaud)
 {
     if(MODULE_ENABLED == NULL)
     {
         SetPinOutsUart(umPortNum);
         ConfigureInterrupts(umPortNum);
         ConfigureUart(umPortNum, ui32WantedBaud);
         UARTEnable(umPortNum,
                 UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

         MODULE_ENABLED = umPortNum;
     }
 }
 
 void vUartPutC(UART_MODULE umPortNum, char cByte);
 
 void vUartPutStr(UART_MODULE umPortNum, char* pString, int iStrLen);
 
 void UARTSendQueuedTask(xQueueHandle * message_queue);

 static void StaticUARTSendQueuedTask( void * task_data)
 {
     UARTSendQueuedTask((xQueueHandle*)task_data);
 }

 void UARTRxPoll(xQueueHandle * message_queue);

 static void StaticUARTRxPoll( void * task_data)
 {
     UARTRxPoll((xQueueHandle*)task_data);
 
 }

void __ISR(_UART1_VECTOR, ipl2) U1IntHandler(void)
{
    //Check if Interrupts was RX
    if( mU1RXGetIntFlag())
    {
        // clear RX Flag
         IFS0bits.U1RXIF = 0;
         
         // Disable the RX int and kick off RXPoll task
         INTEnable(INT_U1RX,INT_DISABLED);  
         vTaskResume(UART_RX_TASK);  
    }
    
}


#endif	/* UART_H */


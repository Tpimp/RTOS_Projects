/* 
 * File:   Uart.h
 * Author: christopher.dean
 *
 * Created on April 19, 2013, 12:08 PM
 */

#ifndef UART_H
#define	UART_H

#include "Data_Structs.h"

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
    }
    else if(umPortNum == UART2)
    {
         // Interrupt enabling for RX and TX section
        INTEnable(INT_U2RX,INT_ENABLED);  // RX Interrupt is enabled
        INTEnable(INT_U2TX,INT_DISABLED);  // TX Interrupt is disabled
    }

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
     SetPinOutsUart(umPortNum);
     ConfigureInterrupts(umPortNum);
     ConfigureUart(umPortNum, ui32WantedBaud);
     UARTEnable(umPortNum,
             UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
     // LAB 3 SPECIFIC - initialize UART STR
 }
 
 void vUartPutC(UART_MODULE umPortNum, char cByte);
 
 void vUartPutStr(UART_MODULE umPortNum, char* pString, int iStrLen);
 
 void UARTSendQueuedTask(UART_TX_DATA_t * task_data);

 static void StaticUARTSendQueuedTask( void * task_data)
 {
     UARTSendQueuedTask((UART_TX_DATA_t*)task_data);
 }

 void UARTRxPoll(UART_RX_DATA_t * task_data);

 static void StaticUARTRxPoll( void * task_data)
 {
     UARTRxPoll((UART_RX_DATA_t*)task_data);
 
 }


#endif	/* UART_H */


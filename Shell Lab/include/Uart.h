/* 
 * File:   Uart.h
 * Author: christopher.dean
 *
 * Created on April 19, 2013, 12:08 PM
 */

#ifndef UART_H
#define	UART_H




#include "Data_Structs.h"




 static void initUart(UART_MODULE umPortNum, uint32_t ui32WantedBaud)
 {
     UARTSetDataRate(umPortNum,
                    (uint32_t)configPERIPHERAL_CLOCK_HZ,
                    ui32WantedBaud);
     UARTEnable(umPortNum,UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
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


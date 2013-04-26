/* 
 * File:   UartDriver.h
 * Author: christopher.dean
 *
 * Created on April 19, 2013, 12:08 PM
 */

#ifndef UARTDRIVER_H
#define	UARTDRIVER_H



#include "Data_Structs.h"


typedef unsigned int Parameter[255];

typedef unsigned int Command[4];

// DEFINE INPUT STATE
 typedef enum UART_IO_STATES
 {
     Monitor_Mode,
     Shell_Mode,
     Output_Mode
 }UART_IO_STATE;


// DEFINE Static members of the UART Singleton Structure
typedef struct UART_MODULE_DATA_t
{
    UART_IO_STATE CURRENT_STATE;
    UART_IO_STATE NEXT_STATE;
    UART_MODULE MODULE_ENABLED;
    xTaskHandle UART_TX_TASK;
    xQueueHandle UART_TX_QUEUE;
    xQueueHandle UART_RX_QUEUE;
    xQueueHandle PARAMETER_QUEUE;
    unsigned short CHAR_IN;
    unsigned short CHAR_OUT;
    int CURRENT_CHAR;
    Command COMMAND_IN;
    Parameter PARAMETER_IN;
    bool IGNORE_SPACE;
    unsigned short MONITOR_CHAR;
    void (*CALLBACK_FUNC)(void);
}UART_MODULE_DATA;

UART_MODULE_DATA ENABLED_MODULE_DATA;

static const char * CR_RECEIVED = "\015\0";

void vUartPutC(UART_MODULE umPortNum, char cByte);

void vUartPutStr(UART_MODULE umPortNum, char* pString, int iStrLen);

void ConfigureInterrupts(UART_MODULE umPortNum);

void ConfigureUart(UART_MODULE umPortNum, uint32_t ui32WantedBaud);

void SetPinOutsUart(UART_MODULE umPortNum);

void HandleUARTINTs();
void initUart(UART_MODULE umPortNum, uint32_t ui32WantedBaud);

void EnableUart(UART_MODULE umPortNum, uint32_t ui32WantedBaud);

 void UartTask(void * task_data);
 void SetMonitorMode(UART_IO_STATE Next_State, char blocking_char);
 static void StaticUartTask( void * task_data)
 {
     UartTask(task_data);
 }



#endif	/* UARTDRIVER_H */


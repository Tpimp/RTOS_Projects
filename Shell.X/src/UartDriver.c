#include "UartDriver.h"

 void vUartPutC(UART_MODULE umPortNum, char cByte)
 {
     while(UARTTransmitterIsReady(umPortNum) == 0)
     {
         vTaskDelay(2 / portTICK_RATE_MS);
     }

     UARTSendDataByte(umPortNum, cByte);
 }


 void vUartPutStr(UART_MODULE umPortNum, char *pString, int iStrLen)
 {
     int current_char = 0;
     while(current_char < iStrLen)
     {
         vUartPutC(umPortNum, *(pString + (current_char++)* sizeof(char)));
     }
 }

  void UartTask(void * task_data)
  {
      //UART_TASK_DATA_t My_Data = *(UART_TASK_DATA_t*)task_data;
      char  MyMessage[255];
      while(1)
      {

        portBASE_TYPE my_ret = xQueueReceive(ENABLED_MODULE_DATA.UART_TX_QUEUE,
                MyMessage,
                portMAX_DELAY);
        if (my_ret == pdTRUE)
        {
            vUartPutStr(ENABLED_MODULE_DATA.MODULE_ENABLED, MyMessage, strlen(MyMessage));
        }
        else
        {
            vTaskDelay(10 / portTICK_RATE_MS);
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

void initUart(UART_MODULE umPortNum, uint32_t ui32WantedBaud)
{
     UARTSetDataRate(umPortNum,
                    (uint32_t)configPERIPHERAL_CLOCK_HZ,
                    ui32WantedBaud);
     UARTEnable(umPortNum,UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX));
     // LAB 3 SPECIFIC - initialize UART STR
 }

 void EnableUart(UART_MODULE umPortNum, uint32_t ui32WantedBaud)
 {
     if(ENABLED_MODULE_DATA.MODULE_ENABLED == NULL)
     {
         SetPinOutsUart(umPortNum);
         ConfigureInterrupts(umPortNum);
         ConfigureUart(umPortNum, ui32WantedBaud);
         UARTEnable(umPortNum,
                 UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
         ENABLED_MODULE_DATA.MODULE_ENABLED = umPortNum;
         ENABLED_MODULE_DATA.CALLBACK_FUNC = NULL;
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
    // Global Interrupt Enable
    INTEnableInterrupts();


}

void SetMonitorMode(UART_IO_STATE Next_State, char block_till_char)
{
    ENABLED_MODULE_DATA.CURRENT_STATE = Monitor_Mode;
    ENABLED_MODULE_DATA.NEXT_STATE = Next_State;
    ENABLED_MODULE_DATA.MONITOR_CHAR = block_till_char;
}

void ConfigureUart(UART_MODULE umPortNum, uint32_t ui32WantedBaud)
{
    // setup baudrate
    UARTSetDataRate(umPortNum,(uint32_t)configPERIPHERAL_CLOCK_HZ,
                    ui32WantedBaud);
    // Set the UART exchange protocol as 8-N-1
    UARTSetLineControl(umPortNum, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE |
                      UART_STOP_BITS_1);
}



void __ISR(_UART1_VECTOR, ipl2)  U1IntHandler(void)
{
    //Check if Interrupts was RX
    if(IFS0bits.U1RXIF)
    {
        if(U1STAbits.URXDA == 1)
        {
             ENABLED_MODULE_DATA.CHAR_IN = UARTGetDataByte(UART1);
             switch(ENABLED_MODULE_DATA.CURRENT_STATE)
             {
                 case Monitor_Mode:
                 {
                     if(ENABLED_MODULE_DATA.CHAR_IN == ENABLED_MODULE_DATA.MONITOR_CHAR)
                     {
                         ENABLED_MODULE_DATA.CURRENT_STATE = ENABLED_MODULE_DATA.NEXT_STATE;
                         (*ENABLED_MODULE_DATA.CALLBACK_FUNC)();
                     }
                     break;
                 }
                 case Shell_Mode:
                 {
                     
                     switch(ENABLED_MODULE_DATA.CHAR_IN)
                     {
                         case 2: // SOT Start of Text
                         {
                             ENABLED_MODULE_DATA.CURRENT_CHAR = 0;
                             break;
                         }
                         case 4: // EOT End of Transmission
                         {
                             //Premature interrupt? - MUST BE A QUERY
                             // -- QUERIES DONT HAVE PARAMETERS
                             // VALID QUERIES
                             //
                             // TASK - LISTS current task states
                             // LEDS - LISTS current led Delay Variables
                             // EXIT - End SHELL
                             //PARAMETER_IN[0] = '\0';
                             ENABLED_MODULE_DATA.CURRENT_CHAR = 0;
                             //xQueueSendToBack(PARAMETER_QUEUE, PARAMETER_IN, 0);
                             break;
                         
                         }
                         case 13:
                         {
                             
                             ENABLED_MODULE_DATA.CURRENT_CHAR = 0;
                             strcpy(ENABLED_MODULE_DATA.PARAMETER_IN, CR_RECEIVED);
                             xQueueSendToBack(ENABLED_MODULE_DATA.PARAMETER_QUEUE,
                                              ENABLED_MODULE_DATA.PARAMETER_IN, 0);
                             break;
                         }
                         case 32:
                         {
                             //if(ENABLED_MODULE_DATA.IGNORE_SPACE)
                             //{
                                 ENABLED_MODULE_DATA.PARAMETER_IN
                                 [ENABLED_MODULE_DATA.CURRENT_CHAR] =
                                 ENABLED_MODULE_DATA.CHAR_IN;    
                                 ENABLED_MODULE_DATA.CURRENT_CHAR++;    
                             /*}
                             else
                             {
                                 xQueueSendToBack(ENABLED_MODULE_DATA.PARAMETER_QUEUE,
                                              ENABLED_MODULE_DATA.PARAMETER_IN, 0);
                                 ENABLED_MODULE_DATA.CURRENT_CHAR = 0;
                             }*/
                             UARTSendDataByte(ENABLED_MODULE_DATA.MODULE_ENABLED,ENABLED_MODULE_DATA.CHAR_IN);
                             break;
                         }
                         case 34:
                         {
                             ENABLED_MODULE_DATA.IGNORE_SPACE = !ENABLED_MODULE_DATA.IGNORE_SPACE;
                             UARTSendDataByte(ENABLED_MODULE_DATA.MODULE_ENABLED,ENABLED_MODULE_DATA.CHAR_IN);
                             break;
                         }
                         default:
                         {
                             
                             ENABLED_MODULE_DATA.PARAMETER_IN
                             [ENABLED_MODULE_DATA.CURRENT_CHAR] =
                             ENABLED_MODULE_DATA.CHAR_IN;
                             UARTSendDataByte(ENABLED_MODULE_DATA.MODULE_ENABLED,ENABLED_MODULE_DATA.CHAR_IN);
                             ENABLED_MODULE_DATA.CURRENT_CHAR++;
                             break;
                         }
                     }
                     break;
                 }
             }
        }
         
         //INTEnable(INT_U1RX,INT_DISABLED);  // RX Interrupt is enabled
         // clear RX Flag
         IFS0bits.U1RXIF = 0;
    }
}

#pragma vector U1IntHandler 23

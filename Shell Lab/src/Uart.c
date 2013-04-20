#include "Uart.h"

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

  void UARTSendQueuedTask(UART_TX_DATA_t * task_data)
  {
      char  MyMessage[50];
      while(1)
      {

        portBASE_TYPE my_ret = xQueueReceive(task_data->My_Queue,
                MyMessage,
                portMAX_DELAY);
        if (my_ret == pdTRUE)
        {
            vUartPutStr(UART1, MyMessage, strlen(MyMessage));
        }

      }
  }

  void UARTRxPoll(UART_RX_DATA_t * uart_rx_data)
  {
      short Current_Char = 0;
      char MyMessageBuffer[250];
      char recieved_char;
      int bytes_recieved =0;
      while(1)
      {
          while(!UARTReceivedDataIsAvailable(UART1))
          {
              vTaskDelay(10 / portTICK_RATE_MS );
          }
          while(bytes_recieved = UARTReceivedDataIsAvailable(UART1))
          {
              recieved_char = UARTGetDataByte(UART1);
              switch(recieved_char)
              {
                  // Recieved STX (start of text)
                  case 2: { Current_Char = 0; break;}
                  // Received ETX (end of text)
                  case 3:
                  {
                      //
                      MyMessageBuffer[Current_Char++] = '\0';
                      xQueueSendToBack(uart_rx_data->My_Queue, MyMessageBuffer ,
                                       125 / portTICK_RATE_MS);
                      break; 
                  }
                  case 8:
                  {
                      if(Current_Char > 0)
                      {
                          Current_Char--;
                      }
                  }
                  case 13:
                  {
                      MyMessageBuffer[Current_Char++] = '\0';
                      xQueueSendToBack(uart_rx_data->My_Queue, MyMessageBuffer ,
                                       125 / portTICK_RATE_MS);
                      Current_Char = 0;
                      break;
                  }
                  default: { MyMessageBuffer[Current_Char++] =
                             recieved_char; break;}
              }   
          }
      }
  }
  
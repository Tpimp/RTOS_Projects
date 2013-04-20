#include "MainControl.h"
#include "led.h"
#include "string.h"
void MainControl(void * CONTROL_DATA)
{
    // system control params and
    CONTROL_TASK_DATA_t* MyData = (CONTROL_TASK_DATA_t*)CONTROL_DATA;
    // create the task handle
    // create queue for message passing
    char MyMessage[50];
    char RecievedMessage[255];
    strcpy(MyMessage,UART_STR);
    MyMessage[LED_NUM_POS] = MyData->LED_NUMBER;
    // 4 LED States ALL OFF, ONE ON, TWO ON, THREE ON
    // 2 Suspended states Suspended or Active
    // 2 Key states Down or Up
    // 13 total state combinations (cant be suspended and off)
    while(1) // while the task is running
    {
        while(uxQueueMessagesWaiting(MyData->UART_RX_QUEUE))
        {
            portBASE_TYPE my_ret = xQueueReceive(MyData->UART_RX_QUEUE,
                                                 RecievedMessage,
                                                 0);
            if(my_ret == pdTRUE)
            {
                int length_message= strlen(RecievedMessage);
                int i = 0;
                while( i < length_message)
                {
                    vUartPutC(UART1,RecievedMessage[i++]);
                }
            }

        }
        if(!BUTTON_DOWN) // if not waiting for a key to be released
        {
            // Scan for a keypress beginning with button 1
            if(!mPORTDReadBits(BUTTON_ONE)) // if found button 1 down
            {
                vTaskDelay( 10/ portTICK_RATE_MS);
                if(!mPORTDReadBits(BUTTON_ONE))
                {
                    // debounced and the button is still down
                    // button one pressed
                    xQueueSendToBack(MyData->LED_QUEUE,
                                     &DECREASE_DELAY,
                                     (10/ portTICK_RATE_MS));
                    BUTTON_LOCKED = 0;
                    BUTTON_DOWN = 1;
                }

            }
            else if(!mPORTDReadBits(BUTTON_TWO))
            {
                vTaskDelay( 10/ portTICK_RATE_MS);
                if(!mPORTDReadBits(BUTTON_TWO))
                {
                    // debounced and the button is still down
                    // button one pressed
                    xQueueSendToBack(MyData->LED_QUEUE,
                                     &INCREASE_DELAY,
                                     (10/ portTICK_RATE_MS));
                    BUTTON_LOCKED = 1;
                    BUTTON_DOWN = 1;
                }
                
            }
            else if(!mPORTDReadBits(BUTTON_THREE))
            {
                vTaskDelay( 10/ portTICK_RATE_MS); // debounce
                if(!mPORTDReadBits(BUTTON_THREE))
                {
                    // debounced and the button is still down
                    // button one pressed
                    // first send the message to uart
                    xQueueSendToBack(MyData->UART_TX_QUEUE,
                                     MyMessage,
                                     (10/ portTICK_RATE_MS));
                    // then switch to next task
                    vTaskResume(*MyData->NEXT_CONTROL);
                    vTaskSuspend(NULL);
                    BUTTON_LOCKED = 2;
                    BUTTON_DOWN = 1;
               } 
            }
            //else didnt pass debounce
        }
        else
        {
            switch(BUTTON_LOCKED)
            {
                case 0:
                {
                    BUTTON_DOWN = !mPORTDReadBits(BUTTON_ONE);
                    if(!BUTTON_DOWN)
                    {
                        vTaskDelay( 10/ portTICK_RATE_MS); // debounce release
                        BUTTON_DOWN = !mPORTDReadBits(BUTTON_ONE);
                    }
                    break;
                }
                case 1:
                {
                    BUTTON_DOWN = !mPORTDReadBits(BUTTON_TWO);
                    {
                        vTaskDelay( 10/ portTICK_RATE_MS); // debounce release
                        BUTTON_DOWN = !mPORTDReadBits(BUTTON_TWO);
                    }
                    break;
                }
                case 2:
                {
                    BUTTON_DOWN = !mPORTDReadBits(BUTTON_THREE);
                    {
                        vTaskDelay( 10/ portTICK_RATE_MS); // debounce release
                        BUTTON_DOWN = !mPORTDReadBits(BUTTON_THREE);
                    }
                    break;
                }
                default : {BUTTON_DOWN = 0;break;}
            }
        }
        // Allow the idle task to run for 100 ms
        vTaskDelay( 100/  portTICK_RATE_MS);
    }
}



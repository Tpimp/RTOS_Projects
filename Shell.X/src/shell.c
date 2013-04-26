#include "shell.h"

void ShellMainTask(void * task_data)
{
    Simple_Stack ParameterStack;
    char CurrentParam[255];
    InitializeSimpleStack(&ParameterStack , 4, 255);
    //strcpy(CurrentParam, PreAmble);
    StackPushItem(&ParameterStack, PreAmble, strlen(PreAmble));
    //strcpy(CurrentParam, CLEAR_SCRN);
    StackPushItem(&ParameterStack, CLEAR_SCRN, strlen(CLEAR_SCRN));
    SetMonitorMode( Shell_Mode, 'x');
    short MESSAGE_SENT = 0;
    SHELL_TASK_DATA.SHELL_REPEAT_MESSAGE = PreAmble;
    ENABLED_MODULE_DATA.CALLBACK_FUNC = ChangeState;
    portTickType last_check = xTaskGetTickCount();
    SHELL_TASK_DATA.CURRENT_STATE = IOMonitor_Mode;
    SHELL_TASK_DATA.NEXT_STATE = Command_Mode;
    while(1)
    {
        switch(SHELL_TASK_DATA.CURRENT_STATE)
        {

            case IOMonitor_Mode:
            {
                if(!MESSAGE_SENT)
                {
                    while(ParameterStack.StackPtr > 0)
                    {
                        strcpy(CurrentParam,StackPopItem(&ParameterStack));
                        xQueueSendToBack(ENABLED_MODULE_DATA.UART_TX_QUEUE,
                                         CurrentParam, (8 / portTICK_RATE_MS));
                    }
                    MESSAGE_SENT = 1;
                }
                else
                {
                    if(SHELL_TASK_DATA.SHELL_REPEAT_MESSAGE != NULL)
                    {
                        if((xTaskGetTickCount() - last_check) > (2500UL / portTICK_RATE_MS) )
                        {
                            last_check = xTaskGetTickCount();
                            strcpy(CurrentParam,SHELL_TASK_DATA.SHELL_REPEAT_MESSAGE);
                            xQueueSendToBack(ENABLED_MODULE_DATA.UART_TX_QUEUE,
                                         CurrentParam, (8 / portTICK_RATE_MS));
                        }
                    }

                }

                break;
            }
            case Command_Mode:
            {
                strcpy(CurrentParam,CLEAR_SCRN);
                xQueueSendToBack(ENABLED_MODULE_DATA.UART_TX_QUEUE,
                                 CurrentParam, (8 / portTICK_RATE_MS));
                while(1)
                {
                    portBASE_TYPE my_ret = xQueueReceive(ENABLED_MODULE_DATA.PARAMETER_QUEUE,
                            CurrentParam,0);
                    if(my_ret == pdTRUE)
                    {
                        xQueueSendToBack(ENABLED_MODULE_DATA.UART_TX_QUEUE,
                                         CurrentParam, (10 / portTICK_RATE_MS));
                        xQueueSendToBack(ENABLED_MODULE_DATA.UART_TX_QUEUE,
                                         "\r\n", (4 / portTICK_RATE_MS));

                    }
                    ScanButtons();
                    vTaskDelay(100 /portTICK_RATE_MS );
                }
                break;
            }
            default: {break;}
        }
        ScanButtons();
        vTaskDelay(100 /portTICK_RATE_MS );
    }
}

void ScanButtons()
{
   // char MyMessage[255];
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
                    xQueueSendToBack(SHELL_TASK_DATA.LED_QUEUES[SHELL_TASK_DATA.CURRENT_LED],
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
                    xQueueSendToBack(SHELL_TASK_DATA.LED_QUEUES[SHELL_TASK_DATA.CURRENT_LED],
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
                    xQueueSendToBack(ENABLED_MODULE_DATA.UART_TX_QUEUE,
                                     (void * const)"Switching LED",
                                     (10/ portTICK_RATE_MS));
                    // then switch to next task
                    if(SHELL_TASK_DATA.CURRENT_LED < 3)
                    {
                        SHELL_TASK_DATA.CURRENT_LED++;
                    }
                    else
                    {
                        SHELL_TASK_DATA.CURRENT_LED = 0;
                    }
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
                    break;
                }
                case 1:
                {
                    BUTTON_DOWN = !mPORTDReadBits(BUTTON_TWO);
                    break;
                }
                case 2:
                {
                    BUTTON_DOWN = !mPORTDReadBits(BUTTON_THREE);
                    break;
                }
                default : {BUTTON_DOWN = 0;break;}
            }
        }
}

void ChangeState()
{
    SHELL_TASK_DATA.CURRENT_STATE = SHELL_TASK_DATA.NEXT_STATE;
}

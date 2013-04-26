#include "led.h"

/*******************************************************************
| led_drive - takes three parameters and performs 1 of
| four commands on an led sensor:
|           1.Read LED current state
|           2&3.SET LED ON or OFF
|           4.TOGGLE the LED state
| Parameters:
|   lednum: a value between 0 and 2 PORTD<2-0>
|   cmd: a value between 0 and 2 indicating which command
|   LED_ON: Default is off (0) for LED_ON value, will be used with
|       SET command (1).
| Return: return_value indicates if the command request was
|       successful and if it wasn't, why not.
*******************************************************************/
unsigned int led_drive(int lednum, int cmd, int LED_ON)
{
    unsigned int return_value = -1;
    if(lednum < 0 || lednum > 2) // LED guard statement
        return INVALID_LED_INDEX; // return invalid 
    // switch on the current command
    switch(cmd)
    {
        case 0: // READ the value for return
        {
           return_value =  mPORTDReadBits(1 << lednum);
           break;
        }
        case 1: // set the led on or off
        {
           if(LED_ON) 
           { 
               // SET LED_ON
               mPORTDSetBits(1 << lednum);
           }
           else
           {
               // SET LED_OFF
               mPORTDClearBits(1 << lednum);
           }
           return_value = 0; // return success
           break;
        }
        case 2: // TOGGLE the bits
        {
            // Toggle LED_ON/LED_OFF
            mPORTDToggleBits(1 << lednum);
            return_value = 0; // return success
            break;
        }
        // return invalid cmd
        default : { return_value = INVALID_LED_COMMAND; break;}
    }
    return return_value; // EXIT drive_led with return status
}

// LED_FlashTask takes a void * casted LED_TASK_DATA sruct
// While task is running continuosly toggle the LED on and off
// hand off to idle task for 500 Ms in between each toggle
void LED_FlashTask(void * LED_DATA)
{
    // start with 500ms as the delay
    int CURRENT_DELAY = 500;
    // count for messages waiting
    int messages_waiting = 0;
    // determine the needed amount of char's to representa DELAY_MESSAGE
    char Message[sizeof(DELAY_MESSAGE)/sizeof(char)];
    LED_TASK_DATA_t* My_Data = (LED_TASK_DATA_t*)LED_DATA;
    while(1)
    {
        messages_waiting = uxQueueMessagesWaiting(My_Data->My_Queue);
        if(messages_waiting > 0)
        {
            // UNCOMMENT BELOW TO PROVE Queue overflow possibility
            //  if(messages_waiting > 3)
            //{
            // The below line will break if there is more than one
            // message in the queue. -to provoke, rock back and forh on button
            // one and two
            //   int extra_messages = (messages_waiting -1);
            //}
            // then change the next line to 'if' instead of 'while'
            while(messages_waiting > 0)
            {
                portBASE_TYPE my_ret = xQueueReceive(My_Data->My_Queue,
                                                     &Message,
                                                     0);
                // because running while loop without checking status of queue
                // each iteration, there is possiblity to that a message was
                // pulled from a ISR or another task.
                if(my_ret ==  pdTRUE) // So always retest validity of message
                {
                    DELAY_MESSAGE current_message = *(DELAY_MESSAGE*)&Message;
                    if(current_message == DECREASE_DELAY) // if decrease
                    {
                        if(CURRENT_DELAY > 200) // if greater than threshold
                        {
                            CURRENT_DELAY -= 25; // remove 25
                        }
                    }
                    else if( current_message == INCREASE_DELAY) // else increase
                    {
                        if(CURRENT_DELAY < 1000) // if less than thresshold
                        {
                            CURRENT_DELAY += 25; // add 25
                        }
                    }
                    // else (BAD Message Recieved?)
                    messages_waiting--;
                }
                else
                    break;
            }
        }
        // toggle the led number on
        led_drive(My_Data->LED_NUMBER,2,0);
        // Nothing left to do so
        // release the processor until time to resume
        vTaskDelay( CURRENT_DELAY /portTICK_RATE_MS);
    }
}
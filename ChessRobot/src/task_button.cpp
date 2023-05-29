#include <Arduino.h>
#include <PrintStream.h>
#include <ezButton.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"

ezButton done_button(2, INPUT_PULLUP);

void task_button (void* p_params)
{
    done_button.setDebounceTime(5);
    
    while(true)
    {
        done_button.loop();
        if (done_button.isReleased() || done_button.isPressed())
        {
            button_flag.put(1);
        }     
        vTaskDelay(10);
    }
}
#include <Arduino.h>
#include <PrintStream.h>
#include <ezButton.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"

ezButton limitswitch_x(32, INPUT_PULLUP);
ezButton limitswitch_y(33, INPUT_PULLUP);

void task_limit (void* p_params)
{
    limitswitch_x.setDebounceTime(5);
    limitswitch_y.setDebounceTime(5);
    
    while(true)
    {
        limitswitch_x.loop();
        limitswitch_y.loop();
        if (limitswitch_x.isPressed())
        {
            x_flag.put(1);
        }     
        if (limitswitch_y.isPressed())
        {
            y_flag.put(1);
        }
        vTaskDelay(10);
    }
}
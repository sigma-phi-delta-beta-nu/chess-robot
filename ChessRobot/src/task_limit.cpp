#include <Arduino.h>
#include <PrintStream.h>
#include <ezButton.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"

ezButton limitswitch_x(32);
ezButton limitswitch_y(33);

void task_limit (void* p_params)
{
    limitswitch_x.setDebounceTime(50);
    limitswitch_y.setDebounceTime(50);
    
    while(true)
    {
        limitswitch_x.loop();
        limitswitch_y.loop();
        if (limitswitch_x.isPressed())
        {
            x_done.put(1);
        }
        if (limitswitch_x.isReleased())
        {
            x_done.put(0);
        }        
        if (limitswitch_y.isPressed())
        {
            y_done.put(1);
        }
        if (limitswitch_y.isReleased())
        {
            y_done.put(0);
        }
        vTaskDelay(10);
    }
}
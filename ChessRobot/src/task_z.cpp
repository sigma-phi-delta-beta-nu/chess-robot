/** @file task_z.cpp
 *  This file contains code to run the linear actuator.
 * 
 *  @author Corey Agena
 *  @date   2023-Apr-20
 */

#include <Arduino.h>
#include <PrintStream.h>
#include <SparkFun_TB6612.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"

// Pins for the linear actuator
#define CIN1 13
#define CIN2 14
#define PWMC 27
#define STBY 19

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetC = 1;

// Initialize the linear actuator.
Motor motor_z = Motor(CIN1, CIN2, PWMC, offsetC, STBY);

void task_z (void* p_params)
{

  while(true)
  {
    float trigger = z_trigger.get();
    if(trigger != 0)
    {
        motor_z.drive(155);
    }
    else
    {
        motor_z.drive(-155);
    }

    vTaskDelay(10);
  }
}
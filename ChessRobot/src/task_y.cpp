/** @file task_y.cpp
 *  This file contains code to run the y-axis motor.
 * 
 *  @author Corey Agena
 *  @date   2023-Apr-20
 */
#include <Arduino.h>
#include <PrintStream.h>
#include <ESP32Encoder.h>
#include <SparkFun_TB6612.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define BIN1 23
#define BIN2 22
#define PWMB 23
#define STBY 19

#define CLK 35
#define DT 34

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor_y = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

ESP32Encoder encoder_y;

void task_y (void* p_params)
{
  encoder_y.attachHalfQuad(CLK, DT);

  while(true)
  {
    float desired_pos = y_dist.get();
    // float desired_pos = 10000;
    float encoder_current = encoder_y.getCount();
    // Serial.print(encoder_current);
    float error = desired_pos - encoder_current;
    float new_input = 0.5*(error);

    motor_y.drive(new_input);

    if (error < 0.1 && error > -0.1)
    {
      //Serial.print("Done");
      y_flag.put(1);
    }
    
    // if (desired_pos > 0)
    // {
    //   Serial.println("ESP: Done");
    // }

    vTaskDelay(10);
  }
}
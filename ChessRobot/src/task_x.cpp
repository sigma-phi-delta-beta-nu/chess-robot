/** @file task_x.cpp
 *  This file contains code to run the x-axis motor.
 * 
 *  @author Corey Agena
 *  @date   2023-Feb-23
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
#define AIN1 18
#define AIN2 17
#define PWMA 16
#define STBY 19

#define CLK 39
#define DT 36

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor_x = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

ESP32Encoder encoder_x;

void task_x (void* p_params)
{
  encoder_x.attachFullQuad(CLK, DT);
  encoder_x.clearCount();
  x_flag.put(0);

  while(true)
  {
    if (x_flag.get() == 0)
    {
      // float desired_pos = 400;
      float desired_pos = x_dist.get();
      float encoder_current = encoder_x.getCount();
      float error = desired_pos - encoder_current;
      float new_input = 0.8*(error);
      if (new_input > 10)
      {
        motor_x.drive(50);        
      }
      else if (new_input < -10)
      {
        motor_x.drive(-50);
      }
      else
      {
        motor_x.drive(new_input);
      }
      // Serial.println(desired_pos);
      // Serial.println(encoder_current);
      // Serial.println(error);
      if (error < 0.5 && error > -0.5)
      {
        x_flag.put(1);
        // x_dist.put(encoder_current);
      }
    }
    else
    {
      motor_x.brake();
      if (x_clear.get() == 1)
      {
        encoder_x.clearCount();
        x_dist.put(0);
        x_clear.put(0);
      }
    }
    // float desired_pos = 10000;
    // float encoder_current = -encoder_x.getCount();
    // float error = desired_pos - encoder_current;
    // float new_input = -0.5*(error);
    // motor_x.drive(new_input);
    // Serial.println(desired_pos);
    // Serial.println(encoder_current);
    // Serial.println(error);
    // if (error < 0.1 && error > -0.1)
    // {
    //   Serial.print("done");
    //   x_flag.put(1);
    //   motor_x.brake();
    // }
    // float desired_pos = x_dist.get();
    // //float desired_pos = 10000;
    // float encoder_current = -encoder_x.getCount();
    // float error = desired_pos - encoder_current;
    // float new_input = -2*(error);
    // Serial.println(desired_pos);
    // Serial.println(encoder_current);
    // Serial.println(error);

    //Serial.print(encoder_current);

    // if (error < 0.1 && error > -0.1)
    // {
    //   //Serial.print("Done");
    //   x_flag.put(1);
    // }
    
    // if (desired_pos > 0)
    // {
    //   Serial.println("ESP: Done");
    // }

    vTaskDelay(10);
  }
}
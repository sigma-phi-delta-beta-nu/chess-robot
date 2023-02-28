/** @file task_x.cpp
 *  This file contains code to run the x-axis motor.
 * 
 *  @author Corey Agena
 *  @date   2023-Feb-23
 */
#include <Arduino.h>
#include <ESP32Encoder.h>
#include <SparkFun_TB6612.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 0
#define AIN2 2
#define PWMA 15
#define STBY 4

#define CLK 33
#define DT 32

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

ESP32Encoder encoder;

void task_x (void* p_params)
{
  encoder.attachHalfQuad(CLK, DT);

  while(true)
  {
    float desired_pos = 10000;
    float encoder_current = encoder.getCount();
    Serial.print(encoder_current);
    float new_input = 0.5*(desired_pos - encoder_current);

    motor1.drive(new_input);

    vTaskDelay(10);
  }

}
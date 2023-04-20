/** @file task_fingers.cpp
 *  This file contains code to run the servo motor.
 * 
 *  @author Corey Agena
 *  @date   2023-Apr-20
 */

// Include the relevant libraries
#include <Arduino.h>
#include <PrintStream.h>
#include <ESP32Servo.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"

// Define the pin used to run the servo motor
#define SERVO_PWM 25

// Define Servo a object
Servo Claw;

/** @brief   Task which implements the servo motor.
 *  @details This task sets the servo motor to the pwm recieved from the claw share.
 */
void task_claw (void* p_params)
{
    // Servo setup, attach the servo object to its corresponding pin
    Claw.attach(SERVO_PWM);

    // A on and off state were created
    while(true)
    {
        if (claw_trigger.get() != 0)
        {
            Claw.write(180);
        }
        else{
            Claw.write(0);
        }
        vTaskDelay(10);
    }
}
/** @file main.cpp
 *  This is the main file for the microcontroller portion of the Chess
 *  Robot project. The program includes code to interface with python code
 *  on the users laptop. It also includes the arduino setup function that
 *  initializes the comunication ports and gets the tasks running.
 *  After set up, the the program also includes a loop.
 * 
 *  @author Corey Agena
 *  @date   2023-Feb-23
 */

// Include the relevant libraries.
#include <Arduino.h>
#include <PrintStream.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"
#include "task_x.h"
#include "task_y.h"
#include "task_limit.h"
#include "task_button.h"
#include <iterator>

#define MAX_BUFF_LEN 255

char c;
char str[MAX_BUFF_LEN];
uint8_t idx = 0;

// Create share variables for the pwm values for the x and y motors.
Share<int32_t> x_dist (0);
Share<int32_t> y_dist (0);
Share<uint8_t>  x_flag (0);
Share<uint8_t>  y_flag (0);
Share<uint8_t>  x_done (0);
Share<uint8_t>  y_done (0);
Share<uint8_t>  x_clear (0);
Share<uint8_t>  y_clear (0);
Share<uint8_t>  button_flag (0);

uint32_t x [] = {100,800,1200,1600,2000,2400,2800,3200};
uint32_t y [] = {100,800,1200,1600,2000,2400,2800,3200};
char letter [] = {'A','B','C','D','E','F','G','H'};
char num [] = {'1','2','3','4','5','6','7','8'};

void dictionary_x(String location)
{
  for(int i = 0; i < sizeof(letter); i++)
  {
    if(location [0] == letter [i])
    {
      x_dist.put(x[i]);
    }
  }
}

void dictionary_y(String location)
{
  for(int i = 0; i < sizeof(num); i++)
  {
    if(location [0] == num [i])
    {
      y_dist.put(y[i]);
    }
  }
}

void dictionary2(String location)
{
  for(int i = 0; i < sizeof(letter); i++)
  {
    if(location[0] == letter[i])
    {
      x_dist.put(x[i]);
    }
    if(location[1] == num[i])
    {
      y_dist.put(y[i]);
    }
  }
}

void task_user(void* p_params)
{
  int state = 0;
  int i = 0;
  String commandx = "";
  String commandy = "";
  String command = "";
  int idx = 0;
  while (true)
  {
    if (state == 0)
    {
      if (i == 0)
      {
        Serial.println(state);
        i += 1;
      }
      if (button_flag.get() == 1)
      {
        button_flag.put(0);
        i = 0;
        state = 1;
      }
    }
    else if (state == 1)
    {
      if (i == 0)
      {
        Serial.println(state);
        x_dist.put(-10000);
        i += 1;
      }
      if (x_flag.get() == 1)
      {
        x_clear.put(1);
        x_flag.put(0);
        i = 0;
        state = 2;
      }
    }
    else if (state == 2)
    {
      if (i == 0)
      {
        Serial.println(state);
        i += 1;
      }
      if (button_flag.get() == 1)
      {
        button_flag.put(0);
        i = 0;
        state = 3;
      }
    }
    else if (state == 3)
    {
      if (i == 0)
      {
        Serial.println(state);
        Serial.println("Enter Command:");
        i += 1;
      }
      if(command == "")
      {
        command = Serial.readStringUntil('\n');
      }
      else
      {
        i = 0;
        state = 4;
        x_flag.put(0);
        y_flag.put(0);
      }
    }
    else if (state == 4)
    {
      if (i == 0)
      {
        Serial.println(state);
        dictionary2(command);
        i += 1;
      }
      //Serial.print(x_flag.get());
    }
    vTaskDelay(10);
  }
}


void setup(void) 
{
  Serial.begin(115200);
  //Serial1.begin(115200, 134217756U, 0, 15);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
    Serial.flush();

  // Task which runs x-axis motor. It runs at a high priority
  // stack depth was 2048
  xTaskCreate (task_x, "X Axis", 2048, NULL, 5, NULL);

  // Task which runs y-axis motor. It runs at a high priority
  xTaskCreate (task_y, "Y Axis", 2048, NULL, 5, NULL);

  // Task which runs the limit switches. It runs at a high priority
  xTaskCreate (task_limit, "Limit Switches", 2048, NULL, 5, NULL);

    // Task which runs the limit switches. It runs at a high priority
  xTaskCreate (task_button, "Button", 2048, NULL, 5, NULL);

  // Task which reads from the Serial Port
  xTaskCreate (task_user, "SerialPort", 40000, NULL, 2, NULL);
}

void loop (void) {
}
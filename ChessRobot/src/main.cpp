
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
#include <iterator>

#define MAX_BUFF_LEN 255

char c;
char str[MAX_BUFF_LEN];
uint8_t idx = 0;

// Create share variables for the pwm values for the x and y motors.
Share<uint32_t> x_dist (0);
Share<uint32_t> y_dist (0);
Share<uint8_t>  x_flag (0);
Share<uint8_t>  y_flag (0);

uint32_t x [] = {400,800,1200,1600,2000,2400,2800,3200};
uint32_t y [] = {400,800,1200,1600,2000,2400,2800,3200};
char letter [] = {'A','B','C','D','E','F','G','H'};

void dictionary1(String location)
{
  for(int i = 0; i < sizeof(letter); i++)
  {
    if(location[0] == letter [i])
    {
      x_dist.put(x[i]);
    }
    if(i == location[0])
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
    if(i == location[1])
    {
      y_dist.put(y[i]);
    }
  }
}

void task_read_n_echo(void* p_params)
{
  String data;
  while(true)
  {
    if(Serial.available() > 0)
    {
      c = Serial.read();          // read one byte
      if (c != '\n')
      {                           //still read
        str[idx++] = c;
        data += c;
      }
      else
      {                           // done reading
        str[idx] = '\0';          // convert to str
        idx = 0;
        String strs[20];
        int StringCount = 0;
        while (data.length() > 0)
        {
          int index = data.indexOf(',');
          if (index == -1) // No comma found
          {
            strs[StringCount++] = data;
            break;
          }
          else
          {
            strs[StringCount++] = data.substring(0, index);
            data = data.substring(index+1);
          }
        }

        if(strs[0] == "move")
        {
          dictionary2(strs[1]);
          if(x_flag.get() == 1 && y_flag.get() == 1)
          {
            x_flag.put(0);
            y_flag.put(0);
            dictionary2(strs[2]);
            if(x_flag.get() == 1 && y_flag.get() == 1)
            {
              x_flag.put(0);
              y_flag.put(0);
              Serial.print("done");
            }
          }
        }
        else if(strs[0] == "movx")
        {
          dictionary1(strs[1]);
          if(x_flag.get() == 1)
          {
            x_flag.put(0);
            Serial.print("done");
          }
        }
      

        //Serial.print('\n');
        // if (x_flag.get() == 0)
        // {
        //   x_dist.put(1000);
        // }

        //Serial.print(y_dist.get());
        //x_dist.put(400);
        //y_dist.put(1000);

        //Serial.print(data);
        //data = "";

          // if (data.indexOf(close)){
          // // x_dist.put(10000);
          // }
      }
    }
    vTaskDelay(10);
  }
}

void setup(void) 
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  // Task which runs x-axis motor. It runs at a high priority
  // stack depth was 2048
  xTaskCreate (task_x, "X Axis", 20480, NULL, 5, NULL);

  // Task which runs y-axis motor. It runs at a high priority
  xTaskCreate (task_y, "Y Axis", 20480, NULL, 5, NULL);

  // Task which reads from the Serial Port
  xTaskCreate (task_read_n_echo, "SerialPort", 40000, NULL, 2, NULL);
}

void loop (void) {
}
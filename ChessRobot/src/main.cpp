
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

#define MAX_BUFF_LEN 255

char c;
char str[MAX_BUFF_LEN];
uint8_t idx = 0;

// Create share variables for the pwm values for the x and y motors.
Share<uint32_t> x_dist (0);
Share<uint32_t> y_dist (0);
Share<uint8_t>  x_flag (0);

void task_read_n_echo(void* p_params){
  String data;
  String close = "close";
  while(true){
    if(Serial.available() > 0){
      c = Serial.read();          // read one byte
      if (c != '\n'){              //still read
        str[idx++] = c;
        data += c;
        }
      else{                           // done reading
        str[idx] = '\0';          // convert to str
        idx = 0;
        // Serial.print("ESP: ");
        // Serial.print(str);
        x_dist.put(10000);
        Serial.println("x_dist set to 10000");

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
  xTaskCreate (task_x, "X Axis", 2048, NULL, 5, NULL);

  // Task which reads from the Serial Port
  xTaskCreate (task_read_n_echo, "SerialPort", 4000, NULL, 2, NULL);
}

void loop (void) {}
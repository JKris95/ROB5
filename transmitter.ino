// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

void setup()
{
    pinMode(13, INPUT);
    Serial.begin(9600);	// Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
   int joystick_y = analogRead(1);
   int joystick_x = analogRead(0);

   Serial.print("joystick_y: ");
   Serial.println(joystick_y);
   Serial.print("joystick_x: ");
   Serial.println(joystick_x);
   
   const char *forward = "f";
   const char *freeze = "s";
   const char *back = "b";
   const char *right = "r";
   const char *left = "l";
   if(digitalRead(13) == HIGH || joystick_y > 900)
    {
      driver.send((uint8_t *)forward, strlen(forward));
      driver.waitPacketSent();
    }
   if(joystick_y < 100)
    {
      driver.send((uint8_t *)back, strlen(back));
      driver.waitPacketSent();
    }

    if(joystick_x > 900)
    {
      driver.send((uint8_t *)right, strlen(right));
      driver.waitPacketSent();
    }

    if(joystick_x < 100)
    {
      driver.send((uint8_t *)left, strlen(left));
      driver.waitPacketSent();
    }
   /*
   else
   {
    driver.send((uint8_t *)freeze, strlen(freeze));
    driver.waitPacketSent();
   }
  */
}

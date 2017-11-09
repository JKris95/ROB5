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
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{

   const char *forward = "f";

   while (digitalRead(13) == HIGH)
    {
      driver.send((uint8_t *)forward, strlen(forward));
      driver.waitPacketSent();
    }
}


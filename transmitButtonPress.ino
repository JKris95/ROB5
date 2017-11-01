// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK Radio(2000);

void setup()
{
    pinMode(13, INPUT);
    Serial.begin(9600);	// Debugging only
    if (!Radio.init())
         Serial.println("init failed");
}

void loop()
{
   const char *msg = "kør";
   if(digitalRead(13) == HIGH)
   {
    Radio.send((uint8_t*)msg, strlen(msg));
    Radio.waitPacketSent();
    Serial.println("running");
    delay(1000);
   }
}

// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK Radio(2000,"",2);

void setup()
{
    pinMode(13, OUTPUT);
    Serial.begin(9600);	// Debugging only
    if (!Radio.init())
         Serial.println("init failed");
}

void loop()
{
   const char *msg = "Forbindelse!";

   Radio.send((uint8_t*)msg, strlen(msg));
   Radio.waitPacketSent();
   digitalWrite(13, HIGH);
   delay(1000);
   digitalWrite(13, LOW);
}

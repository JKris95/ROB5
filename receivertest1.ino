// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK Radio(2000,2);

void setup()
{
    Serial.begin(9600);	// Debugging only
    if (!Radio.init())
         Serial.println("init failed");
}

void loop()
{
   uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
   uint8_t buflen = sizeof(buf);

   if  (Radio.recv(buf, &buflen))
   {
    int i;
    String text = "";
    int j;

  for (int j = 0; j < buflen; j++)
    {
      text += (char)buf[j];
    }
    Serial.println(text);
    }
   
   }

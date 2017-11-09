// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK Radio(2000,0);

int in1=9;
int in2=8;
int in3=7;
int in4=6;
/*define channel enable output pins*/
int ENA=10;
int ENB=5;
/*define forward function*/
void _mForward()
{ 
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Forward");
}

void _mRight()
{
  analogWrite(ENA,130);
  analogWrite(ENB,130);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Right");
}



void setup()
{
    Serial.begin(9600);  // Debugging only
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
    pinMode(ENA,OUTPUT);
    pinMode(ENB,OUTPUT);
    if (!Radio.init())
         Serial.println("init failed");
}

void loop()
{
   _mRight();
   uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
   uint8_t buflen = sizeof(buf);

   for(int i; i<15000; i++){
   
     while  (Radio.recv(buf, &buflen))
     {    
      _mForward();
     i=0;
     }
   }
}

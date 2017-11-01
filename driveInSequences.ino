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
  digitalWrite(in1,HIGH);//digital output
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Forward");
}

void _mBack()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("Back");
}

void _mRight()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Right");
}

void _mLeft()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("Left");
}

void freezeAllMotorFunctions()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
}

void setup()
{
    Serial.begin(9600);	// Debugging only
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
   uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
   uint8_t buflen = sizeof(buf);
   int i;
   String command = "";
   int j;
   if  (Radio.recv(buf, &buflen))
   {
      for (int j = 0; j < buflen; j++)
      {
        command += (char)buf[j];
      }
     
   //   command = (int)buf[0];
  
      Serial.println(command);
   }

   //if(command == "stop")
      //freezeAllMotorFunctions();
   if(command == "f")
   {
      _mForward();
      delay(500);
      freezeAllMotorFunctions();
   }
   if(command == "b")
   {
      _mBack();
      delay(500);
      freezeAllMotorFunctions();
   }

    if(command == "r")
   {
      _mRight();
      delay(150);
      freezeAllMotorFunctions();
   }

    if(command == "l")
   {
      _mLeft();
      delay(150);
      freezeAllMotorFunctions();
   }
       
}

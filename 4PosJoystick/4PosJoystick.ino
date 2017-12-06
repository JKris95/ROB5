#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
int xAxis;
int yAxis;
int switchState = 0;

int delayTime = 10;

// Driving directions
const char forward = 'f';
const char backward = 'b';
const char left = 'l';
const char right = 'r';

void setup() 
{
  pinMode(2, INPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}


void loop()
{
  xAxis = analogRead(A1); // Read Joysticks X-axis
  yAxis = analogRead(A0); // Read Joysticks Y-axis
  
  switchState = digitalRead(2);
  if (switchState == HIGH || yAxis < 250)
  {
     Serial.println("forward");
     radio.write(&forward, sizeof(forward));
     delay(delayTime);
  }

  else if (yAxis > 700)
  {
    radio.write(&backward, sizeof(backward));
    delay(delayTime);
    Serial.print("back");
  }

  else if (xAxis < 250)
  {
    radio.write(&left, sizeof(left));
    delay(delayTime);
    Serial.print("left");
  }

  else if (xAxis > 900)
  {
    radio.write(&right, sizeof(right));
    delay(delayTime);
    Serial.print("right");
  }
  
}


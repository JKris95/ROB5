#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
const char forward = 'f';
int switchState = 0;

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
  switchState = digitalRead(2);
  if (switchState == HIGH)
  {
     Serial.println("Trykket");
     Serial.println(forward);
     radio.write(&forward, sizeof(forward));
     delay(20);
  }
  
}


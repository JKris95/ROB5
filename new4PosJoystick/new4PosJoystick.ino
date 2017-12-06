#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
const char forward = 'f';
const char back = 'b';
const char right = 'r';
const char left = 'l';
int switchState2 = 0;
int switchState3 = 0;
int switchState4 = 0;
int switchState5 = 0;

void setup() 
{
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}


void loop()
{
  switchState2 = digitalRead(5);
  switchState3 = digitalRead(2);
  switchState4 = digitalRead(4);
  switchState5 = digitalRead(3);
  if (switchState2 == LOW && switchState3 != LOW && switchState4 != LOW && switchState5 != LOW)
  {
     Serial.println(digitalRead(2));
     Serial.println(forward);
     radio.write(&forward, sizeof(forward));
     delay(10);
  }
  if (switchState2 != LOW && switchState3 == LOW && switchState4 != LOW && switchState5 != LOW){
    Serial.println(digitalRead(3));
     Serial.println(back);
     radio.write(&back, sizeof(back));
     delay(10);

  }
  if (switchState2 != LOW && switchState3 != LOW && switchState4 == LOW && switchState5 != LOW){
    Serial.println(digitalRead(4));
     Serial.println(left);
     radio.write(&left, sizeof(left));
     delay(10);

  }
  if (switchState2 != LOW && switchState3 != LOW && switchState4 != LOW && switchState5 == LOW){
    Serial.println(digitalRead(5));
     Serial.println(right);
     radio.write(&right, sizeof(right));
     delay(10);

  }

}


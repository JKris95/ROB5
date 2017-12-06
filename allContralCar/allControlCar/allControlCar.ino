#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LTF analogRead(A2)
#define LTB analogRead(A3)

// RF variables
RF24 radio(8, 3); // CE, CSN
const byte address[6] = "00001";
char receivedData;

// Linescanners
int rearScan = 3;
int frontScan = 2;


// Motor variables
int in1=4;
int in2=2;
int in3=6;
int in4=7;
/*define channel enable output pins*/
int ENA=5;
int ENB=9;
//button pin


void drivingDirection()
{
  
  
    if (radio.available())// If the NRF240L01 module received data
    { 
      radio.read(&receivedData, sizeof(receivedData)); // Read the data and put it into character array
      delay(20);
      //Serial.println("received is f");
    }
    else
    {
      receivedData = 's';
      //Serial.println("received is s");
      //Serial.println(receivedData);
    }
      
  
}

void detectBoundary()
{
  if (LTF>600)
  {
    _mBack();
    delay(1000);
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);
    delay(200);
  }
  if (LTB>600)
  {
    _mForward();
    delay(1000);
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);
    delay(200);
  }
}
/*define driving functions*/
void _mForward()
{ 
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Forward");
}

void _mBack()
{
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("Back");
}

void _mRight()
{
  analogWrite(ENA,130);
  analogWrite(ENB,100);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Right");
}

void _mLeft()
{
  analogWrite(ENA,105);
  analogWrite(ENB,130);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("Left");
}

void _mStop()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("stop");
  
}

void setup()
{
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  radio.begin();
  radio.openReadingPipe(0, address); // Read from address given as 2nd argument
  radio.setPALevel(RF24_PA_MIN); // Set power level - affects range
  radio.startListening(); // Define as receiver
  pinMode(10, INPUT_PULLUP);
}

void loop()
{
  //Serial.println(digitalRead(10));
  if(receivedData == 'f'){
    while(true){
      detectBoundary();
      drivingDirection();
      //Serial.println(receivedData);
      
      if (receivedData == 'f')
      {
        _mForward(); 
      }
      else if (receivedData == 'b')
      {
        _mBack();
      }
      else if (receivedData == 'l')
      {
        _mLeft();
      }
      else if (receivedData == 'r')
      {
        _mRight();
      }
      else
        _mStop();
  }
 }
 if(receivedData == 'p'){
  while(true){
    detectBoundary();
    drivingDirection();
    Serial.println(receivedData);
    
    if (receivedData == 'p')
    {
      _mForward(); 
    }
    else
      _mRight(); 
 }
 }
}

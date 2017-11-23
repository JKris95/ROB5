// Credit to Dejan Nedelkovski, www.HowToMechatronics.com

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int in1=4;
const int in2=2;
const int in3=6;
const int in4=7;
const int ENA=5;
const int ENB=9;

RF24 radio(8, 3); // CE, CSN
const byte address[6] = "00001";
char receivedData[32] = "";
int  xAxis, yAxis;

int motorSpeedA = 0;
int motorSpeedB = 0;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
 //digitalWrite(ENA, LOW);
 //digitalWrite(ENB, LOW);
  radio.begin();
  radio.openReadingPipe(0, address); // Read from address given as 2nd argument
  radio.setPALevel(RF24_PA_MIN); // Set power level - affects range
  radio.startListening(); // Define as receiver
}

void loop() {

   // Default direction
   // Set Motor A forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  
  if (radio.available()) {   // If the NRF240L01 module received data
    radio.read(&receivedData, sizeof(receivedData)); // Read the data and put it into character array
    xAxis = atoi(&receivedData[0]); // Convert the data from the character array (received X value) into integer
    delay(10);
    radio.read(&receivedData, sizeof(receivedData));
    yAxis = atoi(&receivedData[0]);
    delay(10);
  }

  Serial.println(xAxis);
  Serial.println(yAxis);
  
  // Y-axis used for forward and backward control
  if (yAxis > 480) {
    // Set Motor A backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 509, 875, 0, 255);
    motorSpeedB = map(yAxis, 509, 875, 0, 255);
  }
  else if (yAxis < 429) {
    // Set Motor A forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 458, 100, 0, 255);
    motorSpeedB = map(yAxis, 458, 100, 0, 255);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }
  // X-axis used for left and right control
  if (xAxis < 506) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 506, 160, 0, 180);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 180) {
      motorSpeedB = 180;
    }
  }
  if (xAxis > 606) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 606, 985, 0, 180);
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA -= xMapped;
    motorSpeedB += xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 180) {
      motorSpeedA = 180;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 80) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 80) {
    motorSpeedB = 0;
  }
  analogWrite(ENA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(ENB, motorSpeedB); // Send PWM signal to motor B
}

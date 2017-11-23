/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
char xyData[32] = "";
String xAxis, yAxis; 
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {

  xAxis = analogRead(A1); // Read Joysticks X-axis
  yAxis = analogRead(A0); // Read Joysticks Y-axis

  //Used for testing and debugging
  Serial.print("xAxis: ");
  Serial.println(xAxis);
  Serial.print("yAxis: ");
  Serial.println(yAxis);
  
  // X value
  xAxis.toCharArray(xyData, 5); // Put the String (X Value) into a character array
  radio.write(&xyData, sizeof(xyData)); // Send the array data (X value) to the other NRF24L01 module
  // Y value
  yAxis.toCharArray(xyData, 5);
  radio.write(&xyData, sizeof(xyData));
 
  delay(20);
}

//www.elegoo.com

#define LT1 analogRead(A0)
#define LT2 analogRead(A1)
#define LT3 analogRead(A2)

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

void setup(){
 Serial.begin(9600);  // Debugging only
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
    pinMode(ENA,OUTPUT);
    pinMode(ENB,OUTPUT);
    }

void loop() {
  
Serial.print(analogRead(A0));
Serial.print(", ");
Serial.print(analogRead(A1));
Serial.print(", ");
Serial.println(analogRead(A2));
_mForward();
if (analogRead(A0)>600 || analogRead(A1)>600 || analogRead(A2)>600){
_mBack();
delay(1000);
}
}


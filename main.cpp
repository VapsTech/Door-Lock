#include <IRremote.h>
#include <Servo.h>
#define Open 0xFF22DD
#define Close 0xFFC23D

int receiver = 11;  // pin for the IR sensor
int Green = 40;
int Red = 48;

int clockwise;
int counterclockwise;
int read;

uint32_t Previous; 
IRrecv irrecv(receiver);
decode_results results;
Servo myservo;

void setup()
{
 Serial.begin(9600); 
 irrecv.enableIRIn(); // Start the receiver
 myservo.attach(9);  // attaches the servo on pin 9 to the servo object
 myservo.write(0);
 pinMode(Red, OUTPUT);
 pinMode(Green, OUTPUT);
 clockwise = 180;
 counterclockwise = 0;
 
}

void loop() {
  if (irrecv.decode(&results)) { //if we have received an IR signal
    if (results.value==0xFFFFFFFF) { 
        results.value=Previous;
        }
    switch (results.value) {
      case Open : myservo.write(clockwise); break;
      case Close : myservo.write(counterclockwise); break;           
        } 
  Serial.println (results.value, HEX); //display HEX results 
  irrecv.resume(); //next value
  }
  Previous = results.value;
  
  read = myservo.read();
  
  if (read == 180) {
    digitalWrite(Green, LOW);
    digitalWrite(Red, HIGH);
  } else {
    digitalWrite(Green, HIGH);
    digitalWrite(Red, LOW);
    }
}


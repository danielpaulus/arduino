/*
  Simple example for receiving
  
  http://code.google.com/p/rc-switch/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int firepin=8;

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
  pinMode(firepin, OUTPUT);
    digitalWrite(firepin, LOW);
}
//button a:  17745
//DIP switch: on,off,on,off,off
int receivedValue;
boolean debug=false;
void loop() {
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {

      receivedValue=mySwitch.getReceivedValue();
      if (debug) {
        Serial.print("Received:");
        Serial.println(receivedValue);  
      }
      
      if (receivedValue==17745){
       if(debug) 
         debug_fire();  
        else
          fire();
      }
      
    }
    if(debug) Serial.println("clearing receive buffer..");
    mySwitch.resetAvailable();
  }
}

void debug_fire(){
Serial.println("Fire and wait 5 sec");
delay(5000);
Serial.println("done!");
}
void fire(){
digitalWrite(firepin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(150);              // wait for a second
  digitalWrite(firepin, LOW);
  delay(5000);
}

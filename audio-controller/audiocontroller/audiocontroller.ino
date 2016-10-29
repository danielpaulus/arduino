/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
#include <SoftwareSerial.h>
#include <elapsedMillis.h>

elapsedMillis timeElapsed;
SoftwareSerial mySerial(10, 11); // RX, TX
byte playcommand[]= {0x7E,0xFF,0x06,0x03,0x00,0x00,0x09,0xEF};
int bewegung=7;
int bewegungsstatus=0;
boolean isActive=false;
int r=3;
int g=5;
int b=6;
int count=0;
int interval=20000;
void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
pinMode(bewegung, INPUT);
pinMode(r, OUTPUT);
pinMode(g, OUTPUT);
pinMode(b, OUTPUT);


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
analogWrite(r,255);
}


void doEffect(){
  //Serial.println("movement");
if (isActive){
  sendCommand(playcommand);
  isActive=false;
}
analogWrite(r,count);  
count++;
delay(2);
if (count>254){
count=0;
}
  

}

void loop() // run over and over
{
  
bewegungsstatus=digitalRead(bewegung);
//Serial.println(timeElapsed);
if (bewegungsstatus == HIGH)
{
  if (timeElapsed>interval){
  timeElapsed=0;
    isActive=true;
  }
}
else{
       
}
  if (timeElapsed<interval){
    doEffect();  
  }
  else{
  analogWrite(r,0);
  
  }
  
  

  /*if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());*/
}

void sendCommand(byte cmd[]){
  for (int i = 0; i < 8; i++ ) {
   mySerial.write(cmd[i]);
  }
}

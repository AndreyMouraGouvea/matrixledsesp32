#include <SPI.h>
#define CS 7



//https://www.youtube.com/watch?v=SGjQ-E3UD7A&list=PL1fGguKS29Zxgqa8A-YIpvqV9OM-cFVXZ&index=2
//MAX 7219 control registers
//LED CONTROL LIBRARY


int pirdata = 0;       // pir D is connected to D15
int pirstate = LOW;      // assuming no motion 
int value = 0;            // to read pin status 
int led = 21;

//CLK - 13
//CS - 07
//DIN - 11

void setup() {



  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32-S2!");
  Serial.println("Presence Sensor Program is Running!");
  pinMode(led, OUTPUT);
  pinMode(pirdata, INPUT); 

}

void loop() {
  
  

  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
  presence();
  

}


void SendData(uint8_t address, uint8_t value){
  digitalWrite(CS, LOW);
  SPI.transfer(address); //send address
  SPI.transfer(value); //send value
  digitalWrite(CS, HIGH); //finish transfer 
}



void ledF(){

  int x = 0;
  for (x; x<2; x++) {
    digitalWrite(13, HIGH);
    delay(2000);
    digitalWrite(13, LOW);
    delay(2000);
  }
}


void presence(){
  
  value = digitalRead(pirdata);  
  if (value == HIGH) {           
    digitalWrite(21, HIGH);  
    Serial.println("PRESENCE DETECTED!");
    delay(3000);
    digitalWrite(21, LOW);
    pirstate = LOW;
    Serial.println("PRESENCE NO MORE DETECTED!");
    delay(10000);
    if (pirstate == LOW) {
     
      Serial.println("Nothing!");
      
      pirstate = HIGH;
    }
  } 
}

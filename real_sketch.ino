#include "LedControl.h"
#include <NewPing.h>

#define TRIGGER_PIN 32
#define ECHO_PIN 33
#define MAX_DISTANCE 200 // Maximum distance to measure in centimeters

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int LED_PIN = 14;
int value = 0;   
//int ledAzul = 14;
int pirdata = 27;       // pir D is connected to D15
int pirstate = LOW;  

LedControl lc=LedControl(32,25,23,1);
unsigned long delaytime=100;

void rows() {
  for(int row=0;row<8;row++) {
    delay(delaytime);
    lc.setRow(0,row,B10100000);
    delay(delaytime);
    lc.setRow(0,row,(byte)0);
    for(int i=0;i<row;i++) {
      delay(delaytime);
      lc.setRow(0,row,B10100000);
      delay(delaytime);
      lc.setRow(0,row,(byte)0);
    }
  }
}

void columns() {
  for(int col=0;col<8;col++) {
    delay(delaytime);
    lc.setColumn(0,col,B10100000);
    delay(delaytime);
    lc.setColumn(0,col,(byte)0);
    for(int i=0;i<col;i++) {
      delay(delaytime);
      lc.setColumn(0,col,B10100000);
      delay(delaytime);
      lc.setColumn(0,col,(byte)0);
    }
  }
}

void single() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setLed(0,row,col,true);
      delay(delaytime);
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        delay(delaytime);
        lc.setLed(0,row,col,true);
        delay(delaytime);
      }
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  lc.shutdown(0,false);
  /* Set the brightness to a medium values up to 15 */
  lc.setIntensity(0,5);
  /* and clear the display */
  lc.clearDisplay(0);
  //ledON();

}

void loop() {

  //LED PERNA maior para esquerda - ligacao digital, perna menor = GND
  //presence();
  //Serial.println(pirstate);
  single();
  ledON();
  //distance();
  

  

}

void distance(){
  unsigned int distance = sonar.ping_cm(); // Measure distance in centimeters
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1500);
}

void ledON(){
  digitalWrite(LED_PIN, HIGH);
  delay(10000);
  digitalWrite(LED_PIN, LOW);
}

void presence(){
  
  value = digitalRead(pirdata);  //do... while
  Serial.println(pirdata);
  do {
    Serial.println("PRESENCE DETECTED!");
    Serial.println(pirstate);
    digitalWrite(LED_PIN, HIGH);  
    if(value == 1){
      digitalWrite(LED_PIN, HIGH);
    }else{
      digitalWrite(LED_PIN, LOW);
    }
    delay(3000);
  } while (pirdata == 0);
  digitalWrite(LED_PIN, LOW);
  Serial.println("NO PRESENCE");
  delay(3000);
    
  } 

 

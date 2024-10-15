#include "LedControl.h"

int ledPIR = 14;
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
  pinMode(ledPIR, OUTPUT);
  //pinMode(ledAzul, OUTPUT);
  pinMode(pirdata, INPUT); 

  lc.shutdown(0,false);
  /* Set the brightness to a medium values up to 15 */
  lc.setIntensity(0,5);
  /* and clear the display */
  lc.clearDisplay(0);
  //ledON();

}

void loop() {
  // put your main code here, to run repeatedly:
  //LED PERNA maior para esquerda - ligacao digital, perna menor = GND
  presence();
  Serial.println(pirstate);
  Serial.println("teste");
  single();

  

}

/*void ledON(){
  for(int i = 0; i<=1; i++){
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledAzul, HIGH);
    delay(3000);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledAzul, LOW);
    delay(8000);
    Serial.println("LED'S FORAM ACESOS!");
  }
}*/

void presence(){
  
  value = digitalRead(pirdata);  //do... while
  Serial.println(pirdata);
  do {
    Serial.println("PRESENCE DETECTED!");
    Serial.println(pirstate);
    digitalWrite(ledPIR, HIGH);  
    if(value == 1){
      digitalWrite(ledPIR, HIGH);
    }else{
      digitalWrite(ledPIR, LOW);
    }
    delay(3000);
  } while (pirdata == 0);
  digitalWrite(ledPIR, LOW);
  Serial.println("NO PRESENCE");
  delay(3000);
    
  } 

 

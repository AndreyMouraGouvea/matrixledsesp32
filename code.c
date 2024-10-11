#define BLYNK_TEMPLATE_ID "TMPL2OosqVmHD"
#define BLYNK_TEMPLATE_NAME "Andrey"
#define BLYNK_AUTH_TOKEN "NrgGcMfHgbQ18NGUvLfvZPskVlEXnNmU"


#include <SPI.h>
#include <BlynkSimpleEsp32.h>
#include <string.h>
#define CS 7


char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;






//https://www.youtube.com/watch?v=SGjQ-E3UD7A&list=PL1fGguKS29Zxgqa8A-YIpvqV9OM-cFVXZ&index=2
//MAX 7219 control registers
//LED CONTROL LIBRARY
//https://youtu.be/UTLexTqelk8?si=CSS7BXKV-GPiTbtK
//https://youtu.be/H6Vs98-Cev0?si=lJ5jcgBU1OPxm65d


int pirdata = 0;       // pir D is connected to D15
int pirstate = LOW;      // assuming no motion 
int value = 0;            // to read pin status 
int led = 21;


void setup() {

  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32-S2!");
  Serial.println("Presence Sensor Program is Running!");
  Blynk.begin(auth, ssid, pass);
  pinMode(led, OUTPUT);
  pinMode(pirdata, INPUT); 

}

void loop() {
  
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
  presence();
  Blynk.run();
  timer.run();
  sendPIRdata();
  
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


int presence(){
  
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
  return pirstate;
}

BLYNK_WRITE(V3) {
  int buttonState = param.asInt();
  if (buttonState == 1) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}

void sendPIRdata() {
  presence();

  if (pirstate == 0) {
    
    char ans[]= "No presence!"; 
    Serial.println("");
    //Serial.println(ans);
    Blynk.virtualWrite(V6, ans);
    delay(3000);
    pirstate = 0;
  } else if(pirstate == 1){
    char ans[] = "Presence!"; 
    Serial.println("");
    //Serial.println(ans);
    Blynk.virtualWrite(V6, ans);
    delay(3000);
    pirstate = 0;
  }
  //pirstate == 0 ? Serial.println("No presence") : Serial.println("Presence");
  Blynk.virtualWrite(V0, pirstate);
  //Serial.println(pirstate);

  Serial.print("Presence: ");
  Serial.print(pirstate);
}

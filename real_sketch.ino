int ledPIR = 14;
int value = 0;   
//int ledAzul = 14;
int pirdata = 27;       // pir D is connected to D15
int pirstate = LOW;  


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ledPIR, OUTPUT);
  //pinMode(ledAzul, OUTPUT);
  pinMode(pirdata, INPUT); 
  //ledON();

}

void loop() {
  // put your main code here, to run repeatedly:
  //LED PERNA maior para esquerda - ligacao digital, perna menor = GND
  presence();
  Serial.println(pirstate);
  Serial.println("teste");
  

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

 

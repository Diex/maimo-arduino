// Include Libraries
#include "Arduino.h"


void setup() {
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600);
  Serial.println("start");
  pinMode(LED_BUILTIN, OUTPUT);    
  pinMode(8, OUTPUT);
  pinMode(6, OUTPUT);
}

/* This code is the main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop. */
void loop() {
  String comandos = "";

  // Serial.print(Serial.readString());     es para ver que la comunicacion funciona...
  
  if (Serial.available())
  {
    // leo hasta que termina la linea
    comandos = Serial.readStringUntil('\n');    
    Serial.print("@echo: ");
    Serial.println(comandos); // imprimo de nuevo lo qeue lei (echo)
  }
  
  if (comandos.equals("on"))
  {    
    digitalWrite(8, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("on");
    analogWrite(6, 245);
    
  }
 
  if (comandos.equals("off"))
  {
    digitalWrite(8, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("off");
    analogWrite(6, 10);
  }
}





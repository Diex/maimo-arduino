#include "steer.h"

//This will run only one time.
void setup(){
  Serial.begin(9600);
  steerSetup();     
}


void loop(){
  delay(1);
  joy();
  run();
  
}



#include "steer.h"
#include "lineFollower.h"
//This will run only one time.
void setup(){
  Serial.begin(9600);
  lineFollowerSetup();
  steerSetup();     

}


void loop(){
  delay(1);
  readSensors();
  updateSensors();
  // joy();
  // run();
  
}



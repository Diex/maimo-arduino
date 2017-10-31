#include "steer.h"
#include "lineFollower.h"
// This will run only one time.
void setup()
{
  Serial.begin(9600);
  lineFollowerSetup();
  steerSetup();
}

void loop()
{
  delay(10); // gano tiempo...
  // ------------------------------------
  readSensors();
  updateSensors();
  // switch (status)
  // {
  //   case B00001001:
  //     drive(500, 0);
  //     update();
  //     run();
  //     break;

  //   case B00001101:  // me estoy saliendo 
  //     drive(500, 0);
  //     update();
  //     run();
  //     break;
  // }
  motors(500, 1000);
  run();
  // ------------------------------------
  // joy();
}

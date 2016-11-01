// slowChange.ino - Arduino sketch to show a fading example of a DC motor using the Ardumoto Shield
// Copyright 2012 Jeroen Doggen (jeroendoggen@gmail.com)
//
// Program flow:
//   - change motor speed to +100% (motor should accelerate slowly)
//   - change motor speed to -100% (motor should slow down en slowly reverse direction)
//   - set motor at 100% speed (sudden change in motor speed to 100%)
//   - set motor at 100% speed (sudden change in motor speed to -100%)

#include <L298.h>

L298 Moto;

void setup()
{
  Serial.begin(115200);
  Moto.beginMotoA(47, 49, 2);
  Moto.beginMotoB(51, 53, 3);
}

void loop()
{

  Moto.setSpeed('A', 50);  
  Moto.setSpeed('B', 75);
delay(2000);
  Moto.setSpeed('A', 0);  
  Moto.setSpeed('B', 0);

delay(2000);
  Moto.setSpeed('A', -50);  
  Moto.setSpeed('B', -75);

delay(2000);
//  delay (2000);
//  Moto.slowChange('A',-100);
//  delay (2000);
//  Moto.setSpeed('A',100);
//  delay (2000);
//  Moto.setSpeed('A',-100);
//  delay (2000);
}

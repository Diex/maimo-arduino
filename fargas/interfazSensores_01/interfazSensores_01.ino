#include "Sensor.cpp"
// cuatro sensores fargas
uint8_t ir  = 2;
uint8_t audio     = 3;
uint8_t cap    = 4;
uint8_t temp   = A0;

Sensor capSensor(cap, false, true);
Sensor audioSensor(audio, false, false);
Sensor irSensor(ir, false, false);
Sensor tempSensor(temp, true, false);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  attachInterrupt(1, audioInterrupt, CHANGE);
  attachInterrupt(0, irInterrupt, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(33);
  capSensor.update();
  audioSensor.update();
  irSensor.update();
  tempSensor.update();
  
    irSensor.debug();
    audioSensor.debug();
    capSensor.debug();
    tempSensor.debug();
    Serial.println("--------------");

}

void audioInterrupt() {
  audioSensor.handleInterrupt();
}

void irInterrupt(){
  irSensor.handleInterrupt();
}

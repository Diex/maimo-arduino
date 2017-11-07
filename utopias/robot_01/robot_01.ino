#include "steer.h"
#include "lcd.h"
#include "lineFollower.h"
#include "CmdMessenger.h" // CmdMessenger

const int dataPin = 2; // the number of the pushbutton pin

volatile int transmit = 0;

void interr(){
  transmit = !transmit; // digitalRead(2);
  
}

// This will run only one time.
void setup()
{
  Serial.begin(9600);
  lineFollowerSetup();
  steerSetup();
  lcdSetup();
  // commSetup();
  // testSequence();
  pinMode(dataPin, INPUT);
  attachInterrupt(0, interr, FALLING);
}

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers



void loop()
{
  if(transmit) {
    lcdPrintCommand("ROBOT: GO");
  }else{
    lcdPrintCommand("ROBOT: STOP");
  }

  delay(1); // gano tiempo...
  // ------------------------------------
  // Process incoming serial data, and perform callbacks
  // cmdMessenger.feedinSerialData();
  readSensors();
  updateSensors();
  if (status == B00001111)
  // encontró un blanco, hasta que no encuentra una linea completa no para)
  pathFinding();
  robotWalk();
  run();
  // lcdPrintStatus(status);
}

void pathFinding()
{
  int turn;
  turn = random(1000) < 500? 1:-1;
  while (status != B00000000)
  {
    rotate(turn, med);
    run();
    readSensors();
    updateSensors();
  }
}

void robotWalk()
{
  switch (status)
  {
    // AVANZA
    case B00001001:
      drive(med, 0);
      run();
      break;
    case B00001101:
      drive(med, 0);
      run();
      break;
    case B00001011:
      drive(med, 0);
      run();
      break;
    case B00000000:
      drive(med, 0);
      run();
      break;
      // COMPENSACION A LA IZQUIERDA
      case B00001000:// me estoy saliendo a la derecha.
      motors(-med, med);
      run();
      break;
      case B00001100:// me estoy saliendo a la derecha poquito.
      motors(-med, med);
      run();
      break;
      case B00001110:// me estoy saliendo a la derecha mucho.
      motors(-med, med);
      run();
      break;
      // COMPENSACION A LA DERECHA
      case B00000001:// me estoy saliendo a la izquierda.
      motors(med, -med);
      run();
      break;
      case B00000011:// me estoy saliendo a la izquierda poquito.
      motors(med, -med);
      run();
      break;
      case B00000111:// me estoy saliendo a la izquierda mucho.
      motors(med, -med);
      run();
      break;
      default://
      motors(0, 0);
      run();
      break;
  }
}


unsigned long previousOn = 0;        // will store last time LED was updated
unsigned long onInterval = 1000;
unsigned long previousOff = 0;
unsigned long offInterval = 1000;

void playTones() {

  unsigned long currentMillis = millis();
  
  if(currentMillis - previousOn >= onInterval){
    onInterval = random(100);
    previousOn = currentMillis; 
    tone(BUZZER, random(1000, 4000));   
  }
  
  if(currentMillis - previousOff >= offInterval){
    offInterval = 20 + random(1500);
    previousOff = currentMillis;
    tone(BUZZER, random(1000, 4000));   
  }
  // put your main code here, to run repeatedly:
}

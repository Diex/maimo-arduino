#include "steer.h"
#include "lcd.h"
#include "lineFollower.h"
#include "CmdMessenger.h" // CmdMessenger

#define GO            1
#define DOWNLOADING   2
#define WAITING       4
int action = GO;


unsigned long nextUpdate = 10E3;
unsigned long timeout = 10E3;
unsigned long pFrameTime = 0;        //

int frameRate = 20;


#include "download.h" // este archivo usa las variables anterios de tiempo... ^^^

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
  downloadSetup();

  pinMode(dataPin, INPUT);
  attachInterrupt(0, interr, FALLING);
}

// unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
// unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers




void loop()
{
  // if(transmit) {
  //   lcdPrintCommand("ROBOT: GO");
  // }else{
  //   lcdPrintCommand("ROBOT: STOP");
  // }

  delay(1); // gano tiempo...
  // ------------------------------------
  // Process incoming serial data, and perform callbacks
  unsigned long currentTime = millis();  

  readSensors();
  updateSensors();

  if (status == B00001111) // encontró un blanco, hasta que no encuentra una linea completa no para)
  pathFinding();
  
  
  if ((currentTime - pFrameTime) >= frameRate) {
    pFrameTime = currentTime;
    switch (action) {
      case GO:
        {
          lcdPrintCommand("ROBOT: GO");
          if (currentTime >= nextUpdate) {
             nextUpdate = currentTime + random(timeout)  ; // set up the next timeout period
             action = action == GO ? DOWNLOADING : GO;

            stop();
            run();
          }
          
          playKit();
          silence();
          robotWalk();
          run();
          break;
        }

        case DOWNLOADING:
        {
          lcdPrintCommand("ROBOT: DOWNLOADING");
          playSound();
          playDownloading(currentTime);
          
          break;
        }

        case WAITING:
        {
          lcdPrintCommand("ROBOT: WAITING");
          delay(3E3 + random(10E3));
          nextUpdate = currentTime + random(timeout)  ; // set up the next timeout period
          action = GO;
          break;
        }
    }
  }
  
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




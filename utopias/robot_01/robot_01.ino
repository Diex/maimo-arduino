#include "steer.h"
#include "lcd.h"
#include "lineFollower.h"
#include "communications.h"

#include "CmdMessenger.h"  // CmdMessenger
// This will run only one time.
void setup()
{
  Serial.begin(9600);
  lineFollowerSetup();
  steerSetup();
  lcdSetup();
  // commSetup();
  // testSequence();
  pinMode(2, INPUT);
}

void loop()
{
  delay(1); // gano tiempo...
  // ------------------------------------
  // Process incoming serial data, and perform callbacks
  // cmdMessenger.feedinSerialData();

  readSensors();
  updateSensors();
    
  if(status == B00001111)// encontró un blanco, hasta que no encuentra una linea completa no para)
    pathFinding();

  // robotWalk();
  run();

  if(digitalRead(2)){
    lcdPrintCommand("ROBOT: GO");
  }else{
    lcdPrintCommand("ROBOT: STOP");
  }
   

  

  // lcdPrintStatus(status);
  


  
}

void pathFinding(){

      int turn;
      turn = random(1000) < 500 ? 1 : -1;
      while(status != B00000000)      {
        rotate(turn, med);
        run();
        readSensors();
        updateSensors();
      }
}

void robotWalk(){
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



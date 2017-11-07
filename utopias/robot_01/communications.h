#include "Arduino.h"
#include "CmdMessenger.h"  // CmdMessenger


#ifndef _COMM_DEFS_
#define _COMM_DEFS_


const byte STOP 	= 1;
const byte GO 		= 2;
const byte LEFT 	= 4;
const byte RIGHT 	= 8;

CmdMessenger cmdMessenger = CmdMessenger(Serial1);



enum
{
  rRobotGo              , // Command to request led to be set in specific state
  rRobotStop              , // Command to report status
  rRobotDefault				,
};




// Called when a received command has no attached function
void OnUnknownCommand()
{
	lcdPrintCommand("UNKNOWN CMD");
  // cmdMessenger.sendCmd(kStatus,"Command without attached callback");
}

// Callback function that sets led on or off
void OnRobotGo()
{
	lcdPrintCommand("ROBOT: GO");
}

void OnRobotStop()
{
	lcdPrintCommand("ROBOT: STOP");
}

// Callbacks define on which received commands we take action
void attachCommandCallbacks()
{
  // Attach callback methods
  cmdMessenger.attach(OnUnknownCommand);
  cmdMessenger.attach(rRobotGo, OnRobotGo);
  cmdMessenger.attach(rRobotStop, OnRobotStop);
}

void commSetup(){
  Serial.begin(9600);
  //2400 baud for the 434 model
  Serial1.begin(600);  // con 600 no tengo problemas de ruido

 // Adds newline to every command
  cmdMessenger.printLfCr();   

  // Attach my application's user-defined callback methods
  attachCommandCallbacks();

  // Send the status to the PC that says the Arduino has booted
  // Note that this is a good debug function: it will let you also know 
  // if your program had a bug and the arduino restarted  
  // cmdMessenger.sendCmd(rRobotDefault,"Arduino has started!");
  // Attach a new CmdMessenger object to the default Serial port
}


// void commDataReceive(){
//   if (Serial1.available() > 0) {
//     incomingMessage = Serial1.readUntil('\n');    
//     Serial.println(incomingMessage, DEC);
//   } 
// }
#endif
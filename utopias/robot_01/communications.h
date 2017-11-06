#include "Arduino.h"

#ifndef _COMM_DEFS_
#define _COMM_DEFS_

const byte STOP 	= 1;
const byte GO 		= 2;
const byte LEFT 	= 4;
const byte RIGHT 	= 8;

char[] incomingMessage;

void commSetup(){
  Serial.begin(9600);
  //2400 baud for the 434 model
  Serial1.begin(600);  // con 600 no tengo problemas de ruido
}


void commDataReceive(){
  if (Serial1.available() > 0) {
    incomingMessage = Serial1.readUntil('\n');    
    Serial.println(incomingMessage, DEC);
  } 
}
#endif
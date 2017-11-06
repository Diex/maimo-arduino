#include "Arduino.h"

#ifndef _PIN_DEFS_
#define _PIN_DEFS_

// PWM en mega del 0 al 13, 44, 45 y 46
// Motor A
const int motorPin1 = 9; // Pin 14 of L293
const int motorPin2 = 10; // Pin 10 of L293
// Motor B
const int motorPin3 = 6; // Pin  7 of L293
const int motorPin4 = 5; // Pin  2 of L293


const int LCD_D4 = 22;
const int LCD_D5 = 24;
const int LCD_D6 = 26;
const int LCD_D7 = 28;
const int LCD_RS = 30;
const int LCD_EN = 32;


const int xjoy = A1;
const int yjoy = A0;
// SENSORES SEGUIDOR DE LINEA 
// los sensores estan definidos viendo al robot desde arriba
// L1 L2 -- -- R2 R1
const int CNY_R1 = A4;
const int CNY_R2 = A5;
const int CNY_L2 = A6;
const int CNY_L1 = A7;




#endif

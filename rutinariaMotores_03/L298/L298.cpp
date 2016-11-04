// L298.cpp - Arduino library to control DC motors using the L298 Shield
// Copyright 2012 Jeroen Doggen (jeroendoggen@gmail.com)

#include <L298.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include <pins_arduino.h>
#endif

/// Constructor
L298::L298()
{
  _motoSpeedA = 0;
  _motoSpeedB = 0;
}

/// Destructor
L298::~L298()
{
//do something here? (free(), delete()?)
}

// /// Begin Function: begin with default values (pin selection)
// void L298::begin()
// {
//   beginMotoA(DIRECTION_PIN_A, PWM_PIN_A);
//   beginMotoB(DIRECTION_PIN_B, PWM_PIN_B);
// }

/// Begin Function for moto A (pin selection)
void L298::beginMotoA(int pinA1, int pinA2, int pwmPin)
{
  PIN_A1 = pinA1;
  PIN_A2 = pinA2;
  PWM_PIN_A = pwmPin;

  pinMode(PWM_PIN_A, OUTPUT);                     //Set control pins to be outputs
  analogWrite(PWM_PIN_A, 0);                      //set moto A to run at (0/255 = 0)% duty cycle (stopped)

  pinMode(PIN_A1, OUTPUT);
  pinMode(PIN_A2, OUTPUT);

  DIR_A = 1;
}

/// Begin Function for moto B
void L298::beginMotoB(int pinB1, int pinB2, int pwmPin)
{
  PIN_B1 = pinB1;
  PIN_B2 = pinB2;
  PWM_PIN_B = pwmPin;

  pinMode(PWM_PIN_B, OUTPUT);                     //Set control pins to be outputs
  analogWrite(PWM_PIN_B, 0);                      //set moto A to run at (0/255 = 0)% duty cycle (stopped)

  pinMode(PIN_B1, OUTPUT);
  pinMode(PIN_B2, OUTPUT);

  DIR_B = 1;
}

/// setSpeed: from -100 to + 100
void L298::setSpeed(char moto, int speed)
{
  int throttle = map(abs(speed), 0, 100, 0, 255);

  if (moto == 'A')
  {
    _motoSpeedA = speed;
    if (speed >= 0)
    {
      digitalWrite(PIN_A1, HIGH);
      digitalWrite(PIN_A2, LOW);
    }
    if (speed < 0)
    {
     digitalWrite(PIN_A1, LOW);
      digitalWrite(PIN_A2, HIGH);
    }
#ifdef DEBUG_MOTORS
    Serial.print("Setting Motor A to ");
    Serial.println(speed);
#endif
    analogWrite(PWM_PIN_A, throttle);
  }
  else if (moto == 'B')
  {
    _motoSpeedB = speed;
    if (speed >= 0)
    {
     digitalWrite(PIN_B1, HIGH);
      digitalWrite(PIN_B2, LOW);
    }
    if (speed < 0)
    {
      digitalWrite(PIN_B1, LOW);
      digitalWrite(PIN_B2, HIGH);
    }
#ifdef DEBUG_MOTORS
    Serial.print("Setting Motor B to ");
    Serial.println(speed);
#endif
    analogWrite(PWM_PIN_B, throttle);
  }
}

/// slowChange: set the speed to desiredSpeed, adjusting slowly towards the desired value
/// Warning: this code includes a "delay()" this causes problems when using multiple motors
void L298::slowChange(char moto, int desiredSpeed)
{
  if (moto == 'A')
  {
#ifdef DEBUG_MOTORS
    int difference;
    difference = desiredSpeed - _motoSpeedA;
    Serial.print("Difference: ");
    Serial.println(difference);
#endif
    while ( _motoSpeedA != desiredSpeed)
    {
      if ( _motoSpeedA < desiredSpeed )
      {
        _motoSpeedA++;
        setSpeed(moto, _motoSpeedA);
      }
      if ( _motoSpeedA > desiredSpeed )
      {
        _motoSpeedA--;
        setSpeed(moto, _motoSpeedA);
      }
      delay(SLOWCHANGEDELAY);
    }
  }
  if (moto == 'B')
  {
#ifdef DEBUG_MOTORS
    difference = desiredSpeed - _motoSpeedB;
    Serial.print("Difference: ");
    Serial.println(difference);
#endif
    while ( _motoSpeedB != desiredSpeed)
    {
      if ( _motoSpeedB < desiredSpeed )
      {
        _motoSpeedB++;
        setSpeed(moto, _motoSpeedB);
      }
      if ( _motoSpeedB > desiredSpeed )
      {
        _motoSpeedB--;
        setSpeed(moto, _motoSpeedB);
      }
      delay(SLOWCHANGEDELAY);
    }
  }
}

/// stop the motor
void L298::stop(char moto)
{
  setSpeed(moto, 0);
#ifdef DEBUG_MOTORS
  if (moto == 'A')
  {
    Serial.println("Stopping Motor A");
  }
  else if (moto == 'B')
  {
    Serial.println("Stopping Motor B");
  }
#endif
}

/// brake: brake the motor, using a temporary negative value (uses slowChange)
/// Warning: this code includes a "delay()" this causes problems when using multiple motors
void L298::brakeAgressive(char moto)
{
  if (moto == 'A')
  {
#ifdef DEBUG_MOTORS
    Serial.println("Braking Motor A");
#endif
    setSpeed(moto, - _motoSpeedA / BRAKESPEED);
    slowChange(moto, 0);

  }
  else if (moto == 'B')
  {
#ifdef DEBUG_MOTORS
    Serial.println("Braking Motor B");
#endif
    setSpeed(moto, - _motoSpeedB / BRAKESPEED);
    slowChange(moto, 0);
  }
}

/// brake: really braking the motor electronically is not possible (because of the 74HC1G04 inverter)
void L298::brake(char moto)
{
  if (moto == 'A')
  {
#ifdef DEBUG_MOTORS
    Serial.print("Braking Motor A");
    Serial.println(speed);
#endif
    setSpeed(moto, 0);
  }

  if (moto == 'B')
  {
#ifdef DEBUG_MOTORS
    Serial.print("Braking Motor B");
    Serial.println(speed);
#endif
    setSpeed(moto, 0);
  }
}

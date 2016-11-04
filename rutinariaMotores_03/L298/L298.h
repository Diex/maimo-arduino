// L298.h - Arduino library to control DC motos using the L298 Shield
// Copyright 2012 Jeroen Doggen (jeroendoggen@gmail.com)

#ifndef L298_h
#define L298_h



class L298
{
public:
    L298();                                   // Constructor
    ~L298();                                  // Destructor

    void begin();
    void beginMotoA(int pinA1, int pinA2, int pwmPin);
    void beginMotoB(int pinB1, int pinB2, int pwmPin);

    void setSpeed(char moto, int speed);          // Set the speed of a selected motor, range: -100 to +100
    void slowChange(char moto, int speed);        // Fade the speed of a motor slowly to a specific value: range -100 to 100

    void stop(char moto);
    void brake(char moto);                        // Brake the motor
    void brakeAgressive(char moto);               // Brake the motor

private:
    int _motoSpeedA;
    int _motoSpeedB;
    /// OUTPUT
    int PIN_A1;
    int PIN_A2;
    int DIR_A;
    int PWM_PIN_A;

    int PIN_B1;
    int PIN_B2;
    int DIR_B;
    int PWM_PIN_B;

/// ADJUST BRAKING AND FADING SPEED
    int SLOWCHANGEDELAY;                         // higher number: slower fading: 1=no fading
    int BRAKESPEED;                              // smaller number less abrupt braking (braking reuses FADESPEED)

};
#endif

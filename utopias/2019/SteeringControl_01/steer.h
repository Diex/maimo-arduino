#include "Arduino.h"

int xv = 0;
int yv = 0;

int m1 = 0;
int m2 = 0;
int m3 = 0;
int m4 = 0;
int rwheel = 0;
int lwheel = 0;

int slow = 200;
int med = 300;
int full = 1000;

// PWM en mega del 0 al 13, 44, 45 y 46
// Motor A
const int motorPin1 = 11; 
const int motorPin2 = 10; 


// Motor B
const int motorPin3 = 9; 
const int motorPin4 = 3; 



void steerSetup()
{
	// Set pins as outputs
	pinMode(motorPin1, OUTPUT);
	pinMode(motorPin2, OUTPUT);
	pinMode(motorPin3, OUTPUT);
	pinMode(motorPin4, OUTPUT);
	delay(1000); // dice el manual sobre usar analog como input.
	
}

void motors(int m1, int m2)
{
	lwheel = m1; // (-yv + xv);
	rwheel = m2; // (-yv - xv);
}



// ----------------------------------------


void run()
{
	m1 = map(lwheel, -1000, 1000, 0, 255);
	m2 = map(lwheel, -1000, 1000, 255, 0);
	
	m3 = map(rwheel, -1000, 1000, 255, 0);
	m4 = map(rwheel, -1000, 1000, 0, 255);
	
	analogWrite(motorPin1, m1);
	analogWrite(motorPin2, m2);
	
	analogWrite(motorPin3, m3);
	analogWrite(motorPin4, m4);
}


void testSequence3(){

	motors(1000, 1000);
	run();
	delay(1000);

	motors(-1000, -1000);
	run();
	delay(1000);

	return;

	motors(1000, -1000); // Derecha
	run();
	delay(1000);

	motors(-1000, 1000); // izquierda
	run();
	delay(2000);

	motors(1000, -1000);
	run();
	delay(1000);



	motors(500, -500);
	run();
	delay(1000);

	motors(-500, 500);
	run();
	delay(2000);

	motors(500, -500);
	run();
	delay(1000);

	motors(250, -250);
	run();
	delay(1000);

	motors(-250, 250);
	run();
	delay(2000);

	motors(250, -250);
	run();
	delay(1000);


	motors(250, 250);
	run();
	delay(2000);

	motors(-250, -250);
	run();
	delay(2000);

	motors(0,0);
	run();


}



void testSequence()
{
	// Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
	// This code  will turn Motor A clockwise for 2 sec.
	analogWrite(motorPin1, 180);
	analogWrite(motorPin2, 0);
	analogWrite(motorPin3, 180);
	analogWrite(motorPin4, 0);
	delay(5000);
	// This code will turn Motor A counter-clockwise for 2 sec.
	analogWrite(motorPin1, 0);
	analogWrite(motorPin2, 180);
	analogWrite(motorPin3, 0);
	analogWrite(motorPin4, 180);
	delay(5000);
	// This code will turn Motor B clockwise for 2 sec.
	analogWrite(motorPin1, 0);
	analogWrite(motorPin2, 180);
	analogWrite(motorPin3, 180);
	analogWrite(motorPin4, 0);
	delay(1000);
	// This code will turn Motor B counter-clockwise for 2 sec.
	analogWrite(motorPin1, 180);
	analogWrite(motorPin2, 0);
	analogWrite(motorPin3, 0);
	analogWrite(motorPin4, 180);
	delay(1000);
	// And this code will stop motors
	analogWrite(motorPin1, 0);
	analogWrite(motorPin2, 0);
	analogWrite(motorPin3, 0);
	analogWrite(motorPin4, 0);
}

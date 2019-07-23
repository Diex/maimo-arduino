#include "Arduino.h"



// Differential Steering Joystick Algorithm
// ========================================
//   by Calvin Hass
//   https://www.impulseadventure.com/elec/
//
// Converts a single dual-axis joystick into a differential
// drive motor control, with support for both drive, turn
// and pivot operations.
//

// https://www.impulseadventure.com/elec/robot-differential-steering.html
// https://www.mathworks.com/help/supportpkg/arduino/examples/arduino-robot-line-follower-application.html
// PWM en mega del 0 al 13, 44, 45 y 46
// Motor A
const int motorPin1 = 11; 
const int motorPin2 = 10; 


// Motor B
const int motorPin3 = 9; 
const int motorPin4 = 3; 



// INPUTS
int xv = 0; // x -1000/1000
int yv = 0; // y -1000/1000

int m1 = 0;
int m2 = 0;
int m3 = 0;
int m4 = 0;


// OUTPUTS
int     nMotMixL;           // Motor (left)  mixed output           (-128..+127)
int     nMotMixR;           // Motor (right) mixed output           (-128..+127)

int rwheel = 0;
int lwheel = 0;




// CONFIG
// - fPivYLimt  : The threshold at which the pivot action starts
//                This threshold is measured in units on the Y-axis
//                away from the X-axis (Y=0). A greater value will assign
//                more of the joystick's range to pivot actions.
//                Allowable range: (0..+127)
float fPivYLimit = 800.0;
			
// TEMP VARIABLES
float   nMotPremixL;    // Motor (left)  premixed output        (-128..+127)
float   nMotPremixR;    // Motor (right) premixed output        (-128..+127)
float     nPivSpeed;      // Pivot Speed                          (-128..+127)
float   fPivScale;      // Balance scale b/w drive and pivot    (   0..1   )


void steerSetup()
{
	// Set pins as outputs
	pinMode(motorPin1, OUTPUT);
	pinMode(motorPin2, OUTPUT);
	pinMode(motorPin3, OUTPUT);
	pinMode(motorPin4, OUTPUT);
	
}

void motors(int m1, int m2)
{
	lwheel = m1; 
	rwheel = m2; 
}


void drive(float yv, float xv){

yv = -yv;
xv = -xv;
	// Calculate Drive Turn output due to Joystick X input
if (yv >= 0) {
  // Forward
  nMotPremixL = (xv >= 0) ? 1000.0 : (1000.0 + xv);
  nMotPremixR = (xv >= 0) ? (1000.0 - xv) : 1000.0;
} else {
  // Reverse
  nMotPremixL = (xv >= 0) ? (1000.0 - xv) : 1000.0;
  nMotPremixR = (xv >= 0) ? 1000.0 : (1000.0 + xv);
}

// Scale Drive output due to Joystick Y input (throttle)
nMotPremixL = nMotPremixL * yv / 1000.0;
nMotPremixR = nMotPremixR * yv / 1000.0;

// Now calculate pivot amount
// - Strength of pivot (nPivSpeed) based on Joystick X input
// - Blending of pivot vs drive (fPivScale) based on Joystick Y input
nPivSpeed = xv;
fPivScale = (abs(xv) > fPivYLimit) ? 0.0 : (1.0 - abs(yv) / fPivYLimit);

// Calculate final mix of Drive and Pivot
nMotMixL = (1.0-fPivScale) * nMotPremixL + fPivScale*( nPivSpeed);
nMotMixR = (1.0-fPivScale) * nMotPremixR + fPivScale*(-nPivSpeed);

motors(nMotPremixL, nMotPremixR);

}


void run()
{
	m1 = map(lwheel, -1000, 1000, 255, 0);
	m2 = map(lwheel, -1000, 1000, 0, 255);
	
	m3 = map(rwheel, -1000, 1000, 0, 255);
	m4 = map(rwheel, -1000, 1000, 255, 0);
	
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

	motors(0,0);
	run();


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

	

}



void testSequence()
{
	drive(750, 0);
	run();
	delay(1000);

	drive(0, 0);
	run();
	delay(500);



	drive(750, 1000);
	run();
	delay(1000);

	drive(0, 0);
	run();
	delay(500);


	drive(750, -1000);
	run();
	delay(1000);

	drive(0, 0);
	run();
	delay(500);


	drive(-750, 1000);
	run();
	delay(1000);

	drive(0, 0);
	run();
	delay(500);


	drive(-750, -1000);
	run();
	delay(1000);

	drive(0, 0);
	run();
	delay(500);

	return;

	drive(-400, 0);
	run();
	delay(1000);

	drive(-750, 0);
	run();
	delay(1000);

	drive(-1000, 0);
	run();
	delay(1000);


	drive(0, 0);
	run();
	delay(500);



	drive(1000, 1000);
	run();
	delay(1000);

	drive(0, 0);
	run();
	delay(500);


	
	drive(-1000, 1000);
	run();
	delay(1000);


	drive(0, 0);
	run();
	delay(500);



	drive(1000, -1000);
	run();
	delay(1000);

	drive(0, 0);
	run();
	delay(500);


	drive(-1000, -1000);
	run();
	delay(1000);

	drive(0, 0);
	run();
	delay(500);




	drive(0, 0);
	run();
	delay(1000);






}

#include <L298.h>

#define DEBUG_MOTORS 1

// Motor 1
int driver1A1 = 26;
int driver1A2 = 28;
int driver1AS = 6; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int driver1B1 = 22;
int driver1B2 = 24;
int driver1BS = 7; // Needs to be a PWM pin to be able to control motor speed


// Motor 3
int driver2A1 = 27;
int driver2A2 = 29;
int driver2AS = 4; // Needs to be a PWM pin to be able to control motor speed

// Motor 4
int driver2B1 = 23;
int driver2B2 = 25;
int driver2BS = 5; // Needs to be a PWM pin to be able to control motor speed

// Motor 5
int driver3A1 = 34;
int driver3A2 = 36;
int driver3AS = 2; // Needs to be a PWM pin to be able to control motor speed

// Motor 6
int driver3B1 = 30;
int driver3B2 = 32;
int driver3BS = 3; // Needs to be a PWM pin to be able to control motor speed


L298 driverA;
L298 driverB;
L298 driverC;

L298 * drivers[] = {&driverA, &driverB, &driverC};

void setup() {  // Setup runs once per reset
  // initialize serial communication @ 9600 baud:
  Serial.begin(115200);
  driverA.beginMotoA(driver1A1, driver1A2, driver1AS);
  driverA.beginMotoB(driver1B1, driver1B2, driver1BS);

  driverB.beginMotoA(driver2A1, driver2A2, driver2AS);
  driverB.beginMotoB(driver2B1, driver2B2, driver2BS);

  driverC.beginMotoA(driver3A1, driver3A2, driver3AS);
  driverC.beginMotoB(driver3B1, driver3B2, driver3BS);

  autoTest();
}



void loop() {
  
}

void autoTest(){

for (int i = 0; i < 3; i ++) {
    Serial.print("test driver: ");
    Serial.print(i);
    Serial.println('A');
    testDriver(drivers[i], 'A');
    Serial.print("test driver: ");
    Serial.print(i);
    Serial.println('B');
    testDriver(drivers[i], 'B');
  }
}

void testDriver(L298 * driver, char motor) {
  driver->setSpeed(motor, 100);
  delay(1E3);
  driver->setSpeed(motor, -100);
  delay(1E3);
  driver->brake(motor);
  delay(1E3);
}

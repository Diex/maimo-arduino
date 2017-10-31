#include "Arduino.h"


// los sensores estan definidos viendo al robot desde arriba
// L1 L2 -- -- R2 R1
const int CNY_R1 = A4;
const int CNY_R2 = A5;
const int CNY_L2 = A6;
const int CNY_L1 = A7;

int sensors[] = {CNY_R1, CNY_R2, CNY_L2, CNY_L1};
int blackValue[sizeof(sensors)/sizeof(int)];
int sensorsValue[sizeof(sensors)/sizeof(int)];
byte status = 0;
int treshold = 32;

void calibrateSensors(){
	delay(100);
	for(int i = 0; i < sizeof(sensors)/sizeof(int); i++) {
		blackValue[i] = analogRead(sensors[i]);
		delay(10);
	}
}

void lineFollowerSetup()
{
	for(int i = 0; i < sizeof(sensors)/sizeof(int); i++) pinMode(sensors[i], INPUT);
	calibrateSensors();
}

void readSensors()
{
	for(int i = 0; i < sizeof(sensors)/sizeof(int); i++) {
		sensorsValue[i] = analogRead(sensors[i]);		
		// Serial.print(sensorsValue[i]);
		// Serial.print(':');
		delay(10);
	}	
	// Serial.println();

}

void updateSensors(){
	status = 0;
	Serial.print('R');
	for(int i = 0; i < sizeof(sensors)/sizeof(int); i++){
		byte value = sensorsValue[i] > (blackValue[i] * 2) ? 1 : 0; // 0 estoy en la linea, 1 me sali		
		status |= value << i;
		Serial.print(value & B00000001);
	}	
	Serial.print('L');
	Serial.println();
	
}


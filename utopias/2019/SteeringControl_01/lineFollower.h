#include "Arduino.h"

// SENSORES SEGUIDOR DE LINEA 
// los sensores estan definidos viendo al robot desde arriba
// L1 L2 -- -- R2 R1
const int CNY_L1 = 8;  // S1 en el sensor nuevo
const int CNY_L2 = 7;	// S2
const int CNY_CE = 6;  
const int CNY_R2 = 5;
const int CNY_R1 = 4;

int sensors[] = {CNY_L1, CNY_L2, CNY_CE, CNY_R2, CNY_R1};
int blackValue[sizeof(sensors)/sizeof(int)];
int sensorsValue[sizeof(sensors)/sizeof(int)];
byte status = 0;

void lineFollowerSetup()
{
	for(int i = 0; i < sizeof(sensors)/sizeof(int); i++) pinMode(sensors[i], INPUT);
}

void updateSensors(){
	status = 0;
	for(int i = 0; i < sizeof(sensors)/sizeof(int); i++){
		byte value = sensorsValue[i] > 0 ? 1 : 0; // 0 estoy en la linea, 1 me sali		
		status |= value << i;
	}
}



void readSensors()
{
	for(int i = 0; i < sizeof(sensors)/sizeof(int); i++) {
		sensorsValue[i] = digitalRead(sensors[i]); // ease(digitalRead(sensors[i]), sensorsValue[i], factor);		
		Serial.print(sensorsValue[i]);
		Serial.print("\t");
	}	

	Serial.println();
	
}





#include "Button.h"
#define u_int unsigned int
#define ON 0
#define OFF 1

#ifndef DEBUG
#define DEBUG 1
#endif

// leds
u_int leds[] = {3, 5, 6, 9, 10, 11};
u_int ledsStatus[] = {ON, ON, ON, ON, ON, ON};

// botones
u_int address[] = {PORTD2, PORTD4, PORTD7};
u_int input = 8;
u_int buttonsStatus[] = {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF};
boolean buttonStatusChanged = false;
long lastScan = 0;

// usando un 4051 conectado a esos pines.
//  A  B C
// B76543210
int masks [] = {
	B00000000,
	B10000000,
	B00010000,
	B10010000,
	B00000100,
	B10000100,
	B00010100,
	B10010100
};


long intime = 0;
long now = 0;
long framePeriod = 2E4; // 20 ms



void setupLeds() {
	u_int size = sizeof(leds) / sizeof(u_int);
	for (u_int led = 0; led < size; led ++) {
		pinMode(leds[led], OUTPUT);
		digitalWrite(leds[led], ledsStatus[led]);
	}
};

void setupButtons() {
	u_int size = sizeof(address) / sizeof(u_int);
	for (u_int i = 0; i < size ; i++) {
		pinMode(address[i], OUTPUT);
		digitalWrite(address[i], LOW);
	}

	pinMode(input, INPUT_PULLUP);
}

void setup() {

	setupLeds();
	setupButtons();
	Serial.begin(9600);




};


void loop() {
	intime = micros();
	scanButtons(10);
	if(buttonStatusChanged) {
		parseButtons();
		printStatus();
		buttonStatusChanged = false;
	}
	renderLeds();

	now = micros();
	delayMicroseconds(framePeriod - (now - intime));
};

void scanButtons(u_int debounceInterval) {
	
	buttonStatusChanged = false;
	u_int currentState[8];

	for (int i = 0; i < 8 ; i++) {
		selectButton(i);
		currentState[i] = digitalRead(input);
	}

	delay(debounceInterval);

	for (int i = 0; i < 8 ; i++) {
		selectButton(i);
		if (currentState[i] == digitalRead(input)) { // debounceado
			// el estado del buton esta invertido
			if (buttonsStatus[i] != digitalRead(input)) {
				buttonStatusChanged = true;
			}

			buttonsStatus[i] = digitalRead(input);  
		}
	}

}

void selectButton(u_int i) {
	 PORTD = PORTD & B01101011;  // dejo los leds como estan y add = 0;
	 PORTD = PORTD | masks[i];
}

void parseButtons() {
	for (int i = 0; i < sizeof(ledsStatus) / sizeof(u_int); i++) {
		ledsStatus[i] = (buttonsStatus[i + 1] == OFF) ? !ledsStatus[i] : ledsStatus[i]; // boton con logica invertida
	}
}


void renderLeds() {
	for (int i = 0; i < sizeof(leds) / sizeof(u_int); i++) {
		digitalWrite(leds[i], ledsStatus[i]);
	}
}

void printStatus() {		
		for (int i = 0; i < sizeof(buttonsStatus) / sizeof(u_int); i++) {
			Serial.print(buttonsStatus[i]);
		}
		Serial.print('\n');
}

int invert(int value) {
	return 255 - value;
}
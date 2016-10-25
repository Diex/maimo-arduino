//**************************************************************//
//  Name    : shiftOutCode, Hello World                         //
//  Author  : Carlyn Maw,Tom Igoe                               //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                            //
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;


int sensor = 5;

byte rows[] = {
	B00000001,
	B00000010,
	B00000100,
	B00001000,
	B00010000,
	B00100000,
	B01000000,
	B10000000
};


byte frame1[] = {
	B00000001,
	B00000010,
	B00000100,
	B00001000,
	B00010000,
	B00100000,
	B01000000,
	B10000000
};

byte frame2[] = {
	B10000000,
	B00000001,
	B00000010,
	B00000100,
	B00001000,
	B00010000,
	B00100000,
	B01000000	
};


byte frame3[] = {
	B01000000,	
	B10000000,
	B00000001,
	B00000010,
	B00000100,
	B00001000,
	B00010000,
	B00100000
};


byte frame4[] = {
	B00100000,
	B01000000,	
	B10000000,
	B00000001,
	B00000010,
	B00000100,
	B00001000,
	B00010000

};

byte frame5[] = {
	B00010000,
	B00100000,
	B01000000,	
	B10000000,
	B00000001,
	B00000010,
	B00000100,
	B00001000	
};

byte frame6[] = {
	B00001000,	
	B00010000,
	B00100000,
	B01000000,	
	B10000000,
	B00000001,
	B00000010,
	B00000100
};

byte frame7[] = {
	B00000100,
	B00001000,	
	B00010000,
	B00100000,
	B01000000,	
	B10000000,
	B00000001,
	B00000010
};


byte frame8[] = {
	B00000010,
	B00000100,
	B00001000,	
	B00010000,
	B00100000,
	B01000000,	
	B10000000,
	B00000001
};
byte* cols[] = {
	frame1,
	frame2,
	frame3,
	frame4,
	frame5,
	frame6,
	frame7,
	frame8
};


void setup() {
	//set pins to output because they are addressed in the main loop
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);

	pinMode(sensor, INPUT);
	attachInterrupt(0, isr, RISING);
	Serial.begin(9600);
}

int z = 0;
long delayTime = 0;
volatile double deltaTime = 1E3;
void loop() {
	
	if(millis() - delayTime > deltaTime){ //avanzo un cuadro
		 z = (z + 1) % 8;
		 delayTime = millis();
	}

	deltaTime = ease(1E3, deltaTime, 0.995);

	
	for(int j = 0; j < 8; j++){
		Serial.println(deltaTime);
		for(int i = 0; i < 8 ; i++){	// multiplexo las filas
			digitalWrite(latchPin, LOW);
			shiftOut(dataPin, clockPin, LSBFIRST, 255 - rows[i]);   // col 0-7  
			shiftOut(dataPin, clockPin, LSBFIRST,  cols[z][i]);   // row 0-7  (invertida?)			
			digitalWrite(latchPin, HIGH);			
			delayMicroseconds(400);	
		}		
	}
} 

void isr(){
	deltaTime = 10;
}

double ease(double current, double last, double factor){
	return last * factor + (1 - factor) * current;
}
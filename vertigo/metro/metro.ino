// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define NUMPIXELS 56
#define MAX_POSITION NUMPIXELS-1

#define TEMPO A0
#define DECAY A1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
byte leds[NUMPIXELS];

void setup()
{
	Serial.begin(115200);
	pixels.begin(); // This initializes the NeoPixel library.
	pixels.setBrightness(64);
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
}

int position = 0;
int decay = 10;

int frameDuration = 1;
unsigned long frameCount = 0;


unsigned long minPeriod = frameDuration * NUMPIXELS;
unsigned long lastStep = 0;
int bpm = 60;
void loop()
{
			// enterFrame();
			unsigned long frameStart = millis();						
			// beginDraw();
			// position = (frameCount * speed >> 8) % NUMPIXELS;

			// 60,000 ms (1 minute) / Tempo (BPM) = Delay Time in ms for quarter-note beats
			if(frameStart - lastStep > 60E3 / bpm / NUMPIXELS){ 
				lastStep = frameStart;
				position = pingPong(position, MAX_POSITION);
				for (int i = 0; i < NUMPIXELS; i++)
				{
					leds[i] = (i == position)? 255: leds[i]; //leds[i] - decay;
					// leds[i] = constrain(leds[i], 0, 255);
					pixels.setPixelColor(i, pixels.Color(leds[i], leds[i], leds[i])); 
				}
				applyDecay(leds, decay);
				pixels.show();	
			}
			
			decay = map(analogRead(DECAY), 0, 1024, 0, 255);
			bpm = map(analogRead(TEMPO), 0, 1024, 20, 600);
			// exitFrame();
			// basicamente desperdicio el tiempo que me sobro.
			digitalWrite(13, HIGH);
			while(millis() - frameStart < frameDuration){}
			frameCount ++;
			digitalWrite(13, LOW);
			
}

boolean up = true; 
int pingPong(int position, int maxPos)
{
	int newpos = 0;
	if(up){
		up = position+1 > maxPos ? false : true;  // el ultimo encendido...
		newpos = position+1 > maxPos ? maxPos : position+1;
	}else{
		up = position-1 < 0 ? true : false; // el primero
		newpos = position-1 < 0 ? 0 : position-1;
	}
	return newpos; 
}

void applyDecay(byte leds[], byte decay)
{
	for(int i=0; i<NUMPIXELS; i++){
		leds[i] = constrain(leds[i] - decay, 0, 255);
	}
}

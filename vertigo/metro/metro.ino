// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define NUMPIXELS 58
#define MAX_POSITION NUMPIXELS-1

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

int frameDuration = 5;
unsigned long frameCount = 0;
byte speed = 255;
void loop()
{
			// enterFrame();
			unsigned long frameStart = millis();						
			// beginDraw();
			position = (frameCount * speed >> 8) % NUMPIXELS;
			for (int i = 0; i < NUMPIXELS; i++)
			{
				leds[i] = (i == position)? 255: 0; //leds[i] - decay;
				leds[i] = constrain(leds[i], 0, 255);
				pixels.setPixelColor(i, pixels.Color(leds[i], leds[i], leds[i])); 
			}
			pixels.show();

			// exitFrame();
			// basicamente desperdicio el tiempo que me sobro.
			digitalWrite(13, HIGH);
			while(millis() - frameStart < frameDuration){}
			frameCount ++;
			digitalWrite(13, LOW);
			
}


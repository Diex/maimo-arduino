#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 352 

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 6
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
	Serial.begin(115200);
	Serial.println("resetting");
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(84);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }
#define DECAY A1
int maxPos = 0;
int position = 0;
boolean up = true;
int pingPong(int position, int maxPos)
{
  int newpos = 0;
  if (up) {
    up = position + 1 > maxPos ? false : true; // el ultimo encendido...
    newpos = position + 1 > maxPos ? maxPos : position + 1;
  } else {
    up = position - 1 < 0 ? true : false; // el primero
    newpos = position - 1 < 0 ? 0 : position - 1;
  }
  return newpos;
}


void loop() { 
  long time = micros();
     maxPos = map(constrain(analogRead(DECAY), 0, 1024), 0, 1024, 0, 352);
  position = pingPong(position, maxPos); // muevo el cursor.
//  pixels.clear();
  for (int i = 0; i < maxPos; i++)
  {
    leds[i] = (i == position) ? CRGB(255,255,255) : CRGB(0,0,0); //leds[i];
//    pixels.setPixelColor(i, pixels.Color(leds[i], leds[i], leds[i]));
  }
//  pixels.show();
FastLED.show();
Serial.println(micros() - time);
  return;

  
	static uint8_t hue = 0;
	Serial.print("x");
	// First slide the led in one direction
	for(int i = 0; i < NUM_LEDS; i++) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}
	Serial.print("x");

	// Now go in the other direction.  
	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}
}

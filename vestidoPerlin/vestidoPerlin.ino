#include "Perlin.h"

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      26
unsigned char maxBrightness = 255;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



uint8_t buffer[NUMPIXELS];
static double i = 0;
double pv;
int delayval = 150; // delay for half a second


void setup() {
  Serial.begin(9600);

  pixels.begin(); // This initializes the NeoPixel library.

}



void loop()
{


  i += 0.01;

  for (int y = 0; y < NUMPIXELS; y++) {
    pv = pnoise(0, (double) y , i);
    int value = (int) (pv * 1000);
    int id = (int) map(value, -1000, 1000, 0, 255);
    buffer[y] = lut[id];
  }
  
  pixels.clear();  
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, buffer[i], buffer[i], buffer[i], 127); // Moderately bright green color. //   
    Serial.print(buffer[i]);
    Serial.print(':');
  }
  Serial.println();
  
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).

}







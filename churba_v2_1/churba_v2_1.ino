// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6
#define PIN2           5
#define PIN3           7
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      15

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need toa change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel belt = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel other = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  belt.begin();
  other.begin();
}

int pixelOn = 0;
int maxInt = 64;
float offset = TWO_PI / NUMPIXELS;


void loop() {
  long t = millis() / 2;
  int c;
  for(int i=0;i<NUMPIXELS;i++){
    float val = sin(0.002f * t + (i * offset));
    c = maxInt + val * maxInt;
    pixels.setPixelColor(i, pixels.Color(c,c,c)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.

  
  for(int i=0;i<NUMPIXELS;i++){
    float val = sin(0.003f * t + (i * offset));
    c = maxInt + val * maxInt;     
    belt.setPixelColor(i, pixels.Color(c,c,c)); // Moderately bright green color.
    if (i ==  pixelOn) belt.setPixelColor(i, pixels.Color(maxInt * 4, maxInt * 4, maxInt * 4)); // Moderately bright green color.
  }

  belt.show();
  

   for(int i=0;i<NUMPIXELS;i++){
    float val = sin(0.0025f * t + (i * offset));
    c = maxInt + val * maxInt;     
    other.setPixelColor(i, pixels.Color(c,c,c)); // Moderately bright green color.
    if (i ==  pixelOn) other.setPixelColor(i, pixels.Color(maxInt * 4, maxInt * 4, 0)); // Moderately bright green color.
  }

  other.show();
  

  pixelOn = (pixelOn + 1) % NUMPIXELS;

}

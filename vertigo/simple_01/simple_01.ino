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
#define NUMPIXELS      353

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second
byte leds[NUMPIXELS];

#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // Onboard LED

int maximumRange = 200; // Maximum range needed 175 es sin nadie
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance



void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)

  Serial.begin(115200);

}

int offset = 0;
int current = 0;
float speed = 0.01;

#define MULT 4096
int decay = 5;

#define RUNNING 1
#define IDLE 2

int state = RUNNING;
int limit = 175;
boolean isPeople = false;

void loop() {
  sensor();

  if (distance < limit) {
    state = RUNNING;
  } else {
    state = IDLE;
  }

  switch (state) {

    case RUNNING:
      // speed control
      speed = sin(millis() * 0.005) * 0.0005;
//      Serial.println(speed);
      // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
      current = map(sin(millis() * speed) * MULT, -MULT, MULT, 0, NUMPIXELS);
      offset++;
      current = (current + offset) % NUMPIXELS;

      for (int i = 0; i < NUMPIXELS; i++) {
        int value = (i == current) ? 255 : leds[i] - decay;
        leds[i] = constrain(value, 0, 255);
        pixels.setPixelColor(i, pixels.Color(leds[i], leds[i], leds[i])); // Moderately bright green color.
      }
      pixels.show(); // This sends the updated pixel color to the hardware.


      break;

    case IDLE:
      for (int i = 0; i < NUMPIXELS; i++) {
        int value = leds[i] - decay;
        leds[i] = constrain(value, 0, 255);
        pixels.setPixelColor(i, pixels.Color(leds[i], leds[i], leds[i])); // Moderately bright green color.
      }
      pixels.show(); // This sends the updated pixel color to the hardware.


      break;

  }


}

void sensor() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;
  if (distance >= maximumRange || distance <= minimumRange) {
    /* Send a negative number to computer and Turn LED ON
      to indicate "out of range" */
    Serial.println("-1");
    digitalWrite(LEDPin, HIGH);
  }
  else {
    /* Send the distance to the computer using Serial protocol, and
      turn LED OFF to indicate successful reading. */
    Serial.println(distance);
    digitalWrite(LEDPin, LOW);
  }
}



#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define BUZZER 12
#define PIN    6
#define NUMPIXELS      8

int frameRate = 20;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER, OUTPUT);
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(115200);
}

unsigned long pFrameTime = 0;        // 
void loop() {
  unsigned long currentTime = millis();
  if((currentTime - pFrameTime) >= frameRate){
    pFrameTime = currentTime;
    playKit();  
  }

  playSound();
  
}


int ledsbuffer[NUMPIXELS];
unsigned long pLedUpdate = 0;        // will store last time LED was updated
unsigned int currentLed = 0;
int delayVal = 120;
int dir = 1;

void playKit() {

    
  if ((millis() - pLedUpdate) >= delayVal) {
    pLedUpdate = millis();
    currentLed = (currentLed + dir);
    dir = currentLed > 0 & currentLed < (NUMPIXELS - 1) ? dir : dir * -1;  // ida y vuelta
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    if (i == currentLed) {
      ledsbuffer[i] = 120;
    } else {
      Serial.println(ledsbuffer[i]);
      ledsbuffer[i] = constrain(ledsbuffer[i] - 10, 0, 255);;

    }
    pixels.setPixelColor(i, pixels.Color(ledsbuffer[i], ledsbuffer[i], ledsbuffer[i])); // Moderately bright green color.

  }
  pixels.show(); // This sends the updated pixel color to the hardware.



}



unsigned long previousOn = 0;        // will store last time LED was updated
unsigned long onInterval = 1000;
unsigned long previousOff = 0;
unsigned long offInterval = 1000;

void playSound() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousOn >= onInterval) {
    onInterval = random(100);
    previousOn = currentMillis;
    tone(BUZZER, random(1000, 4000));
  }

  if (currentMillis - previousOff >= offInterval) {
    offInterval = 20 + random(1500);
    previousOff = currentMillis;
    tone(BUZZER, random(1000, 4000));
  }

}



// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define NUMPIXELS 352     // ya los medí y hay esa cantidad
#define LAST_LED NUMPIXELS-1

#define TEMPO_CTRL A0
#define DECAY_CTRL A1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
byte white[NUMPIXELS];


int decay = 10;

unsigned long frameCount = 0;
unsigned long lastStep = 0;
int bpm = 60;


int frameStepTime = 1; // ms
#define MIN_SPEED 10;
#define MAX_SPEED 10E3  // 10000
// hay un cabezal "playhead" que se mueve
// todas las animaciones en el circulo se generan "moviendo" este playhead
int playhead = 0; 
// un contador que uso para llevar la cuenta de cuando tengo que avanzar el playhead
unsigned long step;
// cuanto incremento en cada draw();
unsigned long speed = MAX_SPEED;


void setup()
{
  Serial.begin(115200);
  pixels.begin();
  pixels.setBrightness(64);  // ATENCION !
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}


void loop()
{
  unsigned long frameStart = millis();						// tiempo al inciar el frame
  draw();
  // terminé de hacer lo que tenía que hacer
  // me quedo desperdiciando el tiempo que me sobro
  // esto me regula un "frameRate" siempre y cuando el tiempo de draw se menor que frameStepTime
  digitalWrite(13, HIGH);
  while (millis() - frameStart < frameStepTime) {}
  digitalWrite(13, LOW);
  // el led13 destella "mostrandome" cuanto tiempo me sobro.
}



void draw()
{
    float d = (sin(millis() * 0.005) + 1) / 2 ; //map(* MAX_SPEED, 0, MAX_SPEED, MAX_SPEED/2, MAX_SPEED);
    unsigned long s = map(d * 10E3, 0, 10E3, MIN_SPEED, MAX_SPEED);
    Serial.println(s);
    forward(playhead, step, s);
//  fastest(playhead);

}
void forward(int &playhead, unsigned long &step, unsigned long speed)
{ 
  step += speed;
  playhead = step > 10E3 ? (playhead + 1) % NUMPIXELS : playhead;  
  step = step > 10E3 ? 0 : step;
  pixels.clear();
  white[playhead] = 255;
  pixels.setPixelColor(playhead, pixels.Color(white[playhead], white[playhead], white[playhead]));  
  pixels.show();
}

void fastest(int &playhead)
{ 
  playhead = (playhead + 1) % NUMPIXELS;  
  pixels.clear();
  white[playhead] = 255;
  pixels.setPixelColor(playhead, pixels.Color(white[playhead], white[playhead], white[playhead]));  
  pixels.show();
}

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

void applyDecay(byte leds[], byte decay)
{
  for (int i = 0; i < NUMPIXELS; i++) {
    leds[i] = constrain(leds[i] - decay, 0, 255);
  }
}

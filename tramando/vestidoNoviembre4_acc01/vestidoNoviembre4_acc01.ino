#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);



/*
  top son las tiras que van adelante arriba
  bot son las que van abajo, atras y adelante.
  como estan unidas en la cintura, las de arriba estan en orden invertido.
*/

#define BOT_PIN 6
#define TOP_PIN 5
#define BOT_NUM_LEDS 21   // uno tiene 19 bullshit
#define TOP_NUM_LEDS 14   // uno tiene 13 bullshit



// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel top = Adafruit_NeoPixel(TOP_NUM_LEDS, TOP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bottom = Adafruit_NeoPixel(BOT_NUM_LEDS, BOT_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  initSensor();
  top.begin();
  top.show(); // Initialize all pixels to 'off'

  bottom.begin();
  bottom.show(); // Initialize all pixels to 'off'
  
  runTest();
  runTest();
  runTest();
}

float prevY = 0;

void loop() {

  /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);

  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.println("m/s^2 ");
  
  float delta = prevY - event.acceleration.y;
  prevY = event.acceleration.y;
  Serial.print("delta: ");  Serial.println(delta);
  delay(20);
  
  if(delta > 2.0){
    playAnimation(15);
  }
  
  
}

void initSensor(){
  #ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");

  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }

  /* Display some basic information on this sensor */
  displaySensorDetails();
}
void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}


void playAnimation(int clock){

  int val = 255;
  int decay = 7;

  
  for (int i = TOP_NUM_LEDS ; i >= -1; i --) {
    top.clear();
    for (int a = 0; a < decay; a++) {
      top.setPixelColor(i - a, val / a, val / a, val / a);
    }
    top.show();
     delay(clock);
   }

  for (int i = 0 ; i < BOT_NUM_LEDS; i ++) {
    bottom.clear();
    for (int a = 0; a < decay; a++) {
      bottom.setPixelColor(i + a, val / a, val / a, val / a);
    }
    bottom.show();
    delay(clock);
  }

}

void runTest(){
  int val = 255;
  for (int i = TOP_NUM_LEDS ; i >= -1; i --) {
    top.clear();
    for (int a = 0; a < 5; a++) {
      top.setPixelColor(i - a, val / a, val / a, val / a);
    }
    top.show();
    delay(10);
  }

  for (int i = 0 ; i < BOT_NUM_LEDS; i ++) {
    bottom.clear();
    for (int a = 0; a < 5; a++) {
      bottom.setPixelColor(i + a, val / a, val / a, val / a);
    }
    bottom.show();
    delay(10);
  }
}


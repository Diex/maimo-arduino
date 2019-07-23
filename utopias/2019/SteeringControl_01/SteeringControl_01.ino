#include "steer.h"
#include "lineFollower.h"
// estados de control general del robot
#define GO 1 // el robot avanza - usa el lineFollower
#define NO_GO 2
#define WANDERING 4
#define LOOKING_FOR_MUM 8
#define BREEDING 16
// YWROBOT
// Compatible with the Arduino IDE 1.0
// Library version:1.1
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
int action = GO;
static const char * TAG = "infante";
void setup()
{
  Serial.begin(115200);
  Serial.println("Booting");
  lcd.init(); // initialize the lcd
  // lcd.noBacklight();
  lcd.backlight();

  lineFollowerSetup();
  steerSetup();
  // testSequence3();
  // testSequence();

}

byte prevStatus = 0;


int max = 500;
int med = 400;
int min = 300;

int delayed = 0;
int lastTime = 0;


void loop()
{
  readSensors();
  updateSensors();

  robotWalk();

  if (status == prevStatus) return;
  prevStatus = status;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("");
  lcd.print(String(status, BIN));

  lcd.setCursor(0, 1);
  lcd.print("");
  // lcd.print(avg);


}

void robotWalk()
{
  walkTheLine(status);
}

boolean pathFinding = false;

void walkTheLine(byte status) {

  if(pathFinding){
    if(status != B00000000 && status != B00011111){
      pathFinding = false;
    }
    return;
  }


  switch (status) {
  case B00010000: // -1
    drive(med, 500);
    run();
    break;

  case B00011000: // -10
    drive(med, 600);
    run();
    break;

  case B00011100: // -100
    drive(med, 800);
    run();
    break;

  case B00011110: // -1000
    drive(med, 1000);
    run();
    break;

  case B00011111: // OUT
    // drive(0, 0);
    pathFinding = true;
    intersection();
    run();
    break;

  case B00001111: // 1000
    drive(med, -1000);
    run();
    break;

  case B00000111: // 100
    drive(med, -800);
    run();
    break;

  case B00000011: // 10
    drive(med, -600);
    run();
    break;

  case B00000001: // 1
    drive(med, -500);
    run();
    break;

  case B00000000: // CROSS
    pathFinding = true;
    intersection();
    break;

  }
}


float ease(float p, float c, float f) {
  return (p * f) + (c * (1 - f));
}

void intersection() {
  drive(0,0);
  run();
  delay(random(5000));
  // intersecion
  drive(max, (random(1000) < 500 ) ? -1000 : 1000);
  run();

}

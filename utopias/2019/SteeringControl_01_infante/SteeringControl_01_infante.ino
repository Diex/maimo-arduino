#include "steer.h"
#include "lineFollower.h"
#include <LiquidCrystal_I2C.h>

// estados de control general del robot
#define GO 1 // el robot avanza - usa el lineFollower
#define NO_GO 2
#define WANDERING 4
#define LOOKING_FOR_MUM 8
#define BREEDING 16

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
static const char * TAG = "infante";

int state = GO;
int actionPin = 2;

void actionChage() {
  state = NO_GO;
  if (digitalRead(actionPin)) state = GO;
}


void setup()
{
  Serial.begin(115200);
  Serial.println("Booting");

  lcd.init();
  lcd.backlight();

  pinMode(actionPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(actionPin), actionChage, CHANGE);

  lineFollowerSetup();
  steerSetup();

}

int max = 500;
int med = 400;
int min = 300;

// int delayed = 0;
long lastTime = 0;
int fps = 200; // ms tiempo de refresh

char *currentStatus;
char go_str[] = "GO";
char nogo_str[] = "NOGO";
char wandering_str[] = "WANDERING";
char whoknows_str[] = "WTF ???";

void loop()
{
  readSensors();
  updateSensors();

  switch (state) {
  case GO:
    walkTheLine(status);
    currentStatus = go_str;
    break;

  case NO_GO:
    stop();
    currentStatus = nogo_str;
    break;

  case WANDERING:
    if (status != B00000000 && status != B00011111) state = GO;
    currentStatus = wandering_str;
    break;

  default:
    stop();
    currentStatus = whoknows_str;
    break;
  }

  renderLcd();

}


void renderLcd() {

  if (millis() > lastTime + fps) {
    lastTime = millis();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("");
    lcd.print(String(status, BIN));

    lcd.setCursor(0, 1);
    lcd.print("");
    lcd.print(currentStatus);

  }

}


void walkTheLine(byte status) {

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
    state = WANDERING;
    intersection(max);
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
    state = WANDERING;
    intersection(max);
    break;

  default:
    drive(max, 0);
    run();
  break;
  }
}


float ease(float p, float c, float f) {
  return (p * f) + (c * (1 - f));
}


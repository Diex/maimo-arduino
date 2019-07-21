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
  // Print a message to the LCD.
  lcd.backlight();
  lineFollowerSetup();
  steerSetup();
  testSequence3();
}

void loop()
{
  readSensors();
  lcd.setCursor(0, 0);
  lcd.print(String(status, BIN));
  updateSensors();
  robotWalk();
}

void robotWalk()
{
  walkTheLine(status);
}

void walkTheLine(byte status)
{
  byte result = ~status & B00001110;

  lcd.setCursor(0, 1);
  lcd.print(String(result, BIN));
  
  switch (result)
  {
    case B00001110:     // OUT
        motors(500,500);        
        run();
      break;
    case B00000110:     // left        
        motors(-500,500);
        run();
      break;
    case B00000010:
        
        motors(-100,100);
        run();
      break;
    case B00001000:
        motors(100,-100);
        run();
      break;
    case B00001100:
        motors(500,-500);
        run();
      break;
    case B00000000:
        motors(0,0);        
        run();
      break;
  }
}

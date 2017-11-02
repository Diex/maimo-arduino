// include the library code:
#include <LiquidCrystal.h>
#include <Arduino.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(11, 12, 14, 15, 16, 17);

void lcdSetup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void lcdPrintStatus(byte status) {  
  lcd.clear();
  lcd.setCursor(0, 0);  
  
  if(status == B00000000) lcd.print("----");  

  if(status == B00000001) lcd.print("---x");  
  if(status == B00000010) lcd.print("--x-");  
  if(status == B00000011) lcd.print("--xx");  
  if(status == B00000100) lcd.print("-x--");  

  if(status == B00000101) lcd.print("-x-x");  
  if(status == B00000110) lcd.print("-xx-");  
  if(status == B00000111) lcd.print("-xxx");  
  if(status == B00001000) lcd.print("x---");  

  if(status == B00001001) lcd.print("x--x");  
  if(status == B00001010) lcd.print("x-x-");  
  if(status == B00001011) lcd.print("x-xx");  
  if(status == B00001100) lcd.print("xx--");  

  if(status == B00001101) lcd.print("xx-x");  
  if(status == B00001110) lcd.print("xxx-");  
  if(status == B00001111) lcd.print("xxxx");  
  

  // char * b;

  // for(int i =0 ; i < 8 ; i++)
  // {
  //     b[i] = 48 + (status & (B10000000 >> i));
  // }
     
}

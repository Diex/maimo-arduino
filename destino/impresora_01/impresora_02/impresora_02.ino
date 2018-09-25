#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#define IDLE 0
#define PRINTING 1
#define DONE 2
#include <locale.h>

#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

int state = IDLE;

int ledPin = 3;    // LED connected to digital pin 9
int button = 2;


// https://www.unicode.org/Public/MAPPINGS/VENDORS/MICSFT/PC/CP437.TXT
// http://www.kostis.net/charsets/cp437.htm
// https://www.ascii-codes.com/
// http://www.acc.umu.se/~saasha/charsets/?charset=cp437&charset=cp1252

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(115200);

  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)
  printer.upsideDownOff();
  printer.justify('C');

  printer.setCharset(CHARSET_LATINAMERICA);
  printer.setCodePage(CODEPAGE_ISO_8859_15);

//  return;
  //  printer.upsideDownOn();
//  printer.write(27);
//  printer.write(123);
//  printer.write(1);

 
}


void loop() {
  buttonLight();
//  char * todos = "ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜ¢£¥₧ƒáíóúñÑªº¿⌐¬½¼¡«»░▒▓│┤╡╢╖╕╣║╗╝╜╛┐└┴┬├─┼╞╟╚╔╩╦╠═╬╧╨╤╥╙╘╒╓╫╪┘┌█▄▌▐▀αßΓπΣσµτΦΘΩδ∞φε∩≡±≥≤⌠⌡÷≈°∙·√ⁿ²■\\0";  
//  char * vowels = "áéíóú";
  char * q_001 = "¿Para qué habría que decir algo nuevo?";
  String p = "¿Para qué habría que decir algo nuevo?";
//  char decoded [256] = {};
String pp ;
  switch (state) {
    case IDLE:
      if (!digitalRead(button)) {
        state = PRINTING;
      }
      break;
    case PRINTING:
      pp = utf8ascii(p);

      //  esto no funciona
      //        printer.print(vowels);
      //        printer.print('\n');

      // esto si. no se por qué...
      printer.println(pp);
      

      state = DONE;
      break;

    case DONE:
      delay(1000);
      state = IDLE;
      break;
  }
}


uint32_t ptime = 0;
uint16_t ftime = 30;
int16_t fvalue = 0;
int16_t finc = 5;

void buttonLight() {

  if (millis() - ptime > ftime) {
    fvalue += finc;
    if (fvalue >= 255 || fvalue < 0) {
      finc *= -1;
    }
    fvalue = constrain(fvalue, 0, 255);
    ptime = millis();
  }
  analogWrite(ledPin, fvalue);
}








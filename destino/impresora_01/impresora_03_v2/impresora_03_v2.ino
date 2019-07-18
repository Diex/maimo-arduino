#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include <limits.h>
#define IDLE 0
#define PRINTING 1
#define DONE 2
#include "questions.h"



#define TX_PIN 10 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 9 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

int state = IDLE;

int ledPin = 6;    // LED connected to digital pin 9
int gnd = 8;
int button = 7;



// https://www.unicode.org/Public/MAPPINGS/VENDORS/MICSFT/PC/CP437.TXT
// http://www.kostis.net/charsets/cp437.htm
// https://www.ascii-codes.com/
// http://www.acc.umu.se/~saasha/charsets/?charset=cp437&charset=cp1252

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(gnd, OUTPUT);
  digitalWrite(gnd, LOW);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(115200);

  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)
  printer.upsideDownOff();
  printer.justify('C');

  //https://github.com/adafruit/Adafruit-Thermal-Printer-Library/blob/master/Adafruit_Thermal.h
  printer.setCharset(CHARSET_LATINAMERICA);
  printer.setCodePage(CODEPAGE_ISO_8859_15);

  printer.setSize('M');
//  printer.upsideDownOn();
  //  printer.write(27);
  //  printer.write(123);
  //  printer.write(1);

  // random
  int val = UINT_MAX;
  for (int x = 0; x < 1000; x++) {
    val ^= analogRead(A0);
  }
//  Serial.println(val);
  randomSeed(val);
}


void loop() {
  buttonLight();

  switch (state) {
    case IDLE:
      if (!digitalRead(button)) {
        state = PRINTING;
      }
      break;
      
    case PRINTING:
      printQuestion();
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

// https://stackoverflow.com/questions/9072320/split-string-into-string-array
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "*";
}

//int cual = 0;
void printQuestion() {

  char buffer[255];    // make sure this is large enough for the largest string it must hold
  
//  String temp;
  char temp[] = "";
//  String question;
   char question[] = "";
  int cual = random(202);
  
  String w = "";
  int wid = 0;

  strcpy_P(buffer, (char*) pgm_read_word(&(string_table[cual]))); // Necessary casts and dereferencing, just copy.//cual++%10

//  question = buffer;
//  strcpy (question,buffer);
//  question = utf8ascii(question);
  strcpy (question,utf8ascii(buffer));
  
  if (random(20) < 2) {
//    translate(&question, (int) random(5));
  }


  //  esto no funciona
  //        printer.print(vowels);
  //        printer.print('\n');
  // esto si. no se por qué...

    printer.feed(2);

  // split in lines:
  // 32 caracteres por linea
  String line = "";
  while (! w.equals("*")) {
    w = getValue(question, ' ', wid);
    if (! w.equals("*") && (line.length() + w.length()) < 32) {
      line += w;
      line += ' ';
      wid++;
    } else {
//      Serial.print(cual);
//      Serial.print(' ');
//      Serial.println(line);
      
      printer.println(line);
      line = "";
    }
  }
    printer.feed(4);
    printer.println("----------------");
    printer.feed(2);
  
//  cual++;
}

unsigned char simbolos[] = {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 58, 59, 60, 61, 62, 63, 64, 91, 92, 93, 94, 95, 96};

void translate(String * translated, int kind) {
  int simbol = 0;
  String temp = String(*translated);
      
  for (int i = 1; i < translated->length() - 1; i++) { // el primer y ultimo caracter siempre con ¿?
    char c = translated->charAt(i);
      switch (kind) {
        // numeros y signos locos
        case 0:
          if(c == ' ') continue;
          simbol = random(0, sizeof(simbolos) / sizeof(char));
          translated->setCharAt(i, simbolos[simbol]);
          break;
        case 1:
          if(c == ' ') continue;
          translated->setCharAt(i, random(2) > 0 ? '.' : '-');
          break;
        case 2:
          if(c == ' ') continue;
          translated->setCharAt(i, random(2) == 0 ? '0' : '1');
          break;
        case 3:
          if(c == ' ') continue;
          translated->setCharAt(i, ' ');
          break;
         case 4:
          translated->setCharAt(i, temp.charAt(temp.length() - 1 - i));//                      
          break;
      }    
  }
}

void strcat(char* original, char appended)
{
  while (*original++)
    ;
  *original++ = appended;
  if (appended)
    *original = '\0';
}






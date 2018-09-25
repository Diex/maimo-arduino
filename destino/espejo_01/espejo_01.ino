#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"


int sharp = A0;
int closest = 100;
void setup() {
  Serial.begin(115200);
  setupMP3();
}

const int IDLE = 0;
const int PLAYING = 1;

int state = IDLE;


SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int fileCount = 0;


long lastPlay = 0;
long timeOut = 0;

boolean ppresence = false;
boolean playing = false;

void loop() {

  boolean presence = sensor(true) > 32 ? true : false;
  String data = ">> ";
  data += presence;
  data += " : ";
  data += ppresence;
  if((millis() - timeOut < 3E3)) return;
    
  if (presence ) { // hay alguien
    if (!ppresence & !playing) {
      Serial.println(data);
      Serial.println("play");
      ppresence = true;
      playing = true;
      lastPlay = millis();
      int cual = random(fileCount) + 1 ; // cuenta desde 1
      Serial.println(cual);
      delay(1000);
      myDFPlayer.play(cual);  //Play the first mp3
    }
  }else{
    if(ppresence) timeOut = millis();
    ppresence = false; // me fui
    
  }


  


  if (playing && millis() - lastPlay > 4E3) {
    Serial.println("end play");
    playing = false;
  }
}

float pvalue = 0;
float factor = 0.01;
int sensor(boolean debug) {
  float value = map(analogRead(sharp), 0, 1024, 0, closest) * 1.0;
//  (value * factor) + (pvalue * (1 - factor));
  pvalue = value * factor + (pvalue * (1 - factor));
  if (debug) {
    String data = "|";
    for (int i = 0; i < value; i++) {
      data += "|";
    }
    Serial.println(pvalue);
  }

  return pvalue;
}


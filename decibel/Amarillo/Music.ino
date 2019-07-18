#include "pitches.h"
#include "Timer.h"

// notes in the melody:



long timermusic = 0;
boolean noteOff = false;
boolean noteRunning = false;
Timer t;
long silence = -1 ;
int currentNote = 0;
int maxNote = 7;

long previousMillis = 0;
long interval = 20;
const int max = 5;
int thisNote = 0;
int maxNotes = 8;
long pauseBetweenNotes = 0;
long noteStart = 0;
boolean notePlaying = false;
long noteDuration = 0;


void resetMusic(){
  thisNote = 0;
}


void demoMusic(){ // you loose;
  int melody[] = {
 NOTE_AS4,
 NOTE_A4 ,
 NOTE_GS4,
 NOTE_G4 ,
 NOTE_FS4,
 NOTE_F4 ,
 NOTE_E4 ,
 NOTE_DS4,
 NOTE_D4 ,
 NOTE_CS4,
 NOTE_C4 ,
 NOTE_B3 ,
 NOTE_AS3,
 NOTE_A3 ,
 NOTE_GS3,
 NOTE_G3 ,
 NOTE_FS3,
 NOTE_F3 ,
 NOTE_E3 ,
 NOTE_DS3,
 NOTE_D3 ,
 NOTE_CS3,
 NOTE_C3 ,
 NOTE_B2 ,
 NOTE_AS2,
 NOTE_A2 ,
 NOTE_GS2,
 NOTE_G2 ,
 NOTE_FS2,
 NOTE_F2 ,
 NOTE_E2 ,
 NOTE_DS2,
  NOTE_D2 ,
};


// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
   4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4
};
int maxNotes = 32;

if (millis() - noteStart  < noteDuration + pauseBetweenNotes ) {
    return;
  } else {
    notePlaying = false;
  }

  if(notePlaying) return;

  // iterate over the notes of the melody:
  if (thisNote < maxNotes){
    
  
  // to calculate the note duration, take one second
  // divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  noteDuration = (125) / noteDurations[thisNote];
  tone(46, melody[thisNote], noteDuration);
  
  noteStart = millis();
  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  pauseBetweenNotes = noteDuration * 1.30;
  notePlaying = true;
  thisNote++;
  // delay(pauseBetweenNotes);
  // stop the tone playing:
} else {
  thisNote = 0;
  musicCount--;
}
}

void nbaMusic(int energy){

int level = 0;

  int curL = energy;

  for (int i = 0; i < MAX_LEVEL; i++) {

    long maxEnergyPerLevel = MAX_ENERGY / MAX_LEVEL;


    if (curL > maxEnergyPerLevel) {
    }
    else if (curL <= 0) {
    }
    else {
      level = i;
      break;

    }


    curL -= maxEnergyPerLevel;

  }


int melody[] = {
  NOTE_A3, 0, NOTE_E2, 0, NOTE_FS2, 0, NOTE_GS2, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
   4, 4, 4, 4, 4, 4, 4, 4
};
int maxNotes = 8;

if (millis() - noteStart  < noteDuration + pauseBetweenNotes ) {
    return;
  } else {
    notePlaying = false;
  }

  if(notePlaying) return;

  // iterate over the notes of the melody:
  if (thisNote < maxNotes){
    
  
  // to calculate the note duration, take one second
  // divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  noteDuration = (500 - (75 * level)) / noteDurations[thisNote];
  tone(46, melody[thisNote] + (12 * level), noteDuration);
  
  noteStart = millis();
  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  pauseBetweenNotes = noteDuration * 1.30;
  notePlaying = true;
  thisNote++;
  // delay(pauseBetweenNotes);
  // stop the tone playing:
} else {
  thisNote = 0;
  
}

}




void winMusic() {

  int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

  if (millis() - noteStart  < noteDuration + pauseBetweenNotes ) {
    return;
  } else {
    notePlaying = false;
  }

  if(notePlaying) return;

  // iterate over the notes of the melody:
  if (thisNote < maxNotes){
    
  
  // to calculate the note duration, take one second
  // divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  noteDuration = 500 / noteDurations[thisNote];
  tone(46, melody[thisNote], noteDuration);
  
  noteStart = millis();
  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  pauseBetweenNotes = noteDuration * 1.30;
  notePlaying = true;
  thisNote++;
  // delay(pauseBetweenNotes);
  // stop the tone playing:
} else {
  thisNote = 0;
  musicCount--;
}



}

void doAfter() {
  noteRunning = false;
}

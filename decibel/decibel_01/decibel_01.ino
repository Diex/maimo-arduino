
#include <avr/pgmspace.h>
#include "Piso.cpp"

Piso pisos[] = {
  Piso(2),
  Piso(3),
  Piso(5),
  Piso(6),
  Piso(7),
  Piso(8)
  };

// ----------------------------------------------------------------
// JUEGO
// ----------------------------------------------------------------

volatile boolean interrupted = false;
const int MAX_LEVEL = 6;
const int MAX_LED_LEVEL = 63;
const int MAX_INACTIVITY_SECS = 10000;


const float DEMO_LIGHTS_INC = 1.2;
const float DEMO_WIN_INC = 12;
const int STATE_WIN_NR_FLASHES = 7;

// ----------------------------------------------------------------
// LOOP
// ----------------------------------------------------------------
long frameDuration = 2E3; //µS = 2ms
long lastmicros;
long currentTime  = 0;


long lastInterruptTime = 0;



// ----------------------------------------------------------------
// ENERGIA
// ----------------------------------------------------------------
const long MAX_ENERGY = 400L;

float energy = 0;
float discharge = 0.02;

// ----------------------------------------------------------------
// ?
// ----------------------------------------------------------------

bool lightsLoading = true;
int lightsLoadedFlasesCnt = 0;

// ----------------------------------------------------------------
// ESTADOS
// ----------------------------------------------------------------
static const unsigned int STATE_DEMO =1;
static const unsigned int STATE_INIT_PLAYING = 2;
static const unsigned int STATE_PLAYING = 3;
static const unsigned int STATE_WIN = 5;

volatile unsigned int currentState = STATE_DEMO;


// ----------------------------------------------------------------
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot




void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(13, OUTPUT); //debug to led 13
  // pinMode(21, INPUT);
  //attachInterrupt(2, interruptionHandler, FALLING);
}

int musicCount = 0;

void loop() {
  
  currentTime = millis();
  checkAnalogSensor();
  
  // sensorValue = analogRead(analogInPin);        
 

  switch (currentState) {

  case STATE_DEMO:
  if(! musicCount <= 0) demoMusic();
    stateDemo();
    break;

  case STATE_INIT_PLAYING:
    initPlaying();
    break;

  case STATE_PLAYING:
    statePlaying();
    break;

  case STATE_WIN:
  if(! musicCount <= 0) winMusic();
    stateWin();
    break;

  }
  lastmicros = micros();
  delayMicroseconds(frameDuration - (micros() - lastmicros));
}


long flashesTime = 0;

void stateWin() {

  Serial.println("stateWin");

  energy += DEMO_WIN_INC;

  renderFloors();

  if (energy > MAX_ENERGY) {
    lightsLoadedFlasesCnt++;

    if (lightsLoadedFlasesCnt >= STATE_WIN_NR_FLASHES) {
      energy = MAX_ENERGY;

      if (flashesTime == 0) {
        flashesTime = currentTime;
      } else {
        if (currentTime - flashesTime > 3000) {
          Serial.println("luyces por tres segundos.....");
          Serial.print(currentTime - flashesTime);
          changeState(STATE_DEMO); 
          return;
        }      
      }

    } 
    else {
      energy = 0;
    } 
  }
}


void initPlaying() {
  energy = 0;
  currentState = STATE_PLAYING;

}

void statePlaying() { 
  checkSensor();
   nbaMusic(energy);

  // win check
  if (energy >= MAX_ENERGY)  {
    Serial.println("-------------- gane ");
    changeState(STATE_WIN);
    return;
  }

  //lose check
  if ((currentTime - lastInterruptTime) > MAX_INACTIVITY_SECS){
    Serial.println("-------------- perdi ");
    changeState(STATE_DEMO) ;
  }

  renderFloors();

  dischargeEnergy();
}

void changeState(unsigned int st) {
  lightsLoading = true;
  energy = 0;
  lightsLoadedFlasesCnt = 0;
  
  if (st != STATE_PLAYING) {
    lastInterruptTime = currentTime;
  }
  
    if(st == STATE_WIN){
    musicCount = 1;
    resetMusic();
  }
  if(currentState == STATE_PLAYING && st == STATE_DEMO){
    musicCount = 1;
    resetMusic();
  }

  currentState = st;
  flashesTime = 0;
}

void renderFloors() {
  int curL = energy;

  for (int i = 0; i < MAX_LEVEL; i++) {

    long maxEnergyPerLevel = MAX_ENERGY / MAX_LEVEL;

    int brightness = 100;

    if (curL > maxEnergyPerLevel) {
      brightness = 100;
    } 
    else if (curL <=0){
      brightness = 0;
    } 
    else {
      brightness = curL * 100.0 / maxEnergyPerLevel;
    }

    int ledBrigthnessLevel  = brightness * MAX_LED_LEVEL / 100;
    /*
    Serial.print("level ");
     Serial.print(i);
     Serial.print(" br");
     Serial.println(ledBrigthnessLevel);
     */

    pisos[i].setBrightness(ledBrigthnessLevel);
    pisos[i].render();
    curL -= maxEnergyPerLevel;

  }
}

void dischargeEnergy() {
  energy -= discharge;

  if (energy < 0) {
    energy = 0;
  }
}

void checkSensor(){
  if(interrupted){
    interrupted = false;    
    // dTime = millis() - lastInterruptTime;
    lastInterruptTime = millis();

    //delta = 1000.0/ (float) dTime;
    energy += 1.5;//(MAX_ENERGY)/MAX_LEVEL; 
  } 
}

int lastOutputValue = 0;

void checkAnalogSensor() {
  if (currentState == STATE_DEMO) {
    Serial.println("lala lalala state demo");
    sensorValue = analogRead(analogInPin);       
    int outputValue = map(sensorValue, 0, 1023, 0, 255);     
    int diff = (lastOutputValue - outputValue); 
    
    diff = diff < 0? diff *- 1: diff; 
//    if ( outputValue  > 60 && outputValue < 80) {
       if ( outputValue == 0 && diff == 0) {
       Serial.println("lala lalala empiezo a jugar playing");
      changeState(STATE_INIT_PLAYING);
    }
  } else if (currentState == STATE_PLAYING) {
      sensorValue = analogRead(analogInPin);       
      int outputValue = map(sensorValue, 0, 1023, 0, 255);  
//      if (outputValue > 60 && outputValue < 80) {
         if ( outputValue == 0) {
         Serial.println("interrupted true");
         interrupted = true;
      }
  }
  
}


float ease(float current, float prev, float factor) {
  return (current * factor) + (prev * (1 - factor));
}


void stateDemo() {
  //Serial.println("stateDemo");

  energy += DEMO_LIGHTS_INC * (lightsLoading? 1:-1);

  if (lightsLoading) {
    if (energy > MAX_ENERGY) {
      lightsLoading = false; 
    } 
  } 
  else {
    if (energy < 0) {
      lightsLoading = true; 
    } 
  }
  renderFloors();
}

// ---------------------------------------------
void interruptionHandler()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200) 
  {
    if (currentState == STATE_DEMO) {
      currentState = STATE_INIT_PLAYING;
    }

    if (currentState == STATE_PLAYING) {
      interrupted = true;
    }
  }
  last_interrupt_time = interrupt_time;
}




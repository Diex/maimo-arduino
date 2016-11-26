int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int led6 = 7;

int leds[] = {led1, led2, led3, led4, led5, led6};
int maxLeds = 6;

int mic = 18;
int smoke = 10;
int smokeBurstTime = 500;
int smokeTime = 4E3;

int cooler = 11;
long coolerStartTime = 0;
long coolerOnTime = 30E3;
boolean coolerStatus = false;

float level = 0;
float levelUp = 4;
float maxLevel = 600;


const int IDLE = 0;
const int PLAYING = 1;
const int SHOW = 2;

int state = PLAYING;

void interrupt() {
  level += levelUp;
}

void setup() {
  for (int led = 0; led < maxLeds; led++) {
    pinMode(leds[led], OUTPUT);
  }
  attachInterrupt(digitalPinToInterrupt(mic), interrupt, RISING);
  pinMode(smoke, OUTPUT);
  pinMode(cooler, OUTPUT);
  Serial.begin(115200);
}


boolean isMaxLevel = false;

void loop() {
  level = ease(0, level, 0.001);
  if (coolerStatus && millis() - coolerStartTime > coolerOnTime) {
    stopCoolers();
  }

  switch (state) {
    case PLAYING:
      showLeds(level);
      Serial.println(level);      
//      if (checkIfMaxLevel(level)) {
//        state = SHOW;
//      }
      break;

    case SHOW:
      triggerSmoke();
      delay(smokeTime);
      startCoolers(millis());
      state = PLAYING;
      break;
  }

}


void startCoolers(long now) {

  digitalWrite(cooler, LOW);
  coolerStartTime = now;
  coolerStatus = true;
}

void stopCoolers() {
  digitalWrite(cooler, HIGH);
  coolerStatus = false;
}

void triggerSmoke() {
  digitalWrite(smoke, LOW);
  delay(smokeBurstTime);
  digitalWrite(smoke, HIGH);
}



boolean checkIfMaxLevel(float level) {
  if ( level >= (maxLevel / maxLeds) * (maxLeds - 1)) {
    return true;
  } else {
    return false;
  }
}

void showLeds(float level) {
  float curL = level;
  float maxEnergyPerLevel = maxLevel / maxLeds;

  for (int i = 0; i < maxLeds; i++) {
    int brightness = 100;

    if (curL > maxEnergyPerLevel) {
      brightness = 100;
    }
    else if (curL <= 0) {
      brightness = 0;
    }
    else {
      brightness = curL * 100.0 / maxEnergyPerLevel;
    }
    curL -= maxEnergyPerLevel;

    int ledBrigthnessLevel  = map(brightness, 0, 100, 0, 255);
    /*
      Serial.print("level ");
      Serial.print(i);
      Serial.print(" br");
      Serial.println(ledBrigthnessLevel);
    */

    analogWrite(leds[i], ledBrigthnessLevel);
    //    pisos[i].setBrightness(ledBrigthnessLevel);
    //    pisos[i].render();
  }
}

float ease(float current, float prev, float factor) {
  return (current * factor) + (prev * (1 - factor));
}



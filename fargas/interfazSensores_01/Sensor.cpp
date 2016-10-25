#include <Arduino.h>

class Sensor {

  private:
    const uint8_t   OFF = 0;
    const uint8_t   ON = 1;
    uint8_t   pin;
    bool      isAnalog;
    bool      isFrecCount;
    uint8_t   state;

    uint16_t  minTh;
    uint16_t  maxTh;

    volatile uint16_t currentReading;


  public:
    Sensor(uint8_t _pin, bool _isAnalog, bool _isFrecCount) {
      pin = _pin;
      isAnalog = _isAnalog;
      isFrecCount = _isFrecCount;
      minTh = 10; // default
      if(isAnalog) minTh = 470;
      pinMode(pin, INPUT);
    };

    void setMinMax(uint16_t  _minTh, uint16_t  _maxTh) {
      minTh = _minTh;
      maxTh = _maxTh;
    }

    void update() {
      if (isAnalog) {
        currentReading = 1024 - analogRead(pin);
        state = currentReading > minTh ? 1 : 0;
      } else {
        if (isFrecCount) {
          // low pass filtering
          currentReading = easeUint(pulseIn(pin, HIGH, 1000L), currentReading, 3);
          state = (currentReading > minTh) ? 1 : 0;
        } else {
          // reseteo lo que dejo la interrupcion
          currentReading = easeUint(0, currentReading, 3);
          state = currentReading > minTh ? 1 : 0;
        }
      }
    };

    int debug() {
      Serial.print("pin:");
      Serial.print(pin);
      Serial.print("\t|");
      Serial.print("state: ");
      Serial.print(state);
      Serial.print("\t|");
      Serial.print("current value: ");
      Serial.print(currentReading);
      Serial.println("\t| ");
    };

    uint16_t easeUint(uint16_t current, uint16_t prev, uint16_t percent) {
      return  (current * 100 / percent + prev * (100 - (100 / percent))) / 100;
    };

    void handleInterrupt() {
      currentReading = digitalRead(pin) * 100;
    };




};

int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int led6 = 7;

int vu[] = {led1, led2, led3, led4, led5, led6};

void setup() {
  // put your setup code here, to run once:
 for (int ledPin = 0; ledPin < 6; ledPin ++) {
  pinMode(ledPin, OUTPUT);
 }
}

void loop() {
//   int ledPin = 7;
  for (int ledPin = 0; ledPin < 6; ledPin ++) {
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      analogWrite(vu[ledPin], fadeValue);
      delay(2);
    }
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(vu[ledPin], fadeValue);
      delay(2);
    }
  }

}


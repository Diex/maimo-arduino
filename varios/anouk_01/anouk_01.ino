

int sensor = 0;

void setup() {
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(9, INPUT);
}

void loop() {
  if (digitalRead(9)) {
    digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)

  } else {
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
  }



}

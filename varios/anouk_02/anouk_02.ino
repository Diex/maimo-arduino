

int sensor = A0;
int led1 = 2;
int led2 = 3;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(sensor, INPUT);

  Serial.begin(115200);
}


boolean detectado = false;

void loop() {

  detectado = digitalRead(sensor);

  if (detectado) {
    digitalWrite(led1, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led2, LOW);
  } else {
    digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led1, HIGH);
  }
}

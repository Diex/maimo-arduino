

int mic = 18;
int smoke = 10;
int cooler = 11;



void interrupt() {
  digitalWrite(smoke, LOW);
//  digitalWrite(cooler, LOW);
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(mic), interrupt, RISING);
  pinMode(smoke, OUTPUT);
//  pinMode(cooler, OUTPUT);
}


void loop() {
  delay(1000);
  digitalWrite(smoke, HIGH);
//  digitalWrite(cooler, LOW);
}




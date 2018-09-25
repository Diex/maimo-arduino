
void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), interrupcion, FALLING);
}

volatile int cuenta = 0;

void loop() {
  Serial.println(cuenta);
}

volatile long last_micros = 0;
volatile long debouncing_time = 60;


void interrupcion(){
  if( (long) (micros() - last_micros) >= debouncing_time * 1000) {
    cuenta ++;  
    last_micros = micros();
  }
}

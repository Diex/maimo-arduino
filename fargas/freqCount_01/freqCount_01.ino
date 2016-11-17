void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  Serial.begin(9600);
}

uint32_t time;

void loop() {
  // put your main code here, to run repeatedly:
//time =  pulseIn(2, HIGH);
//Serial.println(time);

Serial.println(analogRead(0));

delay(10);

}

/*
  Simple Transmitter Code
  This code simply counts up to 255
  over and over
  (TX out of Arduino is Digital Pin 1)
*/
byte counter;
int incomingByte = 0;

void setup() {
  Serial.begin(9600);
  //2400 baud for the 434 model
  Serial1.begin(600);
  counter = 0;
}

void loop() {
  //send out to transmitter
  Serial1.write(counter);
  counter++;
  delay(10);

  if (Serial1.available() > 0) {
    incomingByte = Serial1.read();    
    Serial.println(incomingByte, DEC);
  }

  

  incomingByte = 0;

 
}


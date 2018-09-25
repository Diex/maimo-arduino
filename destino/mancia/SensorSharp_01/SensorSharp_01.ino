void setup() {
  Serial.begin(9600);
}


float p; 
float ease;
float factor = 0.95;
boolean debug = false;

void loop() {
      float value = map(analogRead(A2), 0, 1024, 0, 1000) / 1000.0;
  p = p * factor + value * (1 - factor);

  if(debug){
        Serial.print(0);
    Serial.print('\t');
  Serial.print(value);
  Serial.print('\t');
  
  Serial.print(p);
  Serial.print('\t');
  
  Serial.print(1.0);
  Serial.println('\t');
  }else{
    Serial.println(p);
  }

  
  delay(100);
}

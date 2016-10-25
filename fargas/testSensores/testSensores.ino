void setup(){
  Serial.begin(115200);
}

void loop(){
  Serial.print(analogRead(A0));
    Serial.print(" : ");
  delay(1);
    Serial.print(analogRead(A1));
        Serial.print(" : ");
  delay(1);
    Serial.print(analogRead(A2));
        Serial.print(" : ");
  delay(1);
    Serial.print(analogRead(A3));
        Serial.print(" : ");
  delay(1);
  Serial.println();
//    Serial.println("-------------");
  delay(100);
}

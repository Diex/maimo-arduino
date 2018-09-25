
void setup() {
  Serial.begin(115200);
}
int valor;

void loop() {
  
  while (Serial.available() > 0) {
    valor = Serial.parseInt(); 
    Serial.println(valor);
  }
   
  analogWrite(9, valor);  
  delay(10);

}



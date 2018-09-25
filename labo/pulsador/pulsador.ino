int pulsador = 3;

void setup() {
  pinMode(pulsador, INPUT_PULLUP);
  Serial.begin(9600);
}

int cuenta = 0;
boolean yaLoConte = false;

long puedoContar = 10;
long ultimaVez = 0;

void loop() {

  int estado = digitalRead(pulsador);
  if (millis() - ultimaVez > puedoContar) {
    ultimaVez = millis();
    if (estado == 0) { // si apreto?
      if (yaLoConte) {

      } else {
        cuenta++;
        yaLoConte = true;
      }
    } else {
      yaLoConte = false;
    }
  } else {

  }

  Serial.println(cuenta);


}

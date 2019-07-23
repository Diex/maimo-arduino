char _buffer[256];
int id = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Restarting...");
  pinMode(13, OUTPUT);
}

void loop()
{
  if (OnReceive())
  {
    Serial.print("value: ");
//    int strcmp(const char *str1, const char *str2)
    
    Serial.println(_buffer);
    

    char caca[] = "caca";
    
    if(strncmp(_buffer, caca, strlen(caca)) == 0){
      digitalWrite(13, HIGH);
      Serial.println("linda caca");
    }
  }
}

bool OnReceive()
{
  bool status = false;

  if (Serial.available())
  {
    digitalWrite(13, HIGH);
    
    char _byte_received = Serial.read();
    if (_byte_received == '\n') {
      _buffer[id] = 0; // Mark the end of string.
      id = 0;
      status = true;
    } else {
      _buffer[id++] = _byte_received;
      _buffer[id+1] = '\0';
    }
    digitalWrite(13, LOW);
  }
  return status;
}
  

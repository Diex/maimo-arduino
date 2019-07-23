char _buffer[256];
int id = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Restarting...");
  pinMode(13, OUTPUT);
}


// messages:
char nogo[] = "nogo";
char okgo[] = "okgo";
char datain[] = "datain";
char showdata[] = "showdata";



char *message;

void loop()
{
  if (OnReceive())
  {
    Serial.print("value: ");    
    Serial.println(_buffer);
  }
   
   parseMessage(_buffer);

   Serial.print("the message is: ");
   Serial.println(message);
}

void parseMessage(char _buffer[]){
  if(strncmp(_buffer, nogo, strlen(nogo)) == 0) { message = nogo; return; }
  if(strncmp(_buffer, okgo, strlen(okgo)) == 0) { message = okgo; return; }
  if(strncmp(_buffer, datain, strlen(okgo)) == 0) { message = datain; return; }
  if(strncmp(_buffer, showdata, strlen(okgo)) == 0) { message = showdata; return; }
}

bool OnReceive()
{
  bool status = false;
  if (Serial.available())
  {
    char _byte_received = Serial.read();
    if (_byte_received == '\n') {
      _buffer[id] = 0; // Mark the end of string.
      id = 0;
      status = true;
    } else {
      _buffer[id++] = _byte_received;
      _buffer[id+1] = '\0';
    }    
  }
  return status;
}
  

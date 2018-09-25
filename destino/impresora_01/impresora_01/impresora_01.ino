#define IDLE 0
#define PRINTING 1
int state = IDLE;

int ledPin = 3;    // LED connected to digital pin 9
int button = 2;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  buttonLight();
  
  
  switch(state){
    case IDLE:
      if(!digitalRead(button)) {       
        state = PRINTING;
         Serial.println("bang");    
      }
    break;
      case PRINTING:
        
      break;
  }
}


uint32_t ptime = 0;
uint16_t ftime = 30;
int16_t fvalue = 0;
int16_t finc = 5;

void buttonLight(){
  
  if(millis() - ptime > ftime){
      fvalue += finc;
      if(fvalue >= 255 || fvalue < 0){
        finc *= -1;
      }            
      fvalue = constrain(fvalue, 0, 255);
      ptime = millis();      
   }
   analogWrite(ledPin, fvalue);
}


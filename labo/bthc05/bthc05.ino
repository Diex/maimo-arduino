#include <SoftwareSerial.h>

//#define uint8 unsigned char
//#define uint16 unsigned int
//#define uint32 unsigned long int

#define RxD 10 // This is the pin that the Bluetooth (BT_TX) will transmit to the Arduino (RxD)
#define TxD 11 // This is the pin that the Bluetooth (BT_RX) will receive from the Arduino (TxD)

#define DEBUG_ENABLED 1
//Servo myservo ;

int led = 9 ;

SoftwareSerial blueToothSerial(RxD, TxD);


/*----------------------SETUP----------------------------*/
void setup() {
  //myservo.attach(10);
  //myservo.write(0);

  Serial.begin(9600);//low Serial communication via USB cable to computer (if required)
  pinMode(RxD, INPUT); // Setup the Arduino to receive INPUT from the bluetooth shield on Digital Pin 6
  pinMode(TxD, OUTPUT); // Setup the Arduino to send data (OUTPUT) to the bluetooth shield on Digital Pin 7
  pinMode(13, OUTPUT); // Use onboard LED if required.
  pinMode(9, OUTPUT);
  setupBlueToothConnection(); //Used to initialise the Bluetooth shield


}


/*----------------------LOOP----------------------------*/
void loop() {
  digitalWrite(13, LOW); //Turn off the onboard Arduino LED
  char recvChar;
  while (1) {
    if (blueToothSerial.available()) {//check if there's any data sent from the remote bluetooth shield
      recvChar = blueToothSerial.read();
      Serial.print(recvChar); // Print the character received to the Serial Monitor (if required)

      //If the character received = 'r' , then change the RGB led to display a RED colour
      if (recvChar == 'r') {
        //  myservo.write(100);
        // Send32Zero(); // begin
        // DataDealWithAndSend(255, 0, 0); // first node data
        // Send32Zero(); // send to update data
        digitalWrite(led, HIGH);
        delay(500);

      }

      //If the character received = 'g' , then change the RGB led to display a GREEN colour
      if (recvChar == 'g') {
        digitalWrite(led, LOW);
        //  myservo.write(50);


      }

      //If the character received = 'b' , then change the RGB led to display a BLUE colour
      if (recvChar == 'b') {
        // Send32Zero(); // begin
        // DataDealWithAndSend(0, 0, 255); // first node data
        // Send32Zero(); // send to update data
        digitalWrite(led, HIGH);
        //myservo.write(180);
      }

      //If the character received = 'x' , then turn RGB led OFF
      if (recvChar == 'x') {
        // Send32Zero(); // begin
        // DataDealWithAndSend(0, 0, 0); // first node data
        // Send32Zero(); // send to update data
        digitalWrite(led, LOW);
        //myservo.write(0);
      }
    }

    //You can use the following code to deal with any information coming from the Computer (serial monitor)
    if (Serial.available()) {
      recvChar = Serial.read();

      //This will send value obtained (recvChar) to the phone. The value will be displayed on the phone.
      blueToothSerial.print(recvChar);
    }
  }
}



//The following code is necessary to setup the bluetooth shield ------copy and paste----------------
void setupBlueToothConnection()
{
  blueToothSerial.begin(9600);// BluetoothBee BaudRate to default baud rate 38400
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STNA=HC-05\r\n"); //set the bluetooth name as "SeeedBTSlave"
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable
  Serial.println("The slave bluetooth is inquirable!");
  delay(2000); // This delay is required.
  blueToothSerial.flush();
}

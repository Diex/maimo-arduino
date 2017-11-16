#include <DS3231.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 3;
SimpleDHT11 dht11;

// SD
const int chipSelect = 4;

// RTC ----------
DS3231 Clock;
bool h12;
bool PM;
bool Century = false;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;
boolean gotTrouble = false;
// Compass
#define addr 0x1E //I2C Address for The HMC5883


void setup() {
  Wire.begin();
  Serial.begin(115200);
  //  setClock();
  // analogReference(EXTERNAL);
  
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    gotTrouble = true;
    return;
  }

  Wire.beginTransmission(addr); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();

  Serial.println("card initialized.");
  
}

void loop() {
  if(gotTrouble) return;

  // ----------------------------------------
  // rtc
  String dataString = "";

  dataString += "20";
  dataString += Clock.getYear();
  dataString += '-';
  dataString += Clock.getMonth(Century);
  dataString += '-';
  dataString += Clock.getDate();
  dataString += ',';
  // Finally the hour, minute, and second
  dataString += Clock.getHour(h12, PM);
  dataString += ':';
  dataString += Clock.getMinute();
  dataString += ':';
  dataString += Clock.getSecond();
  dataString += ",";

  // Display the temperature
  // dataString += Clock.getTemperature();
  // dataString += ',';

  // Tell whether the time is (likely to be) valid
  // if (Clock.oscillatorCheck()) {
    // dataString += "osc:OK";
  // } else {
    // dataString += "osc:FUCK";
  // }

  
  // ----------------------------------------
  // DHT11
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    //    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    temperature = -1;
    humidity = -1;
    //    return;
  }

  dataString += (int)temperature;
  dataString += ",";
  dataString += (int)humidity;
  dataString += ",";

  // ----------------------------------------
//  Serial.println(dataString);
  // ----------------------------------------


  // uso un archivo por dia
  String filename = "20";
  filename += Clock.getYear();
  filename += Clock.getMonth(Century);
  filename += Clock.getDate();
  filename += '.';
  filename += "csv";
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(filename, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.print("error opening: ");
    Serial.println(filename);
    gotTrouble = true;
  }
  Serial.println(dataString);
  delay(1000);
}

void setClock() {
  Clock.setClockMode(false);
  Clock.setSecond(0);
  Clock.setMinute(37);
  Clock.setHour(21);
  Clock.setDoW(5);
  Clock.setDate(17);
  Clock.setMonth(7);
  Clock.setYear(17);
}


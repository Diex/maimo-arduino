#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
char ssid[] = "suckmykiss";    //  your network SSID (name)
char pass[] = "frutigran";   // your network password
int status = WL_IDLE_STATUS;
WiFiClient  client;

unsigned long myChannelNumber = 365636;
const char * myWriteAPIKey = "X4UUXU8N99J86PI8";

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

String data;
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    data = Serial.readString();
    char str[256];
    data.toCharArray(str, 256);
    char * pch;
    pch = strtok (str, " ,.-");
    int count = 1;
    while (pch != NULL)
    {
      pch = strtok (NULL, ",");
      ThingSpeak.setField(count, pch);
      count++;
    }

    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  }

}

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
// https://github.com/Robot-Will/Stino/issues/445
#include "steer.h"
#include "lcd.h"
#include "lineFollower.h"
#include "index.h"  //Web page header file

const char * ssid = "suckmykiss";
const char * password = "frutigran";

// estados de control general del robot
#define GO 1 // el robot avanza - usa el lineFollower
#define DOWNLOADING 2
#define WAITING 4
int action = GO;
static const char * TAG = "infante";




ESP8266WebServer server(80);



//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
void handleFrontSensors() {
 
 String data = ">>";
 for(int i = 0; i < 8; i++)
 {
    data += (status >> i) & 1 ? "1" : "0";
 }

 server.send(200, "text/plane", data); //Send ADC value only to client ajax request
}



void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)? "GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}



void setup()
{
  pinMode(1, FUNCTION_3); 
  pinMode(3, FUNCTION_3); 

  Serial.begin(115200);
  Serial.println("Booting");


  lineFollowerSetup();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // web server
  server.on("/", handleRoot);
  server.on("/frontSensors", handleFrontSensors);//To get update of ADC Value only
  server.onNotFound(handleNotFound);
  
  server.begin();
  
  Serial.println("HTTP server started");
  
  // infante
  steerSetup();
  testSequence();
}

void loop()
{
  infante();
  server.handleClient();
 
}

void infante()
{
  readSensors();
}

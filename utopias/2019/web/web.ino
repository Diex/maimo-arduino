/*
  ESP8266 Temperatur WiFi-Sensor -19.07.2018 - pb -
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
// #include <OneWire.h>
// #include <DallasTemperature.h>

String index_html="";
const char before[] PROGMEM={"<!DOCTYPE html>\n<html>\n<head>\n<meta http-equiv=\"refresh\" content=\"5\"/>\n<style>\nh1 {\n    color: blue;\n    font-family: verdana;\n    font-size: 300%;\n\n}\np  {\n    color: red;\n    font-family: courier;\n    font-size: 160%;\n}\n</style>\n</head>\n<body>\n\n<h1>"};
const char after[] PROGMEM={"</h1>\n\n\n</body>\n</html>\n"};

#define ONE_WIRE_BUS 2 // GPIO of ESP8266 = GPIO2
// OneWire oneWire(ONE_WIRE_BUS);
// DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
String temperature_string = "";
float temperature;

// EspClass ESPm;

const char* ssid = "DLINK";
const char* password = "C63SxIpdTT";



ESP8266WebServer server(80);



void handleRoot() {

  temperature_string = "Temperature: " + String((float)temperature,1) + " C";
  server.send_P(200, "text/html", index_html);

}

void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);

}

void setup(void) {

  sensors.begin(); /* Initialize Dallas temperature library */


  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());



  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void get_temperature() {

  // Get temperature

  // sensors.requestTemperatures();
  // temperature = sensors.getTempCByIndex(0);

  Serial.println();
  Serial.print(temperature,1);
  Serial.print(" Grad Celsius");
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(2000);
}



void loop() {
  server.handleClient();
  get_temperature();
index_html = before + temperature_string + after;
}
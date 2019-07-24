#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


// Neopixel
#include <Adafruit_NeoPixel.h>

// https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html
// https://github.com/tzapu/WiFiManager
// server de control del robot infante

const char* ssid     = "suckmykiss";  // the ssid/name of the wifi, the esp will be connected to
const char* password = "frutigran";   // the password of that wifi

const char* assid = "infante";
const char* asecret = "umai";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>Usted se ha conectado a Robot Infante</h1>");
}

void handleNotFound() {
  server.send(404, "text/plain", "404: :( "); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void handleButton() {
  server.send(200, "text/html", "<form action=\"/hikido\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
}


#define LED D2

#define DATA_IN   2
#define SHOW_DATA 1
#define ROBOT_GO  0


const char datain[] = "datain";
const char showdata[] = "showdata";
const char robotgo[] = "robotgo";


char *message;
int messageId = -1;

char notes[256];
int dataValue = 0;

boolean newmessage = false;


// Neopixel Config
#define NeoPIN D7
#define NUM_LEDS 8
int brightness = 150;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NeoPIN, NEO_RGB + NEO_KHZ800);


void handleMessage() {

  newmessage = true;

  char arg[256];
  char val[256];

  for (uint8_t i = 0; i < server.args(); i++) {

    Serial.print(server.argName(i));
    Serial.print(": ");
    Serial.println(server.arg(i));


    server.argName(i).toCharArray(arg, 256);
    server.arg(i).toCharArray(val, 256);

    if (strncmp(arg, datain, strlen(datain)) == 0) {
      messageId = DATA_IN;
      server.arg(i).toCharArray(notes, 256);

    } else if (strncmp(arg, robotgo, strlen(robotgo)) == 0) {
      messageId = ROBOT_GO;
      dataValue = (strncmp(val, "0", 1) == 0) ? 0 : 1;
    } else if (strncmp(arg, showdata, strlen(showdata)) == 0) {
      messageId = SHOW_DATA;
      dataValue = atoi(val);
    }
  }



  server.send(200, "text/plain", "message received");
  // server.sendHeader("Location","/message");        // Add a header to respond with a new location for the browser to go to the home page again
  // server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}


int penta[] = {200, 225, 250, 300, 333, 400, 450, 500, 600, 666};
int colors[] = {0x95329F, 0xFB35A7, 0x9F70BE, 0x8CDE10, 0x3BBAFF,  0xCF332B, 0xE8DA04, 0x4C7F1D, 0xD9EA57, 0xCF32B0};



void toneESP(uint8_t _pin, unsigned int frequency, unsigned long duration) {
  pinMode (_pin, OUTPUT );
  analogWriteFreq(frequency);
  analogWrite(_pin, 500);  
  delay(duration);
  analogWrite(_pin, 0);
}


void setup() {

  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  WiFi.mode(WIFI_AP_STA);

  //access point part
  Serial.println("Creating Accesspoint");
  WiFi.softAP(assid, asecret, 7, 0, 5);

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());

  //station part
  Serial.print("connecting to...");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  //   we send our IP address on the WiFi network
  if (!MDNS.begin("infante")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }

  Serial.println("mDNS responder started");

  server.on("/", handleRoot);
  server.on("/button", handleButton);
  server.on("/message", handleMessage);

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  strip.setBrightness(brightness);
  strip.begin();
  strip.show(); 
  delay(50);
  Serial.println("NeoPixel started");


}

void loop() {
  MDNS.update();
  server.handleClient();

  processMessage(); // tone(3, random(1000), 100);

}


void setNeoColor(int value){
  Serial.print("Setting Neopixel...");
  // converting Hex to Int
  int number = value; // (int) strtol( &value[1], NULL, 16);
  
  // splitting into three parts
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;
  
  // setting whole strip to the given color
  for(int i=0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color( g, r, b ) );
  }
 
  strip.show();
  
 
}


void processMessage() {
  if (!newmessage) return;

  Serial.println("new message");

  newmessage = false;
  int delay = 0;
  long now = 0;

  switch (messageId) {
  case ROBOT_GO:
    digitalWrite(LED, dataValue);
    break;

  case SHOW_DATA:
    delay = dataValue > 200 ? 200 : dataValue;
    now = millis();

    for(int note = 0; note < strlen(notes); note++) {  // voy a terminar cuando encuentro el caracter 'E'      
      if(notes[note] == 'E') break;
    // void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
      setNeoColor(colors[notes[note] - '0']);
      toneESP(D8,  penta[notes[note] - '0'], delay);
      setNeoColor(0);
      Serial.print(notes[note] - '0');
      Serial.print(':');
      Serial.print(penta[notes[note] - '0']);
      Serial.print(':');
    }

  // blabla...
    break;

  case DATA_IN:

    break;


  }

}

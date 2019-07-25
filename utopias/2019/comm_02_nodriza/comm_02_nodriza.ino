#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>


// Neopixel
#include <Adafruit_NeoPixel.h>

// https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html
// https://github.com/tzapu/WiFiManager
// server de control del robot infante

// const char* ssid     = "CCU";  // the ssid/name of the wifi, the esp will be connected to
// const char* password = "";   // the password of that wifi

const char* ssid     = "infante";  // the ssid/name of the wifi, the esp will be connected to
const char* password = "umai12345678";   // the password of that wifi


const char* assid = "nodriza";
const char* asecret = "umai";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>Usted se ha conectado a Robot Nodriza</h1>");
}

void handleNotFound() {
  server.send(404, "text/plain", "404: :( "); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void handleButton() {
  server.send(200, "text/html", "<form action=\"/hikido\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
}


#define LED D6

#define ROBOT_GO  0
#define ROBOT_NOGO  1
#define DATA_IN   2
#define SHOW_DATA 3


const char datain[] = "datain";
const char showdata[] = "showdata";
const char robotgo[] = "robotgo";


char *message;
int messageId = -1;

char notes[256];
int dataValue = 0;

boolean newmessage = false;

int status = -1;

// Neopixel Config
#define NeoPIN D7
#define buzzer D8
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
  if (!MDNS.begin("nodriza")) {
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

  switch(status){
    case ROBOT_GO:
    break;

    case ROBOT_NOGO:
    break;

    default:
    seq1();
    break;
  }
}

void robotsGo(){

  HTTPClient http;    //Declare object of class HTTPClient
 
  //Post Data
  String postData = "robotgo=1";
  
  http.begin("http://infante.local/message/");              //Specify request destination
  http.addHeader("Content-Type", "text/plain");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
 
  Serial.print("httpCode");
  Serial.println(httpCode);   //Print HTTP return code
  Serial.print("payload");
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection

  status = ROBOT_GO;
}


char  url[] = "http://152.152.152.152/message";
char  msg1[] = "robotgo=1";
char  msg2[] = "robotgo=0";
char msg3[] = "datain=123456789E";
char msg4[] = "showdata=200";


const char sc1[]  = "datain=6257449155199819787662574491551998197876E";
const char sc2[]  = "datain=4173637875621766625744458717390361014939E";
const char sc3[]  = "datain=5210842659386807094936181275452224845957E";
const char sc4[]  = "datain=8516803539810725349444433501582345497653E";
const char sc5[]  = "datain=5882276482115427618684449051971991698523E";
const char sc6[]  = "datain=9501638183453242123139684146031312447573E";
const char sc7[]  = "datain=3641311234516255331987598728711718645270E";
const char sc8[]  = "datain=3176014245643737624698990601280638522241E";
const char sc9[]  = "datain=3314973469488713461701668306298189586129E";
const char sc10[] = "datain=3351317039510238005586228404088563138889E";
const char sc11[] = "datain=5523235045035010387016870506262734898837E";
const char sc12[] = "datain=4003905095472182184279541161737282561078E";
const char sc13[] = "datain=1352624935368459570520503083631475093514E";
const char sc14[] = "datain=9364305879801433586127158532772903213347E";
const char sc15[] = "datain=1766299240995411516682481356996677082050E";
const char sc16[] = "datain=0573543063746524806717967731846668610483E";
const char sc17[] = "datain=7971537163083545222576525105039636260672E";
const char sc18[] = "datain=4238534527698157705136682930004353970807E";
const char sc19[] = "datain=3382295116561489223903613525948815551550E";
const char sc20[] = "datain=1149986358045665358183368640854224671641E";

const char * scores[] = {sc1,sc2,sc3,sc4,sc5,sc6,sc7,sc8,sc9,sc10,sc11,sc12,sc13,sc14,sc15,sc16,sc17,sc18,sc19,sc20};

void seq1(){

  digitalWrite(LED, 0); // me detengo
  postMessage(msg2);  // detengo al infante...
  Serial.println("both stop");
  
  int cual = random(sizeof(scores)/sizeof(char));
  char data[128];
   
  strcat(data,scores[cual]);
  
  postMessage(data);  // send data

  char * pch = strtok(data, "=");
  Serial.print("data: ");
  Serial.println(pch);


  // pch.toCharArray(notes, 256);
  strcpy(notes, pch);
  showData(200); // muestro la data

  
  postMessage(msg4);  // le digo a infante que muestre la data...


  delay(5000);

  digitalWrite(LED, 1);
  postMessage(msg1);
  delay(5000);
}


boolean postMessage(char data[]){

  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // http.addHeader("Host", "www.shippingmanager.dk");
  // http.addHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0");
  // http.addHeader("Accept-Language", " en-US,en;q=0.5");
  // http.addHeader("Accept-Encoding", " gzip, deflate, br");
  // http.addHeader("X-Requested-With", " XMLHttpRequest");
  // http.addHeader("Referer", " https://www.shippingmanager.dk/sh/?fb_source=shippingmanager.dk");
  // http.addHeader("Connection", "keep-alive");
  // http.addHeader("Pragma", " no-cache");
  // http.addHeader("Cache-Control", " no-cache");

  Serial.print(">>> : "); Serial.println(url);
  Serial.print(">>> : "); Serial.println(data);

  int result = http.POST(data);
  String payload = http.getString();    //Get the response payload

  // http.writeToStream(&Serial);
  http.end();
  
  Serial.print("<<< : "); Serial.println(result);
  Serial.print("<<< : "); Serial.println(payload);

  delay(1000);
  return (result == 200) ? true : false ;

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


void showData(int dataValue){

  int delay = dataValue > 200 ? 200 : dataValue;
   long now = millis();

    for(int note = 0; note < strlen(notes); note++) {  // voy a terminar cuando encuentro el caracter 'E'      
      if(notes[note] == 'E') break;
    // void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
      setNeoColor(colors[notes[note] - '0']);
      toneESP(buzzer,  penta[notes[note] - '0'], delay);
      setNeoColor(0);
      Serial.print(notes[note] - '0');
      Serial.print(':');
      Serial.print(penta[notes[note] - '0']);
      Serial.print(':');
    }

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
    showData(dataValue);
  // blabla...
    break;

  case DATA_IN:

    break;


  }

}

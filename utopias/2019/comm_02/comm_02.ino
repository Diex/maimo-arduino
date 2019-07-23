#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

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


char *message;
char data[256];
int messageId = -1;

#define DATA_IN   2
#define SHOW_DATA 1
#define ROBOT_GO  0


char datain[] = "datain";
char showdata[] = "showdata";
char robotgo[] = "robotgo";

int dataValue = 0;

boolean newdata = false;
boolean newmessage = false;

#define LED 2

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
      
      if (!newdata) { 
        server.arg(i).toCharArray(data, 256);
        newdata = true;     
      }

    }else if(strncmp(arg, robotgo, strlen(robotgo)) == 0){
      messageId = ROBOT_GO;
      dataValue = (strncmp(val, "0", 1) == 0) ? 0 : 1; 
    }
  }



  server.send(200, "text/plain", "message received");
  // server.sendHeader("Location","/message");        // Add a header to respond with a new location for the browser to go to the home page again
  // server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
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


}

void loop() {
  MDNS.update();
  server.handleClient();
 
  processMessage(); // tone(3, random(1000), 100);

}

void processMessage(){
  if(!newmessage) return;
  
  Serial.println("new message");

  newmessage = false;

  switch(messageId){
    case ROBOT_GO:
      digitalWrite(LED, dataValue);
    break;

    case SHOW_DATA:
      // blabla...
    break;

    case DATA_IN:

    break;


  }

}
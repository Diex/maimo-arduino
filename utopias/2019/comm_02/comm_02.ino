#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


const char* ssid     = "suckmykiss"; // the ssid/name of the wifi, the esp will be connected to
const char* password = "frutigran"; // the password of that wifi

const char* assid = "espAccessPoint";
const char* asecret = "hello";

ESP8266WebServer server(80);
int led = 2;


/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");

}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void hikido(){  
  digitalWrite(led,!digitalRead(led));      // Change the state of the LED  
  server.sendHeader("Location","/button");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleButton(){  
  server.send(200, "text/html", "<form action=\"/hikido\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
}

char *message;
char data[256];
char datain[] = "datain";

void handleMessage(){
  Serial.println(server.uri());
  Serial.println(server.method());
  Serial.println(server.args());

  for (uint8_t i = 0; i < server.args(); i++) {
    
    Serial.println( "" + server.argName(i) + ": " + server.arg(i));
    
    char temp[256];
    server.argName(i).toCharArray(temp,256);
    
    Serial.println(temp);

    if(strncmp(temp, datain, strlen(datain)) == 0){
      Serial.println("======");
      server.arg(i).toCharArray(data, 256);
      Serial.println(data);
    } 
  }

  

  server.send(200, "text/plain", "message received");
  // server.sendHeader("Location","/message");        // Add a header to respond with a new location for the browser to go to the home page again
  // server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}



void setup(){
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  
  WiFi.mode(WIFI_AP_STA);
 

  //access point part
  Serial.println("Creating Accesspoint");
  WiFi.softAP(assid,asecret,7,0,5);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());

  //station part
  Serial.print("connecting to...");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
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
  // Add service to MDNS-SD
  // MDNS.addService("http", "tcp", 80);

  server.on("/", handleRoot);
  server.on("/button", handleButton);
  server.on("/hikido", HTTP_POST, hikido);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.on("/message", handleMessage);

  server.onNotFound(handleNotFound); 
  server.begin();
  Serial.println("HTTP server started");

  
}

void loop() {
  MDNS.update();
  server.handleClient();
  // tone(3, random(1000), 100);
  
}

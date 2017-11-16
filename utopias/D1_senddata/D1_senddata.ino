#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>                // para crear los mensajes osc. https://github.com/CNMAT/OSC

ESP8266WiFiMulti WiFiMulti;

WiFiUDP Udp;               // A UDP instance to let us send and receive packets over UDP
// 192.168.1.102
//const IPAddress destIp(192, 168, 43, 18); // remote IP of the target device  192.168.43.18
const IPAddress destIp(192, 168, 0, 3); // remote IP of the target device  192.168.43.18
const unsigned int destPort = 12000;    // remote port of the target device where the NodeMCU sends OSC to
const unsigned int localPort = 8000;   // local port to listen for UDP packets at the NodeMCU (another device must send OSC messages to this port)



void setup() {
  // initialize serial communication
  Serial.begin(115200);
  initDevice();
}

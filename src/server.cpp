#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;


const char* ssid = "Basri";
const char* password = "123456789";
IPAddress broadcastIP(192, 168, 232, 255); // Your network's broadcast IP
WiFiUDP udp;
unsigned int localPort = 5763; // dinleme por

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  udp.begin(localPort);
  Serial.print("Listening on IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Udp Remote IP: ");
  Serial.println(udp.remoteIP());

}

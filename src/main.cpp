#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;

const char* ssid = "Basri";
const char* password = "123456789";
//IPAddress broadcastIP(192, 168, 43, 255); // Your network's broadcast IP
//unsigned int localPort = 5763; // Local port to listen on
WiFiServer server(5764);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  server.begin();
  Serial.println("Server started");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String message = client.readStringUntil('\r');
        Serial.print("Client says: ");
        Serial.println(message);
        client.println("Hello, client! I received your message.");
      }
    }
    client.stop();
  }
}
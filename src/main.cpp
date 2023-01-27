#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <DHT.h>
#include <stdio.h>


#define DHTPIN 18 
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);
WiFiUDP Udp;


const char* ssid = "Basri";
const char* password = "123456789";
IPAddress broadcastIP(192, 168, 232, 255); // Your network's broadcast IP
WiFiUDP udp;
unsigned int localPort = 5763; // dinleme por

void setup() {
  Serial.begin(115200);
  dht.begin();
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

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  const char* message = " HelloWorld Basri";
  char tempString[28];
  sprintf(tempString, " Sicaklik: %.2f Nem: %.2f", t,h);
  const char* temperature = tempString;
  Udp.beginPacket(broadcastIP, localPort);
  Udp.write((const uint8_t*) temperature, strlen(temperature));
  Udp.endPacket();
  delay(1000);
}
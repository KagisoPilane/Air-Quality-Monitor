#include <ESP8266WiFi.h>

const char* ssid = "HUAWEI-D755";
const char* password = "ADEAGT63678";

const char* host = "maker.ifttt.com";
const int fireSensorPin = D1;  // Define the pin for the fire sensor

void setup() {
  Serial.begin(115200);
  Serial.println("Email from Node Mcu");
  delay(100);
  delay(1000);
  connectWiFi();
}

void loop() {
  while (!(WiFi.status() == WL_CONNECTED)) {
    connectWiFi();
  }

  WiFiClient client;
  const int httpPort = 80;

  if (digitalRead(fireSensorPin) == LOW) { // Fire detected
    Serial.println("Fire in the House");

    if (client.connect(host, httpPort)) {
      String url = "/trigger/FIRE_ALERT/json/with/key/bBHfgdLhEoFYhWb1vdQWUccev2Ij2Gn8am2ws-_5xuC";
      Serial.print("Requesting URL: ");
      Serial.println(url);
      client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    } else {
      Serial.println("Connection failed");
    }

    // Delay before checking the fire sensor again
    delay(1000);
  }
}

void connectWiFi() {
  int i = 0;
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);

  while (!(WiFi.status() == WL_CONNECTED)) {
    Serial.println(" - ");
    i++;
    delay(300);
    if (i > 10) {
      connectWiFi();
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

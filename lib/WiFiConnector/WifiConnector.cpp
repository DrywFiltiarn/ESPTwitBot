#include <WiFi.h>
#include "WiFiConnector.h"

void WiFiConnectorClass::begin() {
  Serial.println();
  Serial.print("WiFi setup connection: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void WiFiConnectorClass::begin(ScreenClass Screen) {
  unsigned long start = millis();

  Screen.clear();
  Screen.writeln(TFT_CYAN, "WiFi connecting to...");
  Screen.writeln(TFT_BLUE, WIFI_SSID);
  Screen.writeln();

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Screen.write(TFT_ORANGE, '=');
  }

  Screen.writeln();
  Screen.writeln();
  Screen.writeln(TFT_CYAN, "WiFi connected...");
  Screen.writeln(TFT_BLUE, "IP " + WiFi.localIP().toString());
  Screen.writeln();
  Screen.writeln(TFT_CYAN, "Init time (ms)...");
  Screen.writeln(TFT_BLUE, String(((millis() - start))) + "ms");
}

void WiFiConnectorClass::end() {
  Serial.println();
  Serial.println("WiFi disconnected...");
  WiFi.disconnect(true);
}

WiFiConnectorClass WiFiConnector;
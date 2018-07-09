#include <HardwareSerial.h>
#include <WiFiConnector.h>
#include <Screen.h>

void setup() {
  Serial.begin(115200);
  Screen.init();
  Screen.clear();
  WiFiConnector.begin(Screen);
}

void loop() {
}
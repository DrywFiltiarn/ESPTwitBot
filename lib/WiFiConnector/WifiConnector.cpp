#include <WiFiConnector.h>
#include <WiFi.h>

void WiFiConnectorClass::init() {
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

void WiFiConnectorClass::init(ScreenClass* screen) {
  this->screen = screen;
  unsigned long start = millis();

  screen->clear();
  screen->writeln(TFT_CYAN, "WiFi connecting to...");
  screen->writeln(TFT_BLUE, WIFI_SSID);
  screen->writeln();

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    screen->write(TFT_ORANGE, '=');
  }

  screen->writeln();
  screen->writeln();
  screen->writeln(TFT_CYAN, "WiFi connected...");
  screen->writeln(TFT_BLUE, "IP " + WiFi.localIP().toString());
  screen->writeln();
  screen->writeln(TFT_CYAN, "Init time (ms)...");
  screen->writeln(TFT_BLUE, String(((millis() - start))) + "ms");
  delay(500);
}

void WiFiConnectorClass::end() {
  Serial.println();
  Serial.println("WiFi disconnected...");
  WiFi.disconnect(true);
}

WiFiConnectorClass WiFiConnector;
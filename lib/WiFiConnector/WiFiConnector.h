#include "Screen.h"

#ifndef WIFICONNECTOR_H
#define WIFICONNECTOR_H

#ifndef WIFI_SSID
  #define WIFI_SSID "ssid"
#endif
#ifndef WIFI_PASS
  #define WIFI_PASS "pass"
#endif

class WiFiConnectorClass {
  public:
    void init();
    void init(ScreenClass* screen);
    void end();

  private:
    ScreenClass* screen;
};

extern WiFiConnectorClass WiFiConnector;
#endif
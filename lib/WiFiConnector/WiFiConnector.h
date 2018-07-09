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
    void begin();
    void begin(ScreenClass Screen);
    void end();
};

extern WiFiConnectorClass WiFiConnector;
#endif
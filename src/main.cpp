#include <HardwareSerial.h>
#include <WiFiConnector.h>
#include <Screen.h>
#include <TweetMonitor.h>

#include <WiFiClientSecure.h>

TaskHandle_t *dataTaskHandle;
TaskHandle_t *displayTaskHandle;

void dataTask(void * unused) {
  Serial.println("Data task running on core: " + String(xPortGetCoreID()));
  WiFiConnector.init(&Screen);
  WiFiClientSecure client;
  TweetMonitor.init(&Screen, client, TWITTER_QUERY);

  for(;;) {
    // WiFiConnector.watchState(); // Todo: Implement WiFi state watching
    TweetMonitor.watchTweets();
    delay(50); // Small 50ms interval to not run too fast
  }
}

void displayTask(void * unused) {
  Serial.println("Display task running on core: " + String(xPortGetCoreID()));
  for(;;) {
    // TODO: Implement logic to display tweets 
    delay(1000); // Placeholder interval of 1 second
  }
}

void setup() {
  Serial.begin(115200);
  Screen.init();

  xTaskCreatePinnedToCore(dataTask, "dataTask", 1024 * 50, NULL, 1, dataTaskHandle, 0);
  xTaskCreatePinnedToCore(displayTask, "displayTask", 1024 * 50, NULL, 1, displayTaskHandle, 1);
}

 void loop() { /* Do nothing */ }
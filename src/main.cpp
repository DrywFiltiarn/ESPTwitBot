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
    // WiFiConnector.watchState();
    TweetMonitor.watchTweets();
    delay(100);
  }
}

void displayTask(void * unused) {
  Serial.println("Display task running on core: " + String(xPortGetCoreID()));
  for(;;) {
    delay(1000);
  }
}

void setup() {
  Serial.begin(115200);
  Screen.init();

  xTaskCreatePinnedToCore(dataTask, "dataTask", 1024 * 50, NULL, 1, dataTaskHandle, 0);
  xTaskCreatePinnedToCore(displayTask, "displayTask", 1024 * 50, NULL, 1, displayTaskHandle, 1);

  // TweetMonitor.watchTweets();
  /*
  int start = millis();
  Screen.clear();
  Screen.writeln(TFT_CYAN, "Getting tweets...");
  String responseString = api.getTweets("%23esptwitbot%20OR%20@esptwitbot");
  Screen.writeln(TFT_BLUE, "Loaded in " + String(((millis() - start))) + "ms");
  Screen.writeln();

  start = millis();
  Screen.writeln(TFT_CYAN, "Parsing JSON...");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& response = jsonBuffer.parseObject(responseString);

  Serial.println(responseString);
  Serial.println();
  Serial.println();

  if (response.success()) {
    Screen.writeln(TFT_BLUE, "Parsed JSON in " + String(((millis() - start))) + "ms");

    JsonArray& statuses = response["statuses"].asArray();

    int tweetCount = statuses.size();

    Screen.writeln();
    Screen.writeln(TFT_ORANGE, String(tweetCount) + " tweets found");
    Screen.writeln();
    Screen.writeln(TFT_BLUE, "Posted by... ");

    for (int i = 0; i < tweetCount; i++) {
      long id = statuses[i]["id"];
      String screenname = statuses[i]["user"]["screen_name"];
      String message = statuses[i]["text"];

      tweets[i] = {id, screenname, message};
      Screen.writeln(TFT_GREENYELLOW, "@" + screenname);
    }
  } else {
    Screen.writeln(TFT_RED, "Failed to parse JSON");
  }

  Screen.writeln();
  */
}

 void loop() {}
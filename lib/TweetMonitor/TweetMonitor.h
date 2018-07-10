#include <WiFiClientSecure.h>
#include <Screen.h>

#ifndef TWITTER_BEARER
  #define TWITTER_BEARER "bearer_token"
#endif
#ifndef TWITTER_QUERY
  #define TWITTER_QUERY "%23esptwitbot%20OR%20@esptwitbot"
#endif

#ifndef TWEETMONITOR_H
#define TWEETMONITOR_H

#define TW_API_HOST "api.twitter.com"
#define TW_API_SSL_PORT 443
#define TW_API_TIMEOUT 3000
#define TW_API_INTERVAL 15000

struct Tweet {
  long id;
  String screenname;
  String message;
};

class TweetMonitorClass
{
  public:
    void init(ScreenClass* screen, Client &client, String query);
    void watchTweets();
    
  private:
    ScreenClass* screen;
    Client* client;
    String query;
    const int maxMessageLength = 10000;
    bool initialized = false;
    ulong lastUpdate = 0;

    String request(String command);
};

extern TweetMonitorClass TweetMonitor;
#endif
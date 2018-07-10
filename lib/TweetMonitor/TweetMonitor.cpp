#include <TweetMonitor.h>

void TweetMonitorClass::init(ScreenClass* screen, Client &client, String query) {
	this->screen = screen;
	this->client = &client;
	this->query = query;

	screen->clear();
	screen->writeln(TFT_CYAN, "WatchTweets()");

	lastUpdate = millis();
}

String TweetMonitorClass::request(String command) {
	String headers;
	String body;

	bool finishedHeaders = false;
	bool currentLineIsBlank = true;

	unsigned long now;
	bool avail;

	if (client->connect(TW_API_HOST, TW_API_SSL_PORT)) {
		int ch_count = 0;

		client->println("GET " + command +  " HTTP/1.1");
		client->println("Host: " TW_API_HOST);
		client->println("User-Agent: ESP32TwitBot/1.0.0");
		client->println("Authorization: Bearer " + String(TWITTER_BEARER));
		client->println("");
		now = millis();
		avail=false;

		while (millis() - now < TW_API_TIMEOUT) {
			while (client->available()) {
				avail = finishedHeaders;
				char c = client->read();

				if(!finishedHeaders){
					if (currentLineIsBlank && c == '\n') finishedHeaders = true;
					else headers = headers + c;
				} else {
					if (ch_count < maxMessageLength)  {
						body = body + c;
						ch_count++;
					}
				}

				if (c == '\n') currentLineIsBlank = true;
				else if (c != '\r') currentLineIsBlank = false;
			}
			if (avail) {
				break;
			}
		}
	}

	client->stop();
	return body;
}

void TweetMonitorClass::watchTweets() {
	if (!initialized || millis() - lastUpdate >= 15000) {
		initialized = true;

		Serial.println("Update after: " + String(millis() - lastUpdate) + "ms");
		
		int start = millis();
		
		String command = "/1.1/search/tweets.json?q=" + query + "&result_type=recent";
		String response = request(command);

		// TODO: process response

		screen->writeln(TFT_BLUE, "Loaded tweets in: " + String(millis() - start) + "ms");
		lastUpdate = millis();
	}
}

TweetMonitorClass TweetMonitor;
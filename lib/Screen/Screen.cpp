#include <Screen.h>
#include <TFT_eSPI.h>

void ScreenClass::init() {
  tft = TFT_eSPI();
  tft.init();
  tft.setRotation(1);
}

void ScreenClass::clear() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
}

void ScreenClass::write(int color, char chr) {
  tft.setTextColor(color);
  tft.write(chr);
}

void ScreenClass::writeln() {
  tft.println();
}
void ScreenClass::writeln(int color, String str) {
  tft.setTextColor(color);
  tft.println(str);
}

ScreenClass Screen;

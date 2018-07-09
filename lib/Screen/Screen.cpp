#include <TFT_eSPI.h>
#include "Screen.h"

void ScreenClass::init() {
  this->tft = TFT_eSPI();
  this->tft.init();
  this->tft.setRotation(1);
}

void ScreenClass::clear() {
  this->tft.fillScreen(TFT_BLACK);
}

void ScreenClass::write(int color, char chr) {
  this->tft.setTextColor(color);
  this->tft.write(chr);
}

void ScreenClass::writeln() {
  this->tft.println();
}
void ScreenClass::writeln(int color, String str) {
  this->tft.setTextColor(color);
  this->tft.println(str);
}


ScreenClass Screen;

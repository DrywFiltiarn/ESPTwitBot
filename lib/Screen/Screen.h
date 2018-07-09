#include <TFT_eSPI.h>

#ifndef SCREEN_H
#define SCREEN_H

class ScreenClass {
  public:
    void init();
    void clear();
    void write(int color, char chr);
    void writeln();
    void writeln(int color, String str);

  private:
    TFT_eSPI tft;
};

extern ScreenClass Screen;
#endif
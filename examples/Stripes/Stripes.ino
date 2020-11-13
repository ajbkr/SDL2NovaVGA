#include "NovaVGA.h"

#define CS_PIN 10

void fillStripes(uint8_t color1, uint8_t color2, bool vertical) {
  uint8_t c;
  int w, h;
  int high;

  for (h = 0; h < NovaVGA.SCREEN_HEIGHT; ++h) {
    for (w = 0; w < NovaVGA.SCREEN_WIDTH; ++w) {
      high = vertical ? 0x01 & w : 0x01 & h;
      c = high ? color1 : color2;

      NovaVGA.writePixel(w, h, c);
    }
  }
}

void setup() {
  NovaVGA.init(CS_PIN);

  fillStripes(NovaVGA.Green, NovaVGA.Black, true);

#if !defined(ARDUINO)
  NovaVGA.renderPresent();
#endif
}

void loop() {
  // do nothing
}

#if !defined(ARDUINO)
#include <iostream> // cin, getline()
#include <cstdlib>  // EXIT_SUCCESS
#include <string>   // string

int main(int argc, char *argv[]) {
  std::string s;

  setup();
  loop();
  std::getline(std::cin, s);
  NovaVGA.quit();
  // XXX unreached
  return EXIT_SUCCESS;
}
#endif

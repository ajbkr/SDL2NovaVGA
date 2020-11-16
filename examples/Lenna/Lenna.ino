#include "NovaVGA.h"

#include "lenna.h"

#if !defined(ARDUINO)
#define MANUAL_RENDER_PRESENT true
#endif

#define CS_PIN 10

void setup() {
  int x, y;

#if !defined(ARDUINO)
  NovaVGA.init("Lenna", MANUAL_RENDER_PRESENT, 4);
#else
  NovaVGA.init(CS_PIN);
#endif

  for (y = 0; y < NovaVGA.SCREEN_HEIGHT; ++y) {
    for (x = 0; x < NovaVGA.SCREEN_WIDTH; ++x) {
      NovaVGA.writePixel(x, y, lenna[y * NovaVGA.SCREEN_WIDTH + x]);
    }
  }

#if !defined(ARDUINO) && defined(MANUAL_RENDER_PRESENT)
  NovaVGA.renderPresent();
#endif
}

void loop() {
  // XXX ...

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

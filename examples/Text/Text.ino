#include "NovaVGA.h"

#if !defined(ARDUINO)
#define MANUAL_RENDER_PRESENT false
#define ZOOM_LEVEL 4
#endif

#define CS_PIN 10

#define SCREEN_CHAR_WIDTH  NovaVGA.SCREEN_WIDTH  / NovaVGA.CHAR_WIDTH
#define SCREEN_CHAR_HEIGHT NovaVGA.SCREEN_HEIGHT / NovaVGA.CHAR_HEIGHT

uint8_t row = 0;
uint8_t col = 0;

void setup() {
#if !defined(ARDUINO)
  NovaVGA.init("Text", MANUAL_RENDER_PRESENT, ZOOM_LEVEL);
#else
  NovaVGA.init(CS_PIN);
#endif

  NovaVGA.fillScreen(NovaVGA.Black);

  NovaVGA.drawString("Hello\nWorld", 0, 0, NovaVGA.Green);

  row = NovaVGA.CHAR_HEIGHT * 3;

#if !defined(ARDUINO) && MANUAL_RENDER_PRESENT
  NovaVGA.renderPresent();
#endif
}

void loop() {
  // XXX ...

  // do nothing
}

#if !defined(ARDUINO)
#include <iostream> // cin, getline()
#include <string>   // string

int main() {
  std::string s;

  setup();

  while ( !NovaVGA.shouldQuit()) {
    loop();
    std::getline(std::cin, s);
    NovaVGA.pollEventRun();
  }

  NovaVGA.quit();
  return 0;
}
#endif

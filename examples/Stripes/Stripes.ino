#include "NovaVGA.h"

#if !defined(ARDUINO)
#define MANUAL_RENDER_PRESENT true
#define ZOOM_LEVEL 4
#endif

#define CS_PIN 10

void fillStripes(uint8_t color1, uint8_t color2, bool vertical) {
  uint8_t w, h;
  uint8_t c;
  bool high;

  for (h = 0; h < NovaVGA.SCREEN_HEIGHT; ++h) {
    for (w = 0; w < NovaVGA.SCREEN_WIDTH; ++w) {
      high = vertical ? 0x01 & w : 0x01 & h;
      c = high ? color1 : color2;

      NovaVGA.writePixel(w, h, c);
    }
  }
}

void setup() {
#if !defined(ARDUINO)
  NovaVGA.init("Stripes", MANUAL_RENDER_PRESENT, ZOOM_LEVEL);
#else
  NovaVGA.init(CS_PIN);
#endif

  fillStripes(NovaVGA.Green, NovaVGA.Black, true);

#if !defined(ARDUINO) && MANUAL_RENDER_PRESENT
  NovaVGA.renderPresent();
#endif
}

void loop() {
  // do nothing
}

#if !defined(ARDUINO)
int main() {
  setup();

  while ( !NovaVGA.shouldQuit()) {
    loop();
    NovaVGA.pollEventRun();
  }

  NovaVGA.quit();
  return 0;
}
#endif

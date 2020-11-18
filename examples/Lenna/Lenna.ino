#include "NovaVGA.h"

#include "lenna.h"

#if !defined(ARDUINO)
#define MANUAL_RENDER_PRESENT true
#define ZOOM_LEVEL 4
#endif

#define CS_PIN 10

void setup() {
  int x, y;

#if !defined(ARDUINO)
  NovaVGA.init("Lenna", MANUAL_RENDER_PRESENT, ZOOM_LEVEL);
#else
  NovaVGA.init(CS_PIN);
#endif

  for (y = 0; y < NovaVGA.SCREEN_HEIGHT; ++y) {
    for (x = 0; x < NovaVGA.SCREEN_WIDTH; ++x) {
#if !defined(ARDUINO)
      NovaVGA.writePixel(x, y, lenna[y * NovaVGA.SCREEN_WIDTH + x]);
#else
      NovaVGA.writePixel(x, y, pgm_read_byte(lenna + y * NovaVGA.SCREEN_WIDTH + x));
#endif
    }
  }

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

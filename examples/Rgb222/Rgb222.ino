#include "NovaVGA.h"

#if !defined(ARDUINO)
#define MANUAL_RENDER_PRESENT true
#define ZOOM_LEVEL 4
#endif

#define NUM_COLORS (NovaVGA.MAX_COLOR + 1)
#define PALETTE_HEIGHT 7 * (NUM_COLORS / 4)

#define CS_PIN 10

void setup() {
  uint8_t x, y;
  uint8_t i;

#if !defined(ARDUINO)
  NovaVGA.init("Rgb222", MANUAL_RENDER_PRESENT, ZOOM_LEVEL);
#else
  NovaVGA.init(CS_PIN);
#endif
  NovaVGA.fillScreen(NovaVGA.Black);

  i = 0;
  for (y = 0; y < NUM_COLORS / 4; ++y) {
    for (x = 0; x < 4; ++x) {
      NovaVGA.fillRect(
        x * (NovaVGA.SCREEN_WIDTH / 4),
        4 + y * (PALETTE_HEIGHT / (NUM_COLORS / 4)),
        NovaVGA.SCREEN_WIDTH / 4,
        PALETTE_HEIGHT / (NUM_COLORS / 4),
        i++
      );
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

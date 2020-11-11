#include <iostream> // cin, getline()
#include <cstdlib>  // EXIT_SUCCESS
#include <string>   // string

#include "NovaVGA.h"

#define CS_PIN 10

void setup() {
  NovaVGA.init(CS_PIN);
  NovaVGA.fillScreen(NovaVGA.Black);

  Rect r(0, 0, 10, 10);
  NovaVGA.fillRect(r, NovaVGA.Black);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.Blue);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.Green);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.Cyan);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.Red);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.Magenta);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.Brown);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.LightGray);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.LightMagenta);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.LightBlue);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.LightGreen);
  // ...

  r.left = 60;
  r.top = 0;
  NovaVGA.fillRect(r, NovaVGA.LightCyan);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.LightRed);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.Yellow);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.Gray);
  // ...

  r.top += r.height - 1;
  NovaVGA.fillRect(r, NovaVGA.White);
  // ...

  NovaVGA.writePixel(0, 0, NovaVGA.White);
  NovaVGA.writePixel(NovaVGA.SCREEN_WIDTH - 1, 0, NovaVGA.White);
  NovaVGA.writePixel(NovaVGA.SCREEN_WIDTH - 1, NovaVGA.SCREEN_HEIGHT - 1, NovaVGA.White);
  NovaVGA.writePixel(0, NovaVGA.SCREEN_HEIGHT - 1, NovaVGA.White);

#if !defined(ARDUINO)
  SDL_RenderPresent(NovaVGA.getRenderer());
#endif
}

void loop() {
  // do nothing
}

#if !defined(ARDUINO)
int main(int argc, char *argv[]) {
  std::string s;

  setup();
  //loop();
  std::getline(std::cin, s);
  NovaVGA.close();
  // XXX unreached
  return EXIT_SUCCESS;
}
#endif

#include "NovaVGA.h"

#define CS_PIN 10

#define SCREEN_CHAR_WIDTH  NovaVGA.SCREEN_WIDTH  / NovaVGA.CHAR_WIDTH
#define SCREEN_CHAR_HEIGHT NovaVGA.SCREEN_HEIGHT / NovaVGA.CHAR_HEIGHT

int row = 0;
int col = 0;

void setup() {
#if !defined(ARDUINO)
  NovaVGA.init("Text", false, 4);
#else
  NovaVGA.init(CS_PIN);
#endif

  NovaVGA.fillScreen(NovaVGA.Black);

  NovaVGA.drawString("Hello\nWorld", 0, 0, NovaVGA.Green);

  row = NovaVGA.CHAR_HEIGHT * 3;
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

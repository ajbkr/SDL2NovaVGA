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

  // ...
}

void loop() {
  // do nothing
}

int main(int argc, char *argv[]) {
  std::string s;

  setup();
  //loop();
  std::getline(std::cin, s);
  NovaVGA.close();
  // XXX unreached
  return EXIT_SUCCESS;
}

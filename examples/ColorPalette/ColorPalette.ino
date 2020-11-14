#include "NovaVGA.h"

#define CS_PIN 10

void setup() {
  NovaVGA.init(CS_PIN);
  NovaVGA.fillScreen(NovaVGA.Black);

  Rect r(0, 0, 10, 10);
  NovaVGA.fillRect(r, NovaVGA.Black);
  NovaVGA.drawString("Black", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.Blue);
  NovaVGA.drawString("Blue", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.Green);
  NovaVGA.drawString("Green", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.Cyan);
  NovaVGA.drawString("Cyan", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.Red);
  NovaVGA.drawString("Red", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.Magenta);
  NovaVGA.drawString("Magenta", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.Brown);
  NovaVGA.drawString("Brown", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.LightGray);
  NovaVGA.drawString("LightGray", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.LightMagenta);
  NovaVGA.drawString("LightMagenta", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.LightBlue);
  NovaVGA.drawString("LightBlue", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.LightGreen);
  NovaVGA.drawString("LightGreen", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.left = 60;
  r.top = 0;
  NovaVGA.fillRect(r, NovaVGA.LightCyan);
  NovaVGA.drawString("LightCyan", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.LightRed);
  NovaVGA.drawString("LightRed", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.Yellow);
  NovaVGA.drawString("Yellow", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.Gray);
  NovaVGA.drawString("Gray", r.left + r.width + 3, r.top + 2, NovaVGA.White);

  r.top += r.height + 1;
  NovaVGA.fillRect(r, NovaVGA.White);
  NovaVGA.drawString("White", r.left + r.width + 3, r.top + 2, NovaVGA.White);
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

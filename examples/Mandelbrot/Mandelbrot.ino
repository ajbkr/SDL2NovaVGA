#include "NovaVGA.h"

#define CS_PIN 10

uint8_t mandelbrotPoint(float x, float y) {
  uint8_t iterations = 0;
  float xC;
  float yC;
  float xT;
  float yT;
  float xN, yN;
  float x2, y2;
  float escape_check = 0.0F;

  xC = x;
  yC = y;
  xT = x;
  yT = y;

  while (1) {
    x2 = xT * xT;
    y2 = yT * yT;
    xN = x2 - y2 + xC;
    yN = ((xT * yT) * 2) + yC;
    xT = xN;
    yT = yN;

    ++iterations;
    if (iterations == 63) {
      break;
    }

    escape_check = x2 + y2;
    if (escape_check > 4) {
      break;
    }
  }

  return iterations;
}

void mandelbrotDraw(float center_x, float center_y, float radius) {
  int xpix, ypix;
  float pitch;
  float xcoord, xcoord_min;
  float ycoord;

  pitch = (radius * 2.0F) / NovaVGA.SCREEN_HEIGHT;
  xcoord_min = center_x - radius;
  xcoord = xcoord_min;
  ycoord = center_y - radius;

  for (ypix = 0; ypix < NovaVGA.SCREEN_HEIGHT; ++ypix) {
    for (xpix = 0; xpix < NovaVGA.SCREEN_WIDTH; ++xpix) {
      uint8_t c = mandelbrotPoint(xcoord, ycoord);

      NovaVGA.writePixel(xpix, ypix, c);
      xcoord += pitch;
    }

    ycoord += pitch;
    xcoord = xcoord_min;
  }
}

void setup() {
#if !defined(ARDUINO)
  NovaVGA.init("Mandelbrot", 4);
#else
  NovaVGA.init(CS_PIN);
#endif

  NovaVGA.fillScreen(NovaVGA.Black);

  mandelbrotDraw(-1.0F, 0.0F, 1.0F);
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

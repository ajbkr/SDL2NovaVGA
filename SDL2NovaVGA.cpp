#include <iostream> // cerr, endl

#include "NovaVGA.h" // NovaVGAClass, Point

#include "include/font.h"

static SDL_Renderer *renderer_ = NULL;
static SDL_Surface *surface_ = NULL;
static SDL_Window *window_ = NULL;

NovaVGAClass NovaVGA;

//void NovaVGAClass::init(const String title) {
void NovaVGAClass::init(const char *title) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  if ( (window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL) {
    std::cerr << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  // ...

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

  surface_ = SDL_GetWindowSurface(window_);

  // initialise palette
}

void NovaVGAClass::init(uint8_t cspin) {
  // ignore cspin
  init("SDL2NovaVGA");
}

void NovaVGAClass::close() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void NovaVGAClass::drawChar(const char *bitmap, uint8_t x, uint8_t y, uint8_t color) {
  // ...
}

void NovaVGAClass::drawChar(char ch, uint8_t x, uint8_t y, uint8_t color) {
  // ...
}

void NovaVGAClass::drawChar(char ch, Point p, uint8_t color) {
  // ...
}

//void NovaVGAClass::drawString(const String str, uint8_t x, uint8_t y, uint8_t color) { // XXX String
void NovaVGAClass::drawString(const char *str, uint8_t x, uint8_t y, uint8_t color) {
  // ...
}

//void NovaVGAClass::drawString(const String str, Point p, uint8_t color) { // XXX String
void NovaVGAClass::drawString(const char *str, Point p, uint8_t color) {
  // ...
}

void NovaVGAClass::fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color) {
  // ...
}

void NovaVGAClass::fillRect(Rect r, uint8_t color) {
  // ...
}

void NovaVGAClass::fillScreen(uint8_t color) {
  // ...
}

void NovaVGAClass::writePixel(uint8_t x, uint8_t, uint8_t color) {
  // ...
}

void NovaVGAClass::writePixel(Point p, uint8_t color) {
  // ...
}

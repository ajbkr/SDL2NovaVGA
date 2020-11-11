#include <iostream> // cerr, endl

#include "NovaVGA.h" // NovaVGAClass, Point, Rect

#include "include/font.h"

#define STEP 255 / (4 - 1)

static SDL_Renderer *renderer_ = NULL;
static SDL_Surface *surface_ = NULL;
static SDL_Window *window_ = NULL;

static Uint32 palette_[64];

static void init_rgb222_palette_(const SDL_PixelFormat *format) {
  int r, g, b;
  int i;

  i = 0;
  for (r = 0; r < 4; ++r) {
    for (g = 0; g < 4; ++g) {
      for (b = 0; b < 4; ++b) {
        palette_[i++] = SDL_MapRGB(format, r * STEP, g * STEP, b * STEP);
      }
    }
  }
}

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

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

  surface_ = SDL_GetWindowSurface(window_);

  init_rgb222_palette_(surface_->format);
}

void NovaVGAClass::init(uint8_t cspin) {
  // XXX ignore cspin
  init("SDL2NovaVGA");
}

void NovaVGAClass::close() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

SDL_Renderer *NovaVGAClass::getRenderer() {
  return renderer_;
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
  drawString(str, p.x, p.y, color);
}

void NovaVGAClass::fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color) {
  SDL_Rect rect;
  Uint8 r, g, b;

  SDL_GetRGB(palette_[color & 0x3f], surface_->format, &r, &g, &b);
  SDL_SetRenderDrawColor(renderer_, r, g, b, SDL_ALPHA_OPAQUE);
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  SDL_RenderFillRect(renderer_, &rect);
}

void NovaVGAClass::fillRect(Rect r, uint8_t color) {
  fillRect(r.left, r.top, r.width, r.height, color);
}

void NovaVGAClass::fillScreen(uint8_t color) {
  Uint8 r, g, b;

  SDL_GetRGB(palette_[color & 0x3f], surface_->format, &r, &g, &b);
  SDL_SetRenderDrawColor(renderer_, r, g, b, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_);
}

void NovaVGAClass::writePixel(uint8_t x, uint8_t y, uint8_t color) {
  Uint8 r, g, b;

  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
    return;
  }

  SDL_GetRGB(palette_[color & 0x3f], surface_->format, &r, &g, &b);
  SDL_SetRenderDrawColor(renderer_, r, g, b, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoint(renderer_, x, y);
}

void NovaVGAClass::writePixel(Point p, uint8_t color) {
  writePixel(p.x, p.y, color);
}

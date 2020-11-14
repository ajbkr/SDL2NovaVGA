#include <iostream> // cerr, endl

#include "NovaVGA.h" // NovaVGAClass, Point, Rect
#include "font.h"    // font8x8

#define STEP 255 / (4 - 1)

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

uint8_t NovaVGAClass::cspin_;

SDL_Renderer *NovaVGAClass::renderer_ = NULL;
SDL_Surface *NovaVGAClass::surface_ = NULL;
SDL_Texture *NovaVGAClass::texture_ = NULL;
SDL_Window *NovaVGAClass::window_ = NULL;

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

  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);

  texture_ = SDL_CreateTexture(renderer_, surface_->format->format,
    SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_SetRenderTarget(renderer_, texture_);
}

void NovaVGAClass::init(uint8_t cspin) {
  // XXX unused
  cspin_ = cspin;

  init("SDL2NovaVGA");
}

void NovaVGAClass::quit() {
  SDL_SetRenderTarget(renderer_, NULL);

  SDL_DestroyTexture(texture_);
  texture_ = NULL;

  SDL_DestroyRenderer(renderer_);
  renderer_ = NULL;

  // no SDL_DestroySurface()
  surface_ = NULL;

  SDL_DestroyWindow(window_);
  window_ = NULL;

  SDL_Quit();
}

void NovaVGAClass::renderPresent_() {
  SDL_SetRenderTarget(renderer_, NULL);
  SDL_RenderCopy(renderer_, texture_, NULL, NULL);
  SDL_RenderPresent(renderer_);

  SDL_SetRenderTarget(renderer_, texture_);
}

void NovaVGAClass::drawChar(const char *bitmap, uint8_t x, uint8_t y, uint8_t color) {
  int x2, y2;
  int mask;

  for (y2 = 0; y2 < CHAR_HEIGHT; ++y2) {
    mask = 0x01 << (CHAR_WIDTH - 1);

    for (x2 = 0; x2 < CHAR_WIDTH; ++x2) {
      if (bitmap[y2] & mask) {
        writePixel(x + x2, y + y2, color);
      }

      mask >>= 1;
    }
  }
}

void NovaVGAClass::drawChar(char ch, uint8_t x, uint8_t y, uint8_t color) {
  if (ch < ' ' || ch > 127) {
    return;
  }

  drawChar(((const char *) &font8x8[(ch - ' ') * CHAR_HEIGHT]), x, y, color);
}

void NovaVGAClass::drawChar(char ch, Point p, uint8_t color) {
  drawChar(ch, p.x, p.y, color);
}

//void NovaVGAClass::drawString(const String str, uint8_t x, uint8_t y, uint8_t color) { // XXX String
void NovaVGAClass::drawString(const char *str, uint8_t x, uint8_t y, uint8_t color) {
  int i;

  i = 0;
  while (str[i] != '\0') {
    drawChar(str[i], x + i * CHAR_WIDTH, y, color);
    ++i;
  }
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

  renderPresent_();
}

void NovaVGAClass::fillRect(Rect r, uint8_t color) {
  fillRect(r.left, r.top, r.width, r.height, color);
}

void NovaVGAClass::fillScreen(uint8_t color) {
  Uint8 r, g, b;

  SDL_GetRGB(palette_[color & 0x3f], surface_->format, &r, &g, &b);
  SDL_SetRenderDrawColor(renderer_, r, g, b, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_);

  renderPresent_();
}

void NovaVGAClass::writePixel(uint8_t x, uint8_t y, uint8_t color) {
  Uint8 r, g, b;

  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
    return;
  }

  SDL_GetRGB(palette_[color & 0x3f], surface_->format, &r, &g, &b);
  SDL_SetRenderDrawColor(renderer_, r, g, b, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoint(renderer_, x, y);

  renderPresent_();
}

void NovaVGAClass::writePixel(Point p, uint8_t color) {
  writePixel(p.x, p.y, color);
}

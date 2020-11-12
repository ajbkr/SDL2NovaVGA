#include <iostream> // cerr, endl

#include "NovaVGA.h" // NovaVGAClass, Point, Rect

#define STEP 255 / (4 - 1)

static const Uint8 font8x8_[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*   */
  0x18, 0x3c, 0x3c, 0x18, 0x18, 0x00, 0x18, 0x00, /* ! */
  0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* " */
  0x36, 0x36, 0x7f, 0x36, 0x7f, 0x36, 0x36, 0x00, /* # */
  0x0c, 0x3e, 0x03, 0x1e, 0x30, 0x1f, 0x0c, 0x00, /* $ */
  0x00, 0x63, 0x33, 0x18, 0x0c, 0x66, 0x63, 0x00, /* % */
  0x1c, 0x36, 0x1c, 0x6e, 0x3b, 0x33, 0x6e, 0x00, /* & */
  0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, /* ' */
  0x18, 0x0c, 0x06, 0x06, 0x06, 0x0c, 0x18, 0x00, /* ( */
  0x06, 0x0c, 0x18, 0x18, 0x18, 0x0c, 0x06, 0x00, /* ) */
  0x00, 0x66, 0x3c, 0xff, 0x3c, 0x66, 0x00, 0x00, /* * */
  0x00, 0x0c, 0x0c, 0x3f, 0x0c, 0x0c, 0x00, 0x00, /* + */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x06, /* , */
  0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, /* - */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, /* . */
  0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x00, /* / */
  0x3e, 0x63, 0x73, 0x7b, 0x6f, 0x67, 0x3e, 0x00, /* 0 */
  0x0c, 0x0e, 0x0c, 0x0c, 0x0c, 0x0c, 0x3f, 0x00, /* 1 */
  0x1e, 0x33, 0x30, 0x1c, 0x06, 0x33, 0x3f, 0x00, /* 2 */
  0x1e, 0x33, 0x30, 0x1c, 0x30, 0x33, 0x1e, 0x00, /* 3 */
  0x38, 0x3c, 0x36, 0x33, 0x7f, 0x30, 0x78, 0x00, /* 4 */
  0x3f, 0x03, 0x1f, 0x30, 0x30, 0x33, 0x1e, 0x00, /* 5 */
  0x1c, 0x06, 0x03, 0x1f, 0x33, 0x33, 0x1e, 0x00, /* 6 */
  0x3f, 0x33, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x00, /* 7 */
  0x1e, 0x33, 0x33, 0x1e, 0x33, 0x33, 0x1e, 0x00, /* 8 */
  0x1e, 0x33, 0x33, 0x3e, 0x30, 0x18, 0x0e, 0x00, /* 9 */
  0x00, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x0c, 0x00, /* : */
  0x00, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x0c, 0x06, /* / */
  0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x00, /* < */
  0x00, 0x00, 0x3f, 0x00, 0x00, 0x3f, 0x00, 0x00, /* = */
  0x06, 0x0c, 0x18, 0x30, 0x18, 0x0c, 0x06, 0x00, /* > */
  0x1e, 0x33, 0x30, 0x18, 0x0c, 0x00, 0x0c, 0x00, /* ? */
  0x3e, 0x63, 0x7b, 0x7b, 0x7b, 0x03, 0x1e, 0x00, /* @ */
  0x0c, 0x1e, 0x33, 0x33, 0x3f, 0x33, 0x33, 0x00, /* A */
  0x3f, 0x66, 0x66, 0x3e, 0x66, 0x66, 0x3f, 0x00, /* B */
  0x3c, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3c, 0x00, /* C */
  0x1f, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1f, 0x00, /* D */
  0x7f, 0x46, 0x16, 0x1e, 0x16, 0x46, 0x7f, 0x00, /* E */
  0x7f, 0x46, 0x16, 0x1e, 0x16, 0x06, 0x0f, 0x00, /* F */
  0x3c, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7c, 0x00, /* G */
  0x33, 0x33, 0x33, 0x3f, 0x33, 0x33, 0x33, 0x00, /* H */
  0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x1e, 0x00, /* I */
  0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1e, 0x00, /* J */
  0x67, 0x66, 0x36, 0x1e, 0x36, 0x66, 0x67, 0x00, /* K */
  0x0f, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7f, 0x00, /* L */
  0x63, 0x77, 0x7f, 0x7f, 0x6b, 0x63, 0x63, 0x00, /* M */
  0x63, 0x67, 0x6f, 0x7b, 0x73, 0x63, 0x63, 0x00, /* N */
  0x1c, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1c, 0x00, /* O */
  0x3f, 0x66, 0x66, 0x3e, 0x06, 0x06, 0x0f, 0x00, /* P */
  0x1e, 0x33, 0x33, 0x33, 0x3b, 0x1e, 0x38, 0x00, /* Q */
  0x3f, 0x66, 0x66, 0x3e, 0x36, 0x66, 0x67, 0x00, /* R */
  0x1e, 0x33, 0x07, 0x0e, 0x38, 0x33, 0x1e, 0x00, /* S */
  0x3f, 0x2d, 0x0c, 0x0c, 0x0c, 0x0c, 0x1e, 0x00, /* T */
  0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f, 0x00, /* U */
  0x33, 0x33, 0x33, 0x33, 0x33, 0x1e, 0x0c, 0x00, /* V */
  0x63, 0x63, 0x63, 0x6b, 0x7f, 0x77, 0x63, 0x00, /* W */
  0x63, 0x63, 0x36, 0x1c, 0x1c, 0x36, 0x63, 0x00, /* X */
  0x33, 0x33, 0x33, 0x1e, 0x0c, 0x0c, 0x1e, 0x00, /* Y */
  0x7f, 0x63, 0x31, 0x18, 0x4c, 0x66, 0x7f, 0x00, /* Z */
  0x1e, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1e, 0x00, /* [ */
  0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x40, 0x00, /* \ */
  0x1e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1e, 0x00, /* ] */
  0x08, 0x1c, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00, /* ^ */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, /* _ */
  0x0c, 0x0c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, /* ` */
  0x00, 0x00, 0x1e, 0x30, 0x3e, 0x33, 0x6e, 0x00, /* a */
  0x07, 0x06, 0x06, 0x3e, 0x66, 0x66, 0x3b, 0x00, /* b */
  0x00, 0x00, 0x1e, 0x33, 0x03, 0x33, 0x1e, 0x00, /* c */
  0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6e, 0x00, /* d */
  0x00, 0x00, 0x1e, 0x33, 0x3f, 0x03, 0x1e, 0x00, /* e */
  0x1c, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0f, 0x00, /* f */
  0x00, 0x00, 0x6e, 0x33, 0x33, 0x3e, 0x30, 0x1e, /* g */
  0x07, 0x06, 0x36, 0x6e, 0x66, 0x66, 0x67, 0x00, /* h */
  0x0c, 0x00, 0x0e, 0x0c, 0x0c, 0x0c, 0x1e, 0x00, /* i */
  0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1e, /* j */
  0x07, 0x06, 0x66, 0x36, 0x1e, 0x36, 0x67, 0x00, /* k */
  0x0e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x1e, 0x00, /* l */
  0x00, 0x00, 0x33, 0x7f, 0x7f, 0x6b, 0x63, 0x00, /* m */
  0x00, 0x00, 0x1f, 0x33, 0x33, 0x33, 0x33, 0x00, /* n */
  0x00, 0x00, 0x1e, 0x33, 0x33, 0x33, 0x1e, 0x00, /* o */
  0x00, 0x00, 0x3b, 0x66, 0x66, 0x3e, 0x06, 0x0f, /* p */
  0x00, 0x00, 0x6e, 0x33, 0x33, 0x3e, 0x30, 0x78, /* q */
  0x00, 0x00, 0x3b, 0x6e, 0x66, 0x06, 0x0F, 0x00, /* r */
  0x00, 0x00, 0x3e, 0x03, 0x1e, 0x30, 0x1f, 0x00, /* s */
  0x08, 0x0c, 0x3e, 0x0c, 0x0c, 0x2c, 0x18, 0x00, /* t */
  0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6e, 0x00, /* u */
  0x00, 0x00, 0x33, 0x33, 0x33, 0x1e, 0x0c, 0x00, /* v */
  0x00, 0x00, 0x63, 0x6b, 0x7f, 0x7f, 0x36, 0x00, /* w */
  0x00, 0x00, 0x63, 0x36, 0x1c, 0x36, 0x63, 0x00, /* x */
  0x00, 0x00, 0x33, 0x33, 0x33, 0x3e, 0x30, 0x1f, /* y */
  0x00, 0x00, 0x3f, 0x19, 0x0c, 0x26, 0x3f, 0x00, /* z */
  0x38, 0x0c, 0x0c, 0x07, 0x0c, 0x0c, 0x38, 0x00, /* { */
  0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00, /* | */
  0x07, 0x0c, 0x0c, 0x38, 0x0c, 0x0c, 0x07, 0x00, /* } */
  0x6e, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ~ */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  /*   */
};

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
  int x2, y2;
  int mask;

  for (y2 = 0; y2 < CHAR_HEIGHT; ++y2) {
    //mask = 0x01 << (CHAR_WIDTH - 1);
    mask = 0x01;

    for (x2 = 0; x2 < CHAR_WIDTH; ++x2) {
      if (bitmap[y2] & mask) {
        writePixel(x + x2, y + y2, color);
      }

      //mask >>= 1;
      mask <<= 1;
    }
  }
}

void NovaVGAClass::drawChar(char ch, uint8_t x, uint8_t y, uint8_t color) {
  if (ch < ' ' || ch > 127) {
    return;
  }

  drawChar(((const char *) &font8x8_[(ch - ' ') * CHAR_HEIGHT]), x, y, color);
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

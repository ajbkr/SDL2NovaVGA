#ifndef NOVAVGA_H_
#define NOVAVGA_H_

#include "SDL2/SDL.h" // SDL_PixelFormat, SDL_Renderer, SDL_Surface,
                      // SDL_Texture, SDL_Window

struct Point {
  char x;
  char y;

  Point(const char x = 0, const char y = 0) {
    this->x = x;
    this->y = y;
  }

  Point& operator=(const Point& p) {
    x = p.x;
    y = p.y;

    return *this;
  }

  bool operator==(const Point& p) const {
    return x == p.x && y == p.y;
  }

  Point operator+(const Point& p) const {
    return Point(p.x + x, p.y + y);
  }

  Point operator-(const Point& p) const {
    return Point(p.x - x, p.y - y);
  }
};

struct Rect {
  char top; // [sic]
  char left;
  char width;
  char height;

  Rect(const char x = 0, const char y = 0, const char w = 0, const char h = 0) {
    left = x;
    top = y;
    width = w;
    height = h;
  }

  Rect& operator=(const Rect& r) {
    left = r.left;
    top = r.top;
    width = r.width;
    height = r.height;

    return *this;
  }

  bool operator==(const Rect& r) const {
    return left == r.left && top == r.top && width == r.width && height == r.height;
  }

  Rect operator+(const Rect& r) const {
    return Rect(r.left + left, r.top + top, r.width + width, r.height + height);
  }

  Rect operator-(const Rect& r) const {
    return Rect(r.left - left, r.top - top, r.width - width, r.height - height);
  }
};

class NovaVGAClass {
  private:
    static uint32_t palette_[]; // extension
    static uint8_t cspin_;

    static SDL_Renderer *renderer_; // extension
    static SDL_Surface *surface_;   // extension
    static SDL_Texture *texture_;   // extension
    static SDL_Window *window_;     // extension

    static void drawChar(const char *bitmap, uint8_t x, uint8_t y, uint8_t color);
    static void initRgb222Palette_(const SDL_PixelFormat *format); // extension
    static void renderPresent_();                                  // extension

  public:
    static const uint8_t SCREEN_WIDTH  = 160;
    static const uint8_t SCREEN_HEIGHT = 120;

    static const uint8_t CHAR_WIDTH  = 8;
    static const uint8_t CHAR_HEIGHT = 8;

    static const uint8_t Black        = 0x00;
    static const uint8_t Blue         = 0x02;
    static const uint8_t Green        = 0x08;
    static const uint8_t Cyan         = 0x0a;
    static const uint8_t Red          = 0x20;
    static const uint8_t Magenta      = 0x22;
    static const uint8_t Brown        = 0x24;
    static const uint8_t LightGray    = 0x2a;
    static const uint8_t Gray         = 0x15;
    static const uint8_t LightBlue    = 0x17;
    static const uint8_t LightGreen   = 0x1d;
    static const uint8_t LightCyan    = 0x1f;
    static const uint8_t LightRed     = 0x25;
    static const uint8_t LightMagenta = 0x37;
    static const uint8_t Yellow       = 0x3d;
    static const uint8_t White        = 0x3f;

    static const uint8_t Orange       = 0x34;
    static const uint8_t None         = 0xff;

    //static void init(const String title);
    static void init(const char *title);
    static void init(uint8_t cspin);
    static void quit(); // extension

    static void drawChar(char ch, uint8_t x, uint8_t y, uint8_t color);
    static void drawChar(char ch, Point p, uint8_t color);
    //static void drawString(const String str, uint8_t x, uint8_t y, uint8_t color); // XXX String
    static void drawString(const char *str, uint8_t x, uint8_t y, uint8_t color);
    //static void drawString(const String str, Point p, uint8_t color); // XXX String
    static void drawString(const char *str, Point p, uint8_t color);
    static void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
    static void fillRect(Rect r, uint8_t color);
    static void fillScreen(uint8_t color);
    static void writePixel(uint8_t x, uint8_t y, uint8_t color);
    static void writePixel(Point p, uint8_t color);
};

extern NovaVGAClass NovaVGA;

#endif

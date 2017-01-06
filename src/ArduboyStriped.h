#ifndef ArduboyStriped_h
#define ArduboyStriped_h

#include "core/core.h"
#include <SPI.h>
#include <Print.h>
#include <limits.h>

/// Library version.
/**
 * A version number, 'x.y.z', is stored in the form xxyyzz,
 * where ((x * 10000) + (y * 100) + (z)),
 * resulting in 'xxxyyzz', with no leading zeros.
 */
#define ARDUBOY_LIB_VER 20000 // 2.0.0

// EEPROM settings
#define EEPROM_VERSION 0
#define EEPROM_BRIGHTNESS 1
#define EEPROM_AUDIO_ON_OFF 2

// we reserve the first 16 byte of EEPROM for system use
#define EEPROM_STORAGE_SPACE_START 16 // and onward

// eeprom settings above are neded for audio
#include "audio/audio.h"

#define PIXEL_SAFE_MODE

// compare Vcc to 1.1 bandgap
#define ADC_VOLTAGE (_BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1))
// compare temperature to 2.5 internal reference and _BV(MUX5)
#define ADC_TEMP (_BV(REFS0) | _BV(REFS1) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0))

class Arduboy : public ArduboyCore
{
public:
  Arduboy();

  /// Returns true if the button mask passed in is pressed.
  /**
   * if (pressed(LEFT_BUTTON + A_BUTTON))
   */
  boolean pressed(uint8_t buttons);

  /// Returns true if the button mask passed in not pressed.
  /**
   * if (notPressed(LEFT_BUTTON))
   */
  boolean notPressed(uint8_t buttons);

  /// Initializes the hardware
  void beginNoLogo();

  /// Boot utils such as flashlight, etc
  void inline bootUtils() __attribute__((always_inline));
    
  /// Use in loop like: while(arduboy.needsStripe()) { ...; arduboy.displayStripe(); }
  bool needsStripe();

  
  /// Clears current stripe.
  void clearStripe();
  
  /// Displays one horizontal stripe, call this 8 times to paint the entire screen.
  /**
   * X and Y positions on the display are from the top left corner, thus a Y of 64
   * is the bottom of the screen and an X of 128 is the right side of the screen.
   * "Color" or "value" means choosing whether a pixel is lit or not - if color is
   * 0, the pixel is off (black), if color is 1, the pixel is on (white).
   */    
  void displayStripe();

  /// Checks if some y-coordinate intersects the current stripe.
  bool intersectsStripe(int y);

  /// Checks if a character drawn at some y-coordinate would intersect the current stripe.
  bool charIntersectsStripe(int y, uint8_t size);

  /// Checks if a small character drawn at some y-coordinate would intersect the current stripe.
  bool smallCharIntersectsStripe(int y);
  
  /// Sets a single pixel on the screen stripe buffer to white or black.
  void drawPixel(int x, int y, uint8_t color);

  /// Draw a circle of a defined radius, call multiple times for drawing across stripes.
  /**
   * Draws a circle in white or black. X and Y are the center point of the circle.
   */
  void drawCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color);

  /// Draws one or more "corners" of a circle, call multiple times for drawing across stripes.
  void drawCircleHelper(int16_t x0, int16_t y0, uint8_t r, uint8_t cornername, uint8_t color);

  /// Draws a filled-in circle, call multiple times for drawing across stripes.
  void fillCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color);

   /// Draws one or both vertical halves of a filled-in circle, call multiple times for drawing across stripes.
  void fillCircleHelper(int16_t x0, int16_t y0, uint8_t r, uint8_t cornername, int16_t delta, uint8_t color);

  /// Draws a line between two points, call multiple times for drawing across stripes.
  /**
   * Uses Bresenham's algorithm.
   */
  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);

  /// Draws a rectangle of a width and height, call multiple times for drawing across stripes.
  void drawRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color);

  /// Draws vertical line, call multiple times for drawing across stripes.
  void drawFastVLine(int16_t x, int16_t y, uint8_t h, uint8_t color);

  /// Draws a horizontal line, call only when needed for current stripe.
  void drawFastHLine(int16_t x, int16_t y, uint8_t w, uint8_t color);

  /// Draws a filled-in rectangle, call multiple times for drawing across stripes.
  void fillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color);

  /// Fills current stripe with single color.
  void fillStripe(uint8_t color);
  
  /// Draws a rectangle with rounded edges, call multiple times for drawing across stripes.
  void drawRoundRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t r, uint8_t color);

  /// Draws a filled-in rectangle with rounded edges, call multiple times for drawing across stripes.
  void fillRoundRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t r, uint8_t color);

   /// Draws the outline of a triangle, call multiple times for drawing across stripes.
  void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color);

  /// Draws a filled-in triangle, call multiple times for drawing across stripes.
  void fillTriangle (int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color);

  /// Draws images that are bit-oriented horizontally, call multiple times for drawing across stripes.
  /**
   * This requires a lot of additional CPU power and will draw images slower
   * than drawBitmap, where the images are stored in a format that
   * allows them to be directly written to the screen. It is
   * recommended you use drawBitmap when possible.
   */
  void drawSlowXYBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color);

  /// Draws an ASCII character at a point, call multiple times for drawing across stripes.
  void drawChar(int16_t x, int16_t y, unsigned char c, uint8_t color, uint8_t bg, uint8_t size);

  /// Draws an ASCII character with smallest size, call multiple times for drawing across stripes.
  void drawSmallChar(int16_t x, int16_t y, unsigned char c, uint8_t color, uint8_t bg);
  
  unsigned char* getBuffer();

  /// Seeds the random number generator with entropy from the temperature, voltage reading, and microseconds since boot.
  /**
   * This method is still most effective when called semi-randomly such
   * as after a user hits a button to start a game or other semi-random
   * events
   */
  void initRandomSeed();

  /// Swap the references of two pointers.
  void swap(int16_t& a, int16_t& b);

  ArduboyTunes tunes;
  ArduboyAudio audio;

  void setFrameRate(uint8_t rate);
  bool nextFrame();
  bool everyXFrames(uint8_t frames);
  
  /// Returns the load on the CPU as a percentage.
  /**
   * This is based on how much of the time your app is spends rendering
   * frames.  This number can be higher than 100 if your app is rendering
   * really slowly.
   */
  int cpuLoad();
  
  uint8_t frameRate;
  uint16_t frameCount;
  uint8_t eachFrameMillis;
  long lastFrameStart;
  long nextFrameStart;
  bool post_render;
  uint8_t lastFrameDurationMs;

  uint8_t currStripeStartY;
  
  /// useful for getting raw approximate voltage values
  uint16_t rawADC(byte adc_bits);

protected:
  unsigned char sBuffer[WIDTH];

};

#endif

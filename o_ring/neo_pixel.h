#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_COUNT 158
#define NEOPIXEL_PIN   13

class NeoPixel {
  public:
    NeoPixel(int count, int pin, NEO_GRB + NEO_KHZ800);
    ~NeoPixel();
};

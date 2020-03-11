#include "o_ring.h"

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  pinMode(mprA.irqpin, INPUT);
  digitalWrite(mprA.irqpin, HIGH); //enable pullup resistor

  pinMode(mprB.irqpin, INPUT);
  digitalWrite(mprB.irqpin, HIGH); //enable pullup resistor

  pinMode(mprC.irqpin, INPUT);
  digitalWrite(mprC.irqpin, HIGH); //enable pullup resistor

  pinMode(mprD.irqpin, INPUT);
  digitalWrite(mprD.irqpin, HIGH); //enable pullup resistor

  strip = Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
}

void loop() {
  mprA.readTouchInputs();
  mprB.readTouchInputs();
  mprC.readTouchInputs();
  mprD.readTouchInputs();

  for (int i = 0; i < NEOPIXEL_COUNT; i++) {
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(map(i, 0, NEOPIXEL_COUNT, 0, 65535), 255, 255)));

    while (1) {
      if (strip.canShow()) {
        strip.show();
        break;
      }
    }
  }
}

/*********************************************************
  This is a library for the MPR121 12-channel Capacitive touch sensor

  Designed specifically to work with the MPR121 Breakout in the Adafruit shop
  ----> https://www.adafruit.com/products/

  These sensors use I2C communicate, at least 2 pins are required
  to interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_COUNT 158
#define NEOPIXEL_PIN   13
#define TOUCHPT_COUNT  48

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 capA = Adafruit_MPR121();
Adafruit_MPR121 capB = Adafruit_MPR121();
Adafruit_MPR121 capC = Adafruit_MPR121();
Adafruit_MPR121 capD = Adafruit_MPR121();

Adafruit_NeoPixel strip;

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouchedA = 0;
uint16_t currtouchedA = 0;
uint16_t lasttouchedB = 0;
uint16_t currtouchedB = 0;
uint16_t lasttouchedC = 0;
uint16_t currtouchedC = 0;
uint16_t lasttouchedD = 0;
uint16_t currtouchedD = 0;

bool touchArray[TOUCHPT_COUNT] = {false};

void setup() {
  Serial.begin(9600);
  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(100);
  }

  strip = Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
  Serial.println("Adafruit Neopixel is on!");

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!capA.begin(0x5A)) {
    Serial.println("MPR121:A not found, check wiring?");
    while (1);
  }
  if (!capB.begin(0x5B)) {
    Serial.println("MPR121:B not found, check wiring?");
    while (1);
  }
  if (!capC.begin(0x5C)) {
    Serial.println("MPR121:C not found, check wiring?");
    while (1);
  }
  if (!capD.begin(0x5D)) {
    Serial.println("MPR121:D not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121s found!");

  for (uint8_t i = 0; i < NEOPIXEL_COUNT; i++) {
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(map(i, 0, NEOPIXEL_COUNT,
                                         map(300, 0, 360, 0, 65535), map(50, 0, 360, 0, 65535)) % 65535,
                                         255, 255)));
  }
}

void loop() {
  // Get the currently touched pads
  currtouchedA = capA.touched();
  currtouchedB = capB.touched();
  currtouchedC = capC.touched();
  currtouchedD = capD.touched();

  updateTouched();
  updateReleased();
  printTouchArrayLn();

  //strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(0, 0, 0)));

  while (1) {
    if (strip.canShow()) {
      strip.show();
      break;
    }
  }

  lasttouchedA = currtouchedA;
  lasttouchedB = currtouchedB;
  lasttouchedC = currtouchedC;
  lasttouchedD = currtouchedD;

  return;
}

void updateTouched() {
  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedA & _BV(i)) && !(lasttouchedA & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
      touchArray[i] = true;
    }
  }
  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedB & _BV(i)) && !(lasttouchedB & _BV(i)) ) {
      Serial.print(12 + i); Serial.println(" touched");
      touchArray[12 + i] = true;
    }
  }
  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedC & _BV(i)) && !(lasttouchedC & _BV(i)) ) {
      Serial.print(24 + i); Serial.println(" touched");
      touchArray[24 + i] = true;
    }
  }
  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedD & _BV(i)) && !(lasttouchedD & _BV(i)) ) {
      Serial.print(36 + i); Serial.println(" touched");
      touchArray[36 + i] = true;
    }
  }
}

void updateReleased() {
  for (uint8_t i = 0; i < 12; i++) {
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouchedA & _BV(i)) && (lasttouchedA & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
      touchArray[i] = false;
    }

    // if it *was* touched and now *isnt*, alert!
    if (!(currtouchedB & _BV(i)) && (lasttouchedB & _BV(i)) ) {
      Serial.print(12 + i); Serial.println(" released");
      touchArray[12 + i] = false;
    }

    // if it *was* touched and now *isnt*, alert!
    if (!(currtouchedC & _BV(i)) && (lasttouchedC & _BV(i)) ) {
      Serial.print(24 + i); Serial.println(" released");
      touchArray[24 + i] = false;
    }

    // if it *was* touched and now *isnt*, alert!
    if (!(currtouchedD & _BV(i)) && (lasttouchedD & _BV(i)) ) {
      Serial.print(36 + i); Serial.println(" released");
      touchArray[36 + i] = false;
    }
  }
}

void printTouchArrayLn() {
  for (uint8_t i = 0; i < TOUCHPT_COUNT; i++) {
    if (touchArray[i]) {
      Serial.print(i);
      Serial.print(" ");
    } else {
      Serial.print("-1 ");
    }
  }
  Serial.println();
}

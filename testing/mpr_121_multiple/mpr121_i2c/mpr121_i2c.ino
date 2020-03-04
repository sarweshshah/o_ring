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

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 capA = Adafruit_MPR121();
Adafruit_MPR121 capB = Adafruit_MPR121();
Adafruit_MPR121 capC = Adafruit_MPR121();
Adafruit_MPR121 capD = Adafruit_MPR121();

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

void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(100);
  }
  
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
}

void loop() {
  // Get the currently touched pads
  currtouchedA = capA.touched();
  currtouchedB = capB.touched();
  currtouchedC = capC.touched();
  currtouchedD = capD.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedA & _BV(i)) && !(lasttouchedA & _BV(i)) ) {
      Serial.print(1 + i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouchedA & _BV(i)) && (lasttouchedA & _BV(i)) ) {
      Serial.print(1 + i); Serial.println(" released");
    }
  }

  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedB & _BV(i)) && !(lasttouchedB & _BV(i)) ) {
      Serial.print(1 + 12 + i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouchedB & _BV(i)) && (lasttouchedB & _BV(i)) ) {
      Serial.print(1 + 12 + i); Serial.println(" released");
    }
  }

  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedC & _BV(i)) && !(lasttouchedC & _BV(i)) ) {
      Serial.print(1 + 24 + i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouchedC & _BV(i)) && (lasttouchedC & _BV(i)) ) {
      Serial.print(1 + 24 + i); Serial.println(" released");
    }
  }

  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedD & _BV(i)) && !(lasttouchedD & _BV(i)) ) {
      Serial.print(1 + 36 + i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouchedD & _BV(i)) && (lasttouchedD & _BV(i)) ) {
      Serial.print(1 + 36 + i); Serial.println(" released");
    }
  }
  
  lasttouchedA = currtouchedA;
  lasttouchedB = currtouchedB;
  lasttouchedC = currtouchedC;
  lasttouchedD = currtouchedD;

  return;
}

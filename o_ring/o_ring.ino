#include "o_ring.h"

void setup() {
  pinMode(mprA.irqpin, INPUT);
  digitalWrite(mprA.irqpin, HIGH); //enable pullup resistor

  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  mprA.readTouchInputs();
}

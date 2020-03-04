#include <Arduino.h>
#include <Wire.h>
#include "constants.h"

class MPR_121 {
 private:
  void set_register(int, unsigned char, unsigned char);
  bool checkInterrupt();

 public:
  int irqpin;
  int address;
  bool touchStates[12];

  MPR_121(int);
  ~MPR_121();
  void readTouchInputs();
};

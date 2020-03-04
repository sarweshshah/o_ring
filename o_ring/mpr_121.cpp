#include "mpr_121.h"

void MPR_121::set_register(int address, unsigned char r, unsigned char v) {
  Wire.beginTransmission(address);
  Wire.write(r);
  Wire.write(v);
  Wire.endTransmission();
}

bool MPR_121::checkInterrupt() {
  return digitalRead(this->irqpin);
}

MPR_121::MPR_121(int _address) {
  this->address = _address;
  set_register(this->address, ELE_CFG, 0x00);

  // Section A - Controls filtering when data is > baseline.
  set_register(this->address, MHD_R, 0x01);
  set_register(this->address, NHD_R, 0x01);
  set_register(this->address, NCL_R, 0x00);
  set_register(this->address, FDL_R, 0x00);

  // Section B - Controls filtering when data is < baseline.
  set_register(this->address, MHD_F, 0x01);
  set_register(this->address, NHD_F, 0x01);
  set_register(this->address, NCL_F, 0xFF);
  set_register(this->address, FDL_F, 0x02);

  // Section C - Sets touch and release thresholds for each electrode
  set_register(this->address, ELE0_T, TOU_THRESH);
  set_register(this->address, ELE0_R, REL_THRESH);

  set_register(this->address, ELE1_T, TOU_THRESH);
  set_register(this->address, ELE1_R, REL_THRESH);

  set_register(this->address, ELE2_T, TOU_THRESH);
  set_register(this->address, ELE2_R, REL_THRESH);

  set_register(this->address, ELE3_T, TOU_THRESH);
  set_register(this->address, ELE3_R, REL_THRESH);

  set_register(this->address, ELE4_T, TOU_THRESH);
  set_register(this->address, ELE4_R, REL_THRESH);

  set_register(this->address, ELE5_T, TOU_THRESH);
  set_register(this->address, ELE5_R, REL_THRESH);

  set_register(this->address, ELE6_T, TOU_THRESH);
  set_register(this->address, ELE6_R, REL_THRESH);

  set_register(this->address, ELE7_T, TOU_THRESH);
  set_register(this->address, ELE7_R, REL_THRESH);

  set_register(this->address, ELE8_T, TOU_THRESH);
  set_register(this->address, ELE8_R, REL_THRESH);

  set_register(this->address, ELE9_T, TOU_THRESH);
  set_register(this->address, ELE9_R, REL_THRESH);

  set_register(this->address, ELE10_T, TOU_THRESH);
  set_register(this->address, ELE10_R, REL_THRESH);

  set_register(this->address, ELE11_T, TOU_THRESH);
  set_register(this->address, ELE11_R, REL_THRESH);

  // Section D
  // Set the Filter Configuration
  // Set ESI2
  set_register(this->address, FIL_CFG, 0x04);

  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  set_register(this->address, ELE_CFG, 0x0C);  // Enables all 12 Electrodes

  // Section F
  // Enable Auto Config and auto Reconfig
  //  set_register(this->address , ATO_CFG0, 0x0B);
  //  set_register(this->address , ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V
  //  set_register(this->address , ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  //  set_register(this->address , ATO_CFGT, 0xB5);
  // Target = 0.9*USL = 0xB5 @3.3V

  set_register(this->address, ELE_CFG, 0x0C);
}

void MPR_121::readTouchInputs() {
  if (!this->checkInterrupt()) {
    Wire.requestFrom(0x5A, 2);
    byte LSB = Wire.read();
    byte MSB = Wire.read();

    uint16_t touched =
      ((MSB << 8) | LSB);  // 16bits that make up the touch states

    for (int i = 0; i < 12; i++) {
      if (touched & (1 << i)) {
        if (this->touchStates[i] == 0) {
          // pin i was just touched
          Serial.print("pin ");
          Serial.print(i);
          Serial.println(" was just touched");
        }
        // else if (touchStates[i] == 1)//{pin i is still being touched}
        this->touchStates[i] = 1;
      } else {
        if (this->touchStates[i] == 1) {
          Serial.print("pin ");
          Serial.print(i);
          Serial.println(" is no longer being touched");
        }
        this->touchStates[i] = 0;
      }
    }
  }
}

MPR_121::~MPR_121() {}

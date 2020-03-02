# o_ring
 Ardunio based code for implementing gesture based interaction using capactive touch sensors.
 O-Ring architecture consists of many phases and components that care described below.
 
 Components used in the system:
 1. 4 x MPR121 Capacitive Touch Sensor
 2. 1 x Arduino Uno
 3. 4 x 5m single core wires
 
### Phase II: Interacting with MPR121 touch sensor
Once we have tested our hardware with TTP223 capacitive touch sensor we wanted to explore a system with more touch points. Hence, MPR121 was used as they provide 12 touch points on a since pin in Arduino.
Testing that with Ardiuno can be done using the example code in MPR library in the Arduino IDE.

### Phase II: Connecting multiple MPR121 touch sensors using i2c protocol
Using i2c communication, we can attach upto 4 MPR sensors with one Arduino chip. This is done using a 12 bit address system which both MPR sensor and Arduinos come programmed with. The underlying architecture is a classic master slave communication. 
The default address of an MPR sensor is usually **0x5A** (though one must consult the datasheet for that) and can be changed to either **0x5B, 0x5C** or **0x5D** depending on the which pin connects with the **ADD** pin of the sensor.

- ADDR not connected: 0x5A
- ADDR tied to 3V: 0x5B
- ADDR tied to SDA: 0x5C
- ADDR tied to SCL: 0x5D

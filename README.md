# o_ring
 Arduino based code for implementing gesture-based interaction using capacitive touch sensors.
 O-Ring architecture consists of many phases and components that are described below.
 
 Components used in the system:
 1. 4 x MPR121 Capacitive Touch Sensor
 2. 1 x Arduino Uno
 3. 4 x 5m single-core wires

![Arduino Uno](https://github.com/sarweshshah/o_ring/blob/master/images/Arduino%20Uno.jpg) ![MPR121](https://github.com/sarweshshah/o_ring/blob/master/images/MPR121.JPG)
 
### Phase II: Interacting with MPR121 touch sensor
Once we have tested our hardware with TTP223 capacitive touch sensor we wanted to explore a system with more touchpoints. Hence, MPR121 was used as they provide 12 touchpoints on a since pin in Arduino.
Testing that with Arduino can be done using the example code in MPR library in the Arduino IDE.

### Phase III: Connecting multiple MPR121 touch sensors using i2c protocol
Using i2c communication, we can attach up to 4 MPR sensors with one Arduino chip. This is done using a 12-bit address system which both MPR sensor and Arduinos come programmed with. The underlying architecture is a classic master-slave communication. 
The default address of an MPR sensor is usually **0x5A** (though one must consult the datasheet for that) and can be changed to either **0x5B, 0x5C** or **0x5D** depending on the which pin connects with the **ADD** pin of the sensor.

- ADDR not connected: 0x5A
- ADDR tied to 3.3V: 0x5B
- ADDR tied to SDA: 0x5C
- ADDR tied to SCL: 0x5D

*NOTE*: Before attaching ADD pin to any of the other pins except **GND**, the connection between **ADD** and **GRN** pin has to be broken. Refer to the image below:

![](https://github.com/sarweshshah/o_ring/blob/master/images/ADD-GND%20wire%20break.jpg)

Refer to the wiring diagram below for circuit connections. The connection for address change has been shorted (purple wires) in the image below, but a 10K3 ohms resistor is advised to make the connection.

![Wire Connections](https://github.com/sarweshshah/o_ring/blob/master/images/Wire%20connections.png)

### Phase IV: Checking the I2C connections
Once the wiring is complete, the [i2c_scanner.ino](https://github.com/sarweshshah/o_ring/blob/master/testing/mpr_121_multiple/i2c_scanner/i2c_scanner.ino) code can be used to check if the data and clock connections are correctly performed. This, however, does not assure the live and ground wire connection.
![i2c_scanner Serial Monitor output](https://github.com/sarweshshah/o_ring/blob/master/images/i2c_scanner_monitor.png)

The [mpr121_i2c.ino](https://github.com/sarweshshah/o_ring/blob/master/testing/mpr_121_multiple/mpr121_i2c/mpr121_i2c.ino) file shows the ones among 48 sensors that are touched by the user. This is a consolidated test and required a 9V-2A adaptor to power the entire circuit without which the sensors might not respond.
![](https://github.com/sarweshshah/o_ring/blob/master/images/mpr121_i2c%20monitor.png)

### Phase V: Lighting the Neopixel lights
Once the touch sensors are connected, the RGB lights can be added to the circuit with PIN 13 as their input. The 48 touchpoints can then be mapped to the 158 (in our case) RGB lights and desired interactions can be coded. The [mpr121_neopixel.ino](https://github.com/sarweshshah/o_ring/blob/master/testing/mpr121_neopixel/mpr121_neopixel.ino) code lights the LEDs, gathers the touch information from the ring and dims the lights of the mapped pixels.

![](https://github.com/sarweshshah/o_ring/blob/master/images/RGB%20lights.JPG)

The image below shows the serial output of user interactions:
![mpr121_neopixel Serial Monitor output](https://github.com/sarweshshah/o_ring/blob/master/images/mpr121_neopixel%20monitor.png)

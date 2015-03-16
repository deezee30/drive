// AD5258 library implementation via Arduino serial monitor by Adetunji Dahunsi <tunjid.com>
// Updates should (hopefully) always be available at https://github.com/WuMRC

// This sketch changes the wiper position for a two AD5258s; "r1" and "r2" in a rheostat configuration.

#include "Wire.h"
#include "Math.h"
#include "AD5258.h" //Library for AD5933 functions (must be installed)

#define SUPPLY_VOLTAGE 8

int rawAnalog = 0;
float voltage = 0;
uint8_t wiperPosition = 0;

AD5258 r1; // rheostat r1
AD5258 r2; // rheostat r1

void setup() {
  Serial.println();
  Wire.begin(); // Start Arduino I2C library
  Serial.begin(38400);
  // MUST BE DONE BEFOR analogRead() IS CALLED!
  // Set analog reference voltage to 0.2 volts so AD5258 and arduino are not damaged.
  analogReference(EXTERNAL); 
  pinMode(SUPPLY_VOLTAGE, OUTPUT);
  digitalWrite(SUPPLY_VOLTAGE, HIGH); 
  r1.begin(1);
  r2.begin(2);
  Serial.println();
  Serial.println();
}

void loop() {

  while (Serial.available() < 1) {
    delay(15);
  } // Wait for user to move electrodes before starting
  
  // Only collect data within the linear range of AD5933. Take 50 points.
  for(int R1 = 14; R1 < 64; R1++) {
    r1.writeRDAC(R1);
    rawAnalog = analogRead(A0);
    voltage = rawAnalog * (0.213 / 1023.0);
    Serial.print(R1);
    Serial.print(",");
    Serial.print(rawAnalog);
    Serial.print(",");
    Serial.println(voltage, 6);
    delay(500);
  }

} // void loop() {
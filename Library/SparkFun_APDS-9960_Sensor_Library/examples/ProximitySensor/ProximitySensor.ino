/****************************************************************
ProximityTest.ino
APDS-9960 RGB and Gesture Sensor
Shawn Hymel @ SparkFun Electronics
October 28, 2014
https://github.com/sparkfun/APDS-9960_RGB_and_Gesture_Sensor

Tests the proximity sensing abilities of the APDS-9960.
Configures the APDS-9960 over I2C and polls for the distance to
the object nearest the sensor.

Hardware Connections:

IMPORTANT: The APDS-9960 can only accept 3.3V!
 
 Wemos Pin  APDS-9960 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 D3           SDA              I2C Data
 D1           SCL              I2C Clock

Resources:
Include Wire.h and SparkFun_APDS-9960.h

Development environment specifics:
Written in Arduino 1.0.5
Tested with SparkFun Arduino Pro Mini 3.3V

This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, please
buy us a round!

Distributed as-is; no warranty is given.

Modified for ESP8266 by Jon Ulmer Nov 2016
****************************************************************/

#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Pins on wemos D1 mini
#define APDS9960_SDA    D3  //AKA GPIO0
#define APDS9960_SCL    D1  //AKA GPIO5

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint8_t proximity_data = 0;

void setup() {

  //Start I2C with pins defined above
  Wire.begin(APDS9960_SDA,APDS9960_SCL);
  
  // Initialize Serial port
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("------------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - ProximitySensor"));
  Serial.println(F("------------------------------------"));
  
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Adjust the Proximity sensor gain
  if ( !apds.setProximityGain(PGAIN_2X) ) {
    Serial.println(F("Something went wrong trying to set PGAIN"));
  }
  
  // Start running the APDS-9960 proximity sensor (no interrupts)
  if ( apds.enableProximitySensor(false) ) {
    Serial.println(F("Proximity sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }
}

void loop() {
  
  // Read the proximity value
  if ( !apds.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print("Proximity: ");
    Serial.println(proximity_data);
  }
  
  // Wait 250 ms before next reading
  delay(250);
}

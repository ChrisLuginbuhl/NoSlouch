/*************************************************** 
  This is a library for the CAP1188 I2C/SPI 8-chan Capacitive Sensor

  Designed specifically to work with the CAP1188 sensor from Adafruit
  ----> https://www.adafruit.com/products/1602

  These sensors use I2C/SPI to communicate, 2+ pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>

// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9

//Buzzer pins
#define BUZZ1  6
#define BUZZ2  19

// CS pin is used for software or hardware SPI
#define CAP1188_CS  10


// Or...Use I2C, with reset pin
Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_RESET);

void setup() {
  
  Serial.begin(9600);
  Serial.println("CAP1188 test!");

  // Initialize the sensor, if using i2c you can pass in the i2c address
  // if (!cap.begin(0x28)) {
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!");
  pinMode(BUZZ1, OUTPUT);
  pinMode(BUZZ2, OUTPUT);
   
}

void loop() {
  
  uint8_t touched = cap.touched();

//if both C1 and C8 are off
  if (touched == 0) {
    digitalWrite(BUZZ1, LOW);
    digitalWrite(BUZZ2, LOW);
    return;
  }

//if C1 is on and C8 off...ie terrible posture
  if ((touched & 1) && !(touched & (1 << 7))) {
    digitalWrite(BUZZ1, HIGH);
    digitalWrite(BUZZ2, HIGH);
    Serial.print("Terrible posture  ");
  }

 //if C8 is on and C1 off...ie good posture
  if (touched & (1 << 7) && !(touched & 1)){
    digitalWrite(BUZZ1, LOW);
    digitalWrite(BUZZ2, LOW);
    Serial.print("Good posture   ");
  }

// if C1 and C8 are on...ie bad posture
  if ((touched & (1 << 7)) && (touched & 1))  {
    digitalWrite(BUZZ1, HIGH);
    digitalWrite(BUZZ2, LOW);
    Serial.print("Bad posture   ");
  }


  
 /* for (uint8_t i=0; i<8; i++) {
    if (touched & (1 << i)) {
      Serial.print("C"); Serial.print(i+1); Serial.print("\t");
    }
  }
  */ 
  Serial.println();
  delay(50);
 
}


// I2C device class (I2Cdev) demonstration Arduino sketch for MPU9250
// 1/4/2013 original by Jeff Rowberg <jeff@rowberg.net> at https://github.com/jrowberg/i2cdevlib
//          modified by Brent Wilkins <Brent.Wilkins@SparkFun.com>
//
// Changelog:
//     2016-02-26 - made into a simple demo that outputs human readable values.
//     2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"

// I2Cdev and MPU9250 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU9250.h"
#include "helper_3dmath.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU9250 accelGyroMag;

#define LED_PIN 13
bool blinkState = false;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 works as well at 8MHz as it does at 16MHz, but it's really up to
    // you depending on your project)
    Serial.begin(115200);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelGyroMag.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelGyroMag.testConnection() ? "MPU9250 connection successful" : "MPU9250 connection failed");

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    Serial.print("Temperature (˚C): ");
    Serial.println(accelGyroMag.readTempC());

    Serial.print("Temperature (˚F): ");
    Serial.println(accelGyroMag.readTempF());

    Serial.print("Acceleration along X-axis (g): ");
    Serial.println(accelGyroMag.readAccelX());
    Serial.print("Acceleration along Y-axis (g): ");
    Serial.println(accelGyroMag.readAccelY());
    Serial.print("Acceleration along Z-axis (g): ");
    Serial.println(accelGyroMag.readAccelZ());

    Serial.print("Rotation about X-axis (degrees/sec): ");
    Serial.println(accelGyroMag.readGyroX());
    Serial.print("Rotation about Y-axis (degrees/sec): ");
    Serial.println(accelGyroMag.readGyroY());
    Serial.print("Rotation about Z-axis (degrees/sec): ");
    Serial.println(accelGyroMag.readGyroZ());

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
    delay(50);
}

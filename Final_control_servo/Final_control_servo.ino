#include <Wire.h>
#include <Matrix_Display.h>
#include "ArduinoServoController.h"
#include "WiFiServerHandler.h"


// For Servo
#define SERVOMIN 165
#define SERVOMAX 655
ArduinoServoController servoController(0, SERVOMIN, SERVOMAX);

// For Wifi Communications
WiFiServerHandler wifiServerHandler(80);

void setup() {
  Serial.begin(9600);
  
  servoController.begin();
  wifiServerHandler.begin();
  
  servoController.moveServoTo(SERVOMIN, 10);
}

void loop() {
  wifiServerHandler.handleClient(servoController, SERVOMIN);
}

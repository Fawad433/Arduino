#ifndef ARDUINO_SERVO_CONTROLLER_H
#define ARDUINO_SERVO_CONTROLLER_H

#include <Adafruit_PWMServoDriver.h>

class ArduinoServoController {
public:
  ArduinoServoController(uint8_t servonum, uint16_t servomin, uint16_t servomax);
  void begin();
  void moveServoTo(uint16_t newPosition, uint16_t speed);

private:
  Adafruit_PWMServoDriver myServo;
  uint8_t servonum;
  uint16_t servomin;
  uint16_t servomax;
  uint16_t currentPosition;
};

#endif


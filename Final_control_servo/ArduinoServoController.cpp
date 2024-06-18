#include "ArduinoServoController.h"

ArduinoServoController::ArduinoServoController(uint8_t servonum, uint16_t servomin, uint16_t servomax)
  : servonum(servonum), servomin(servomin), servomax(servomax), currentPosition(servomin) {
}

void ArduinoServoController::begin() {
  myServo = Adafruit_PWMServoDriver();
  myServo.begin();
  myServo.setPWMFreq(60);
  delay(10);
}

void ArduinoServoController::moveServoTo(uint16_t newPosition, uint16_t speed) {
  if (newPosition > servomax) newPosition = servomax;
  if (newPosition < servomin) newPosition = servomin;

  if (currentPosition < newPosition) {
    for (uint16_t pos = currentPosition; pos <= newPosition; pos++) {
      myServo.setPWM(servonum, 0, pos);
      delay(speed);
    }
  } else {
    for (uint16_t pos = currentPosition; pos >= newPosition; pos--) {
      myServo.setPWM(servonum, 0, pos);
      delay(speed);
    }
  }
  currentPosition = newPosition;
}

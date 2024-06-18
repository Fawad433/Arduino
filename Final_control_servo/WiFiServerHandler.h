#ifndef WIFI_SERVER_HANDLER_H
#define WIFI_SERVER_HANDLER_H

#include <WiFiS3.h>
#include "arduino_secrets.h"
#include "ArduinoServoController.h"

class WiFiServerHandler {
public:
  WiFiServerHandler(uint16_t port);
  void begin();
  void handleClient(ArduinoServoController& servoController, uint16_t servomin);

private:
  WiFiServer server;
};

#endif

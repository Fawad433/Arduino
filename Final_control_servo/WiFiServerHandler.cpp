#include "WiFiServerHandler.h"
#include "ArduinoServoController.h"

WiFiServerHandler::WiFiServerHandler(uint16_t port) : server(port) {
}

void WiFiServerHandler::begin() {
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  server.begin();
  Serial.println("Server started");

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void WiFiServerHandler::handleClient(ArduinoServoController& servoController, uint16_t servomin) {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        client.flush();

        int angleIndex = request.indexOf("angle=");
        int speedIndex = request.indexOf("speed=");

        if (angleIndex != -1 && speedIndex != -1) {
          String angleString = request.substring(angleIndex + 6, request.indexOf('&', angleIndex));
          String speedString = request.substring(speedIndex + 6);

          int angle = angleString.toInt();
          int speed = speedString.toInt();

          Serial.print("Received angle: ");
          Serial.println(angle);
          Serial.print("Received speed: ");
          Serial.println(speed);

          int receivedData = angle * 2.72;
          receivedData = receivedData + servomin;

          servoController.moveServoTo(receivedData, speed);
          client.println("new angle");
          client.println(angle);
        }

        

        delay(10);
        client.stop();
        Serial.println("Client disconnected.");
      }
    }
  }
}

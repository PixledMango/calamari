#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>

BluetoothSerial SerialBT;

#define JoystickX 32
#define JoystickY 35

void setup()
{
    Serial.begin(115200);

    pinMode(JoystickX, INPUT);
    pinMode(JoystickX, INPUT);

    // Connect to the Robot
    SerialBT.begin("CalamariController", true);
    Serial.print("Controller Serial Started. Discoverable as 'CalamariController'.");
    while (!SerialBT.connect("CalamariRobot"))
    {
        Serial.println("Trying to connect to 'CalamariRobot'");
        delay(1000);
    }
    Serial.println("Connected to 'CalamariRobot'");
}

void loop()
{
    if (SerialBT.available())
    {
        String received = SerialBT.readStringUntil('\n');
        Serial.println("Received from Robot: " + received);
    }

    int xPos = analogRead(JoystickX);
    int yPos = analogRead(JoystickY);

    StaticJsonDocument<128> jsonDoc;
    jsonDoc["x"] = xPos;
    jsonDoc["y"] = yPos;

    String jsonString;
    serializeJson(jsonDoc, jsonString);
    SerialBT.println(jsonString);

    delay(1000);
}
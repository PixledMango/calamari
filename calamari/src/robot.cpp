#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>

BluetoothSerial SerialBT;

void setup()
{
    Serial.begin(115200);

    // Connect to the Controller
    SerialBT.begin("CalamariRobot");
    Serial.print("Controller Serial Started. Discoverable as 'CalamariRobot'.");
    while (!SerialBT.connected())
    {
        Serial.println("Trying to connect to 'CalamariController'");
        delay(1000);
    }
    Serial.println("Connected to 'CalamariController'");
}

void loop()
{
    if (SerialBT.available())
    {
        String incomingData = SerialBT.readStringUntil('\n');
        StaticJsonDocument<128> jsonDoc;
        DeserializationError error = deserializeJson(jsonDoc, incomingData);

        if (error)
            return;

        int x = jsonDoc["x"];

        Serial.println(x);
    }
}
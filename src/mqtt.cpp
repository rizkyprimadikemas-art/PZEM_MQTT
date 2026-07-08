#include "mqtt.h"

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "config.h"
#include "cert.h"
#include "pzem.h"

// ======================================================
// MQTT Client
// ======================================================

WiFiClientSecure secureClient;
PubSubClient mqtt(secureClient);

// ======================================================

String topicData;
String topicStatus;
String topicInfo;
String topicCmd;

// ======================================================

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("[MQTT] Topic : ");
    Serial.println(topic);

    String message;

    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    Serial.print("[MQTT] Payload : ");
    Serial.println(message);

    // TODO:
    // restart
    // reset energy
    // ota
}

// ======================================================

void initMQTT()
{
    secureClient.setCACert(root_ca);

    mqtt.setServer(MQTT_HOST, MQTT_PORT);

    mqtt.setCallback(mqttCallback);

    topicData = "ems/" + String(DEVICE_ID) + "/data";
    topicStatus = "ems/" + String(DEVICE_ID) + "/status";
    topicInfo = "ems/" + String(DEVICE_ID) + "/info";
    topicCmd = "ems/" + String(DEVICE_ID) + "/cmd";
}

// ======================================================

void checkMQTTConnection()
{
    if (WiFi.status() != WL_CONNECTED)
        return;

    if (mqtt.connected())
        return;

    Serial.println("[MQTT] Connecting...");

    bool ok = mqtt.connect(
        DEVICE_ID,
        MQTT_USER,
        MQTT_PASS,
        topicStatus.c_str(),
        0,
        true,
        "offline");

    if (ok)
    {
        Serial.println("[MQTT] Connected");

        mqtt.publish(
            topicStatus.c_str(),
            "online",
            true);

        mqtt.subscribe(topicCmd.c_str());
    }
    else
    {
        Serial.print("[MQTT] Failed : ");
        Serial.println(mqtt.state());
    }
}

// ======================================================

void mqttLoop()
{
    mqtt.loop();
}

// ======================================================

bool isMQTTConnected()
{
    return mqtt.connected();
}

// ======================================================

void publishHeartbeat()
{
    JsonDocument doc;

    doc["device"] = DEVICE_ID;
    doc["status"] = "online";
    doc["uptime"] = millis() / 1000;

    char buffer[128];

    serializeJson(doc, buffer);

    mqtt.publish(topicStatus.c_str(), buffer, true);
}

// ======================================================

void publishDeviceInfo()
{
    JsonDocument doc;

    doc["device"] = DEVICE_ID;
    doc["ip"] = WiFi.localIP().toString();
    doc["mac"] = WiFi.macAddress();
    doc["rssi"] = WiFi.RSSI();
    doc["heap"] = ESP.getFreeHeap();
    doc["uptime"] = millis() / 1000;

    char buffer[256];

    serializeJson(doc, buffer);

    mqtt.publish(topicInfo.c_str(), buffer);
}

// ======================================================

void publishPZEMData()
{
    float voltage = getVoltage();

    if (isnan(voltage))
    {
        Serial.println("[PZEM] Read Error");
        return;
    }

    JsonDocument doc;

    doc["device"] = DEVICE_ID;
    doc["voltage"] = voltage;
    doc["current"] = getCurrent();
    doc["power"] = getPower();
    doc["energy"] = getEnergy();
    doc["frequency"] = getFrequency();
    doc["pf"] = getPF();

    doc["rssi"] = WiFi.RSSI();

    char buffer[256];

    serializeJson(doc, buffer);

    if (mqtt.publish(topicData.c_str(), buffer))
    {
        Serial.println("[MQTT] Publish OK");
        Serial.println(buffer);
    }
    else
    {
        Serial.println("[MQTT] Publish Failed");
    }
}
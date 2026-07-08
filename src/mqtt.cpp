#include "mqtt.h"
#include "wifi_manager.h"
#include "cert.h"

#include <ArduinoJson.h>

WiFiClientSecure secureClient;
PubSubClient mqttClient(secureClient);

unsigned long previousMQTTReconnect = 0;
const unsigned long mqttReconnectInterval = 5000;

void initMQTT()
{
    Serial.println();
    Serial.println("=================================");
    Serial.println("Initializing MQTT");
    Serial.println("=================================");

    secureClient.setCACert(root_ca);

    mqttClient.setServer(MQTT_HOST, MQTT_PORT);
}

bool mqttConnected()
{
    return mqttClient.connected();
}

void reconnectMQTT()
{
    if (!wifiConnected())
        return;

    if (mqttClient.connected())
        return;

    Serial.print("Connecting MQTT... ");

    String statusTopic = "ems/" + String(DEVICE_ID) + "/status";

    if (mqttClient.connect(
            DEVICE_ID,
            MQTT_USER,
            MQTT_PASS,
            statusTopic.c_str(),
            1,
            true,
            "offline"))
    {
        Serial.println("SUCCESS");

        publishStatus("online");

        mqttClient.subscribe(("ems/" + String(DEVICE_ID) + "/cmd").c_str());
    }
    else
    {
        Serial.print("FAILED : ");
        Serial.println(mqttClient.state());
    }
}

void mqttLoop()
{
    unsigned long now = millis();

    if (now - previousMQTTReconnect >= mqttReconnectInterval)
    {
        previousMQTTReconnect = now;

        reconnectMQTT();
    }

    mqttClient.loop();
}

void publishStatus(const char *status)
{
    if (!mqttClient.connected())
        return;

    String topic = "ems/" + String(DEVICE_ID) + "/status";

    mqttClient.publish(topic.c_str(), status, true);
}

void publishPZEM(PZEMData data)
{
    if (!mqttClient.connected())
        return;

    StaticJsonDocument<512> doc;

    doc["device"] = DEVICE_ID;
    doc["voltage"] = data.voltage;
    doc["current"] = data.current;
    doc["power"] = data.power;
    doc["energy"] = data.energy;
    doc["frequency"] = data.frequency;
    doc["pf"] = data.pf;
    doc["ip"] = getIPAddress();
    doc["rssi"] = getRSSI();
    doc["uptime"] = millis() / 1000;

    char payload[512];

    serializeJson(doc, payload);

    String topic = "ems/" + String(DEVICE_ID) + "/data";

    mqttClient.publish(topic.c_str(), payload);

    Serial.println(payload);
}
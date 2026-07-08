#include <Arduino.h>

#include "config.h"
#include "wifi_manager.h"
#include "mqtt.h"
#include "pzem.h"

unsigned long lastWifiCheck = 0;
unsigned long lastMQTTCheck = 0;
unsigned long lastPublish = 0;
unsigned long lastHeartbeat = 0;
unsigned long lastDeviceInfo = 0;

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("==================================");
    Serial.println("EMS Ecosystem");
    Serial.println("Firmware v1.0");
    Serial.println("==================================");

    initPZEM();
    initWiFiManager();
    initMQTT();
}

void loop()
{
    unsigned long now = millis();

    // wajib dipanggil terus
    mqttLoop();

    // ==========================
    // WiFi Task
    // ==========================
    if (now - lastWifiCheck >= WIFI_CHECK_INTERVAL)
    {
        lastWifiCheck = now;
        checkWiFiConnection();
    }

    // ==========================
    // MQTT Task
    // ==========================
    if (now - lastMQTTCheck >= MQTT_CHECK_INTERVAL)
    {
        lastMQTTCheck = now;
        checkMQTTConnection();
    }

    // ==========================
    // Publish Data PZEM
    // ==========================
    if (now - lastPublish >= PUBLISH_INTERVAL)
    {
        lastPublish = now;

        if (isMQTTConnected())
        {
            publishPZEMData();
        }
    }

    // ==========================
    // Heartbeat
    // ==========================
    if (now - lastHeartbeat >= HEARTBEAT_INTERVAL)
    {
        lastHeartbeat = now;

        if (isMQTTConnected())
        {
            publishHeartbeat();
        }
    }

    // ==========================
    // Device Information
    // ==========================
    if (now - lastDeviceInfo >= INFO_INTERVAL)
    {
        lastDeviceInfo = now;

        if (isMQTTConnected())
        {
            publishDeviceInfo();
        }
    }
}
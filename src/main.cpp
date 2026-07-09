#include <Arduino.h>

#include "config.h"
#include "wifi_portal.h"
#include "mqtt.h"
#include "pzem.h"

unsigned long lastPZEMRead = 0;
unsigned long lastMQTTCheck = 0;
unsigned long lastPublish = 0;
unsigned long lastHeartbeat = 0;
unsigned long lastDeviceInfo = 0;

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("======================================");
    Serial.println(" EMS Ecosystem");
    Serial.println(" Firmware v1.0");
    Serial.println("======================================");

    // Inisialisasi PZEM
    //initPZEM();

    // Inisialisasi WiFi Portal
    wifiPortalBegin();

    // Inisialisasi MQTT
    // initMQTT();

    Serial.println("[SYSTEM] Ready");
}

void loop()
{
    unsigned long now = millis();

    // =====================================================
    // WiFi Portal (WAJIB dipanggil terus)
    // =====================================================
    wifiPortalLoop();

    // =====================================================
    // MQTT loop (WAJIB dipanggil terus)
    // =====================================================
    mqttLoop();

    // =====================================================
    // Cek koneksi MQTT
    // =====================================================
    if (now - lastMQTTCheck >= MQTT_CHECK_INTERVAL)
    {
        lastMQTTCheck = now;
        checkMQTTConnection();
    }

    // =====================================================
    // Baca PZEM
    // =====================================================
    if (now - lastPZEMRead >= PZEM_READ_INTERVAL)
    {
        lastPZEMRead = now;
        readPZEM();
    }

    // =====================================================
    // Publish Data
    // =====================================================
    if (now - lastPublish >= PUBLISH_INTERVAL)
    {
        lastPublish = now;

        if (isMQTTConnected())
        {
            publishPZEMData();
        }
    }

    // =====================================================
    // Heartbeat
    // =====================================================
    if (now - lastHeartbeat >= HEARTBEAT_INTERVAL)
    {
        lastHeartbeat = now;

        if (isMQTTConnected())
        {
            publishHeartbeat();
        }
    }

    // =====================================================
    // Device Information
    // =====================================================
    if (now - lastDeviceInfo >= INFO_INTERVAL)
    {
        lastDeviceInfo = now;

        if (isMQTTConnected())
        {
            publishDeviceInfo();
        }
    }
}
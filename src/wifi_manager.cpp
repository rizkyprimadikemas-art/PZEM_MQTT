#include "wifi_manager.h"

WiFiManager wm;

unsigned long previousWifiCheck = 0;
const unsigned long wifiCheckInterval = 5000;

void initWiFi()
{
    Serial.println();
    Serial.println("=================================");
    Serial.println("Initializing WiFi");
    Serial.println("=================================");

    WiFi.mode(WIFI_STA);

    bool res = wm.autoConnect("EMS_Setup");

    if (!res)
    {
        Serial.println("WiFi Connection Failed");
    }
    else
    {
        Serial.println("WiFi Connected");
        Serial.print("IP Address : ");
        Serial.println(WiFi.localIP());

        Serial.print("RSSI       : ");
        Serial.print(WiFi.RSSI());
        Serial.println(" dBm");
    }
}

void wifiLoop()
{
    unsigned long now = millis();

    if (now - previousWifiCheck < wifiCheckInterval)
        return;

    previousWifiCheck = now;

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("[WiFi] Reconnecting...");

        WiFi.disconnect();
        WiFi.reconnect();
    }
}

bool wifiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

String getIPAddress()
{
    if (WiFi.status() != WL_CONNECTED)
        return "0.0.0.0";

    return WiFi.localIP().toString();
}

int getRSSI()
{
    if (WiFi.status() != WL_CONNECTED)
        return -999;

    return WiFi.RSSI();
}
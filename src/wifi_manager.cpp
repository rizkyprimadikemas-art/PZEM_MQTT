#include "wifi_manager.h"

#include <WiFi.h>
#include <WiFiManager.h>

static WiFiManager wm;

//--------------------------------------------------
// Inisialisasi WiFiManager
//--------------------------------------------------

void initWiFiManager()
{
    WiFi.mode(WIFI_STA);

    // Hostname ESP
    WiFi.setHostname("EMS001");

    // Konfigurasi AP jika belum pernah tersimpan
    wm.setConfigPortalTimeout(180);

    wm.setConnectRetries(3);

    wm.setDebugOutput(true);

    Serial.println("[WiFi] Starting WiFiManager...");

    bool res = wm.autoConnect("EMS_Setup");

    if(res)
    {
        Serial.println("[WiFi] Connected");
        Serial.print("[WiFi] IP : ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("[WiFi] Config Portal Timeout");
    }
}

//--------------------------------------------------
// Dipanggil dari scheduler setiap 5 detik
//--------------------------------------------------

void checkWiFiConnection()
{
    if(WiFi.status()==WL_CONNECTED)
        return;

    Serial.println("[WiFi] Reconnecting...");

    WiFi.reconnect();
}

//--------------------------------------------------

bool isWiFiConnected()
{
    return WiFi.status()==WL_CONNECTED;
}

//--------------------------------------------------

String getIPAddress()
{
    return WiFi.localIP().toString();
}

//--------------------------------------------------

String getMacAddress()
{
    return WiFi.macAddress();
}
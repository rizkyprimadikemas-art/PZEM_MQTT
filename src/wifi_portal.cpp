#include "wifi_portal.h"

DNSServer dnsServer;

static bool apMode=false;

static char apSSID[32];

bool connectToWiFi(
    const char* ssid,
    const char* password)
{
    Serial.println();

    Serial.println("===== CONNECT WIFI =====");

    WiFi.persistent(false);

    WiFi.setSleep(false);

    WiFi.mode(WIFI_OFF);

    delay(500);

    WiFi.mode(WIFI_STA);

    delay(500);

    WiFi.begin(ssid,password);

    uint32_t start=millis();

    while(
        WiFi.status()!=WL_CONNECTED &&
        millis()-start<15000)
    {
        Serial.print(".");

        delay(500);
    }

    Serial.println();

    if(WiFi.status()==WL_CONNECTED)
    {
        Serial.println("CONNECTED");

        Serial.print("SSID : ");

        Serial.println(WiFi.SSID());

        Serial.print("IP : ");

        Serial.println(WiFi.localIP());

        return true;
    }

    Serial.println("FAILED");

    return false;
}
void startAPMode()
{
    Serial.println();

    Serial.println("===== START AP =====");

    WiFi.mode(WIFI_OFF);

    delay(500);

    WiFi.mode(WIFI_AP);

    delay(500);

    WiFi.softAPConfig(
        IPAddress(192,168,4,1),
        IPAddress(192,168,4,1),
        IPAddress(255,255,255,0));

    delay(500);

    String mac=WiFi.macAddress();

    String last=
        mac.substring(mac.length()-5);

    last.replace(":","");

    sprintf(
        apSSID,
        "Lantabura_%s",
        last.c_str());

    bool ok=
        WiFi.softAP(
            apSSID,
            AP_PASSWORD,
            1,
            false,
            4);

    if(ok)
    {
        Serial.println("AP START OK");
    }
    else
    {
        Serial.println("AP START FAILED");
    }

    Serial.print("SSID : ");

    Serial.println(apSSID);

    Serial.print("PASS : ");

    Serial.println(AP_PASSWORD);

    Serial.print("IP : ");

    Serial.println(WiFi.softAPIP());

    dnsServer.start(
        53,
        "*",
        WiFi.softAPIP());

    apMode=true;
}
void wifiPortalBegin()
{
    Serial.begin(115200);

    delay(1000);

    bool connected=
        connectToWiFi(
            "NamaWifi",
            "PasswordWifi");

    if(!connected)
    {
        startAPMode();
    }
}
void wifiPortalLoop()
{
    if(apMode)
    {
        dnsServer.processNextRequest();
    }
}
bool isWifiConnected()
{
    return WiFi.status()==WL_CONNECTED;
}

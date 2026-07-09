#ifndef WIFI_PORTAL_H
#define WIFI_PORTAL_H

#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>

#define AP_PASSWORD "12345678"

extern DNSServer dnsServer;

void wifiPortalBegin();

void wifiPortalLoop();

bool connectToWiFi(
    const char* ssid,
    const char* password);

void startAPMode();

bool isWifiConnected();

#endif
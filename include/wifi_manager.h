#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

void initWiFi();

void wifiLoop();

bool wifiConnected();

String getIPAddress();

int getRSSI();

#endif
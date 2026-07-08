#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

void initWiFiManager();
void checkWiFiConnection();

bool isWiFiConnected();

String getIPAddress();
String getMacAddress();

#endif
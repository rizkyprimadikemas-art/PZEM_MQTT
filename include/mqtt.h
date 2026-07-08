#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>

void initMQTT();

void checkMQTTConnection();

void mqttLoop();

bool isMQTTConnected();

void publishPZEMData();

void publishHeartbeat();

void publishDeviceInfo();

#endif
#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "config.h"
#include "pzem.h"

extern WiFiClientSecure secureClient;
extern PubSubClient mqttClient;

void initMQTT();

void mqttLoop();

bool mqttConnected();

void reconnectMQTT();

void publishPZEM(PZEMData data);

void publishStatus(const char *status);

#endif
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

//=====================================================
// DEVICE
//=====================================================

#define DEVICE_ID      "EMS001"
#define FW_VERSION     "0.1.0"

//=====================================================
// PZEM
//=====================================================

#define RX_PIN         0
#define TX_PIN         2

//=====================================================
// MQTT
//=====================================================

#define MQTT_HOST      "i7f57f77.ala.asia-southeast1.emqxsl.com"
#define MQTT_PORT      8883
#define MQTT_USER      "PZEM"
#define MQTT_PASS      "PZEM123"

//=====================================================
// Scheduler
//=====================================================

#define PZEM_READ_INTERVAL      1000UL
#define MQTT_CHECK_INTERVAL     3000UL
#define PUBLISH_INTERVAL        2000UL
#define HEARTBEAT_INTERVAL      30000UL
#define INFO_INTERVAL           60000UL

#endif
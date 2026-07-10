#include "led_task.h"

#include <Arduino.h>

#include "config.h"
#include "globals.h"

//======================================================
// Blink Timer
//======================================================

static unsigned long blinkTimer = 0;
static bool blinkState = false;

const uint16_t BLINK_INTERVAL = 500;

//======================================================

void LED_Init()
{
    pinMode(LED_POWER, OUTPUT);
    pinMode(LED_WIFI, OUTPUT);
    pinMode(LED_MQTT, OUTPUT);
    pinMode(LED_OUTPUT, OUTPUT);

    digitalWrite(LED_POWER, HIGH);
    digitalWrite(LED_WIFI, LOW);
    digitalWrite(LED_MQTT, LOW);
    digitalWrite(LED_OUTPUT, LOW);
}

//======================================================

void LED_Task()
{
    unsigned long now = millis();

    //----------------------------------------
    // Blink Generator
    //----------------------------------------

    if (now - blinkTimer >= BLINK_INTERVAL)
    {
        blinkTimer = now;
        blinkState = !blinkState;
    }

    //----------------------------------------
    // POWER
    //----------------------------------------

    digitalWrite(LED_POWER, HIGH);

    //----------------------------------------
    // WIFI
    //----------------------------------------

    if (Status.wifiConnected)
    {
        digitalWrite(LED_WIFI, HIGH);
    }
    else
    {
        digitalWrite(LED_WIFI, blinkState);
    }

    //----------------------------------------
    // MQTT
    //----------------------------------------

    if (Status.mqttConnected)
    {
        digitalWrite(LED_MQTT, HIGH);
    }
    else
    {
        digitalWrite(LED_MQTT, blinkState);
    }

    //----------------------------------------
    // OUTPUT
    //----------------------------------------

    if (Output.relay1 || Output.relay2)
    {
        digitalWrite(LED_OUTPUT, HIGH);
    }
    else
    {
        digitalWrite(LED_OUTPUT, LOW);
    }
}
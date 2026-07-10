#include "relay_task.h"

#include <Arduino.h>

#include "config.h"
#include "globals.h"

//======================================================
// Last State
//======================================================

static bool lastRelay1 = false;
static bool lastRelay2 = false;

//======================================================

void Relay_Init()
{
    pinMode(RELAY1_PIN, OUTPUT);
    pinMode(RELAY2_PIN, OUTPUT);

    digitalWrite(RELAY1_PIN, LOW);
    digitalWrite(RELAY2_PIN, LOW);

    Output.relay1 = false;
    Output.relay2 = false;

    Serial.println("Relay Initialized");
}

//======================================================

void Relay_Task()
{
    //----------------------------------------
    // Update Relay
    //----------------------------------------

    digitalWrite(RELAY1_PIN, Output.relay1);
    digitalWrite(RELAY2_PIN, Output.relay2);

    //----------------------------------------
    // Debug jika berubah
    //----------------------------------------

    if (Output.relay1 != lastRelay1)
    {
        Serial.print("[DO] Relay1 : ");
        Serial.println(Output.relay1 ? "ON" : "OFF");

        lastRelay1 = Output.relay1;
    }

    if (Output.relay2 != lastRelay2)
    {
        Serial.print("[DO] Relay2 : ");
        Serial.println(Output.relay2 ? "ON" : "OFF");

        lastRelay2 = Output.relay2;
    }
}
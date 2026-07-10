#include "protection.h"

#include <Arduino.h>

#include "globals.h"

//======================================================
// Protection Setting
//======================================================

static const float OVER_VOLTAGE  = 250.0f;
static const float UNDER_VOLTAGE = 180.0f;
static const float OVER_CURRENT  = 10.0f;

//======================================================

void Protection_Init()
{
}

//======================================================

void Protection_Task()
{
    //--------------------------------------------------
    // Default
    //--------------------------------------------------

    Output.relay1 = false;
    Output.relay2 = false;

    //--------------------------------------------------
    // Valid Data ?
    //--------------------------------------------------

    if (isnan(Meter.voltage))
        return;

    if (isnan(Meter.current))
        return;

    //--------------------------------------------------
    // Over Voltage
    //--------------------------------------------------

    if (Meter.voltage > OVER_VOLTAGE)
        return;

    //--------------------------------------------------
    // Under Voltage
    //--------------------------------------------------

    if (Meter.voltage < UNDER_VOLTAGE)
        return;

    //--------------------------------------------------
    // Over Current
    //--------------------------------------------------

    if (Meter.current > OVER_CURRENT)
        return;

    //--------------------------------------------------
    // Digital Input Interlock
    //--------------------------------------------------

    if (!Input.di1)
        return;

    //--------------------------------------------------
    // Semua kondisi aman
    //--------------------------------------------------

    Output.relay1 = true;
    Output.relay2 = true;
}
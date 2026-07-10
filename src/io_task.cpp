#include "io_task.h"

#include <Arduino.h>

#include "config.h"
#include "globals.h"

//======================================================
// Last State
//======================================================

static bool lastDI1 = false;
static bool lastDI2 = false;

//======================================================

void IO_Init()
{
    pinMode(DI1_PIN, INPUT_PULLUP);
    pinMode(DI2_PIN, INPUT_PULLUP);

    Input.di1 = false;
    Input.di2 = false;

    lastDI1 = false;
    lastDI2 = false;

    Serial.println("Digital Input Initialized");
}

//======================================================

void IO_Task()
{
    //----------------------------------------
    // Read Input
    //----------------------------------------

    Input.di1 = !digitalRead(DI1_PIN);
    Input.di2 = !digitalRead(DI2_PIN);

    //----------------------------------------
    // Debug jika berubah
    //----------------------------------------

    if (Input.di1 != lastDI1)
    {
        Serial.print("[DI] DI1 : ");
        Serial.println(Input.di1 ? "ON" : "OFF");

        lastDI1 = Input.di1;
    }

    if (Input.di2 != lastDI2)
    {
        Serial.print("[DI] DI2 : ");
        Serial.println(Input.di2 ? "ON" : "OFF");

        lastDI2 = Input.di2;
    }
}
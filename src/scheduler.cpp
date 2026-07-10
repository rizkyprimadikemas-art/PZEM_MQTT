#include <Arduino.h>

#include "scheduler.h"

#include "pzem_task.h"
#include "io_task.h"
#include "relay_task.h"
#include "button_task.h"
#include "led_task.h"
#include "protection.h"

//======================================================
// Scheduler Timer
//======================================================

static unsigned long timerButton = 0;
static unsigned long timerIO = 0;
static unsigned long timerRelay = 0;
static unsigned long timerLED = 0;
static unsigned long timerProtection = 0;
static unsigned long timerPZEM = 0;

//======================================================
// Scheduler Interval
//======================================================

const uint32_t BUTTON_INTERVAL      = 20;
const uint32_t IO_INTERVAL          = 20;
const uint32_t RELAY_INTERVAL       = 20;
const uint32_t LED_INTERVAL         = 50;
const uint32_t PROTECTION_INTERVAL  = 100;
const uint32_t PZEM_INTERVAL        = 1000;

//======================================================

void Scheduler_Init()
{
    timerButton = millis();
    timerIO = millis();
    timerRelay = millis();
    timerLED = millis();
    timerProtection = millis();
    timerPZEM = millis();
}

//======================================================

void Scheduler_Run()
{
    unsigned long now = millis();

    //---------------- Button ----------------
    if (now - timerButton >= BUTTON_INTERVAL)
    {
        timerButton = now;
        Button_Task();
    }

    //---------------- Digital Input ----------------
    if (now - timerIO >= IO_INTERVAL)
    {
        timerIO = now;
        IO_Task();
    }

    //---------------- Relay ----------------
    if (now - timerRelay >= RELAY_INTERVAL)
    {
        timerRelay = now;
        Relay_Task();
    }

    //---------------- LED ----------------
    if (now - timerLED >= LED_INTERVAL)
    {
        timerLED = now;
        LED_Task();
    }

    //---------------- Protection ----------------
    if (now - timerProtection >= PROTECTION_INTERVAL)
    {
        timerProtection = now;
        Protection_Task();
    }

    //---------------- PZEM ----------------
    if (now - timerPZEM >= PZEM_INTERVAL)
    {
        timerPZEM = now;
        PZEM_Task();
    }
}
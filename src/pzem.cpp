#include "pzem.h"

#include <PZEM004Tv30.h>

#include "config.h"

HardwareSerial PZEMSerial(1);

PZEM004Tv30 pzem(PZEMSerial, RX_PIN, TX_PIN);

//======================================================
// Data
//======================================================

static float voltage = NAN;
static float current = NAN;
static float power = NAN;
static float energy = NAN;
static float frequency = NAN;
static float pf = NAN;

static bool online = false;

//======================================================

void initPZEM()
{
    PZEMSerial.begin(
        9600,
        SERIAL_8N1,
        RX_PIN,
        TX_PIN);

    Serial.println("[PZEM] Initialized");
}

//======================================================

bool readPZEM()
{
    voltage = pzem.voltage();

    if (isnan(voltage))
    {
        online = false;
        return false;
    }

    current = pzem.current();
    power = pzem.power();
    energy = pzem.energy();
    frequency = pzem.frequency();
    pf = pzem.pf();

    online = true;

    return true;
}

//======================================================

float getVoltage()
{
    return voltage;
}

float getCurrent()
{
    return current;
}

float getPower()
{
    return power;
}

float getEnergy()
{
    return energy;
}

float getFrequency()
{
    return frequency;
}

float getPF()
{
    return pf;
}

bool isPZEMOnline()
{
    return online;
}
#ifndef GLOBALS_H
#define GLOBALS_H

struct ElectricalData
{
    float voltage = 0;
    float current = 0;
    float power = 0;
    float energy = 0;
    float frequency = 0;
    float pf = 0;
};

extern ElectricalData Meter;

//=====================================

struct DigitalInput
{
    bool di1 = false;
    bool di2 = false;
};

extern DigitalInput Input;

//=====================================

struct RelayOutput
{
    bool relay1 = false;
    bool relay2 = false;
};

extern RelayOutput Output;

//=====================================

struct SystemStatus
{
    bool wifiConnected = false;
    bool mqttConnected = false;
    bool configMode = false;
};

extern SystemStatus Status;

#endif
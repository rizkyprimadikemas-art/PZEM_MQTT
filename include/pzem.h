#ifndef PZEM_H
#define PZEM_H

#include <Arduino.h>
#include <PZEM004Tv30.h>
#include "config.h"

extern PZEM004Tv30 pzem;

struct PZEMData
{
    float voltage;
    float current;
    float power;
    float energy;
    float frequency;
    float pf;

    bool valid;
};

void initPZEM();

PZEMData readPZEM();

#endif
#ifndef PZEM_H
#define PZEM_H

#include <Arduino.h>

void initPZEM();

bool readPZEM();

float getVoltage();
float getCurrent();
float getPower();
float getEnergy();
float getFrequency();
float getPF();

bool isPZEMOnline();

#endif
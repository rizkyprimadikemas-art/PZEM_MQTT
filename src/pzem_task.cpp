#include "pzem_task.h"

#include <Arduino.h>
#include <PZEM004Tv30.h>

#include "config.h"
#include "globals.h"

//======================================================
// Hardware Serial
//======================================================

HardwareSerial PZEMSerial(1);
PZEM004Tv30 pzem(PZEMSerial, PZEM_RX_PIN, PZEM_TX_PIN);

//======================================================

void PZEM_Init()
{
    Serial.println();
    Serial.println("=================================");
    Serial.println("PZEM Initialize");
    Serial.println("=================================");
}

//======================================================

void PZEM_Task()
{
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    //--------------------------------------------------
    // Update hanya jika data valid
    //--------------------------------------------------

    if (!isnan(voltage))
        Meter.voltage = voltage;

    if (!isnan(current))
        Meter.current = current;

    if (!isnan(power))
        Meter.power = power;

    if (!isnan(energy))
        Meter.energy = energy;

    if (!isnan(frequency))
        Meter.frequency = frequency;

    if (!isnan(pf))
        Meter.pf = pf;

    //--------------------------------------------------
    // Debug Serial
    //--------------------------------------------------

    Serial.println();
    Serial.println("========== PZEM ==========");

    Serial.print("Voltage   : ");
    Serial.print(Meter.voltage);
    Serial.println(" V");

    Serial.print("Current   : ");
    Serial.print(Meter.current);
    Serial.println(" A");

    Serial.print("Power     : ");
    Serial.print(Meter.power);
    Serial.println(" W");

    Serial.print("Energy    : ");
    Serial.print(Meter.energy);
    Serial.println(" kWh");

    Serial.print("Frequency : ");
    Serial.print(Meter.frequency);
    Serial.println(" Hz");

    Serial.print("PF        : ");
    Serial.println(Meter.pf);

    Serial.println("==========================");
}
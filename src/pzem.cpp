#include "pzem.h"

HardwareSerial PZEMSerial(1);

PZEM004Tv30 pzem(PZEMSerial, RX_PIN, TX_PIN);

void initPZEM()
{
    Serial.println("=================================");
    Serial.println("Initializing PZEM...");
    Serial.println("=================================");

    PZEMSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

    delay(100);

    Serial.println("PZEM Ready");
}

PZEMData readPZEM()
{
    PZEMData data;

    data.voltage = pzem.voltage();
    data.current = pzem.current();
    data.power = pzem.power();
    data.energy = pzem.energy();
    data.frequency = pzem.frequency();
    data.pf = pzem.pf();

    data.valid = !isnan(data.voltage);

    if (!data.valid)
    {
        Serial.println("[PZEM] Read Failed");
    }

    return data;
}
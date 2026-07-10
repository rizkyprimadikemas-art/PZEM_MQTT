#include <Arduino.h>

#include "scheduler.h"

#include "button_task.h"
#include "led_task.h"
#include "protection.h"

#include "io_task.h"
#include "relay_task.h"
#include "pzem_task.h"

void setup()
{
    Serial.begin(115200);

    PZEM_Init();
    IO_Init();
    Relay_Init();
    Button_Init();
    LED_Init();

    Scheduler_Init();

    Serial.println();
    Serial.println("EMS Ecosystem Prototype");
}

void loop()
{
    Scheduler_Run();
}
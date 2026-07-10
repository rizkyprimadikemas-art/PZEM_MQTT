#include "button_task.h"
#include "config.h"

static bool buttonState = HIGH;
static bool lastButtonState = HIGH;

static bool shortPressFlag = false;
static bool longPressFlag = false;
static bool factoryResetFlag = false;

static unsigned long pressStartTime = 0;
static unsigned long debounceTime = 0;

const uint16_t DEBOUNCE_DELAY = 50;
const uint16_t LONG_PRESS_TIME = 3000;
const uint16_t FACTORY_RESET_TIME = 10000;

void Button_Init()
{
    pinMode(BTN_CONFIG, INPUT_PULLUP);
}

void Button_Task()
{
    bool reading = digitalRead(BTN_CONFIG);

    // Debounce
    if (reading != lastButtonState)
    {
        debounceTime = millis();
    }

    if ((millis() - debounceTime) > DEBOUNCE_DELAY)
    {
        if (reading != buttonState)
        {
            buttonState = reading;

            //---------------------------------
            // Tombol ditekan
            //---------------------------------
            if (buttonState == LOW)
            {
                pressStartTime = millis();

                longPressFlag = false;
                factoryResetFlag = false;
            }

            //---------------------------------
            // Tombol dilepas
            //---------------------------------
            else
            {
                unsigned long pressDuration = millis() - pressStartTime;

                if (pressDuration < LONG_PRESS_TIME)
                {
                    shortPressFlag = true;
                }
            }
        }
    }

    //---------------------------------
    // Long Press
    //---------------------------------

    if (buttonState == LOW)
    {
        unsigned long duration = millis() - pressStartTime;

        if ((duration >= LONG_PRESS_TIME) && !longPressFlag)
        {
            longPressFlag = true;
        }

        if ((duration >= FACTORY_RESET_TIME) && !factoryResetFlag)
        {
            factoryResetFlag = true;
        }
    }

    lastButtonState = reading;
}

bool Button_IsPressed()
{
    return (buttonState == LOW);
}

bool Button_ShortPress()
{
    if (shortPressFlag)
    {
        shortPressFlag = false;
        return true;
    }

    return false;
}

bool Button_LongPress()
{
    if (longPressFlag)
    {
        longPressFlag = false;
        return true;
    }

    return false;
}

bool Button_FactoryReset()
{
    if (factoryResetFlag)
    {
        factoryResetFlag = false;
        return true;
    }

    return false;
}
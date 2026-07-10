#ifndef BUTTON_TASK_H
#define BUTTON_TASK_H

#include <Arduino.h>

void Button_Init();
void Button_Task();

bool Button_IsPressed();
bool Button_ShortPress();
bool Button_LongPress();
bool Button_FactoryReset();

#endif
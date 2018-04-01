#include "io.hpp"
#include <stdio.h>
#include "gpio.hpp"
#include "printf_lib.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "utilities.h"
extern SemaphoreHandle_t SwitchLock;

bool Enable_eint3(int pinNumber1,int pinNumber2);
void Handle_General_Interrupt();
void Switch1();

void Switch2();

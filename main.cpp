/**
 * @brief Gardener main application.
 */

#include "main.h"

#include <iostream>
#include <wiringPi.h>

#include "config.h"
#include "gardener.h"
#include "pump.h"
#include "timer.h"

#include <ctime>

using namespace gardener;
using namespace std;

const int PWM0_pin = 1; /* GPIO 1 as per WiringPi, GPIO18 as per BCM */
const int PWM1_pin = 24;

/**
 * @brief   Gardener execution entry point.
 *
 * @param   [in] argc   CLI argument count.
 * @param   [in] argv   CLI argument vector.
 *
 * @returns 0 if executed successfully, else error code.
 */
int main(int argc, char *argv[])
{
    cout << argv[0]
         << " Version "
         << Gardener_VERSION_MAJOR
         << "."
         << Gardener_VERSION_MINOR
         << endl;

    if (wiringPiSetup() == -1)
    {
        exit(1);
    }

    const int msPerDay = 24 * 60 * 60 * 1000;
    const int waterTimeMs = 50 * 1000;
    const int waitTimeMs = msPerDay - waterTimeMs;

    IConfig *cfg = new Config(waitTimeMs, waterTimeMs);
    ITimer *gardenerTmr = new Timer();
    ITimer *dwellTmr = new Timer();
    IPump *pump = new Pump(PWM0_pin, PWM1_pin, *dwellTmr);
    IGardener *gardener = new Gardener(*cfg, *pump, *gardenerTmr);

    while (1)
    {
        pump->transition();
        gardener->transition();

        pump->execute();
        gardener->execute();

        delay(10);
    }
}

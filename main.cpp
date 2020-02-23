/**
 * @brief Gardener main application.
 */

#include "main.h"

#include <iostream>
#include <wiringPi.h>

#include "config.h"
#include "igardener.h"
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

    cout << CLOCKS_PER_SEC << endl;

    if (wiringPiSetup() == -1)
    {
        exit(1);
    }

    IConfig *cfg = new Config(10, 1);
    ITimer *gardenerTmr = new Timer();
    ITimer *dwellTmr = new Timer();
    IPump *pump = new Pump(PWM0_pin, PWM1_pin, *cfg, *dwellTmr);

    while (1)
    {
        int speed;

        for (speed = 0; speed <= 100; speed += 10)
        {
            pump->requestChangeSpeed(speed);
            while(!pump->isSpeedSteady())
            {
                pump->transition();
                pump->execute();
                delay(1);
            }

            cout << speed << endl;
        }

        gardenerTmr->reload(100);
        while (!gardenerTmr->isExpired())
        {
            delay(1);
        }

        for (speed = 100; speed >= 0; speed -= 10)
        {
            pump->requestChangeSpeed(speed);
            while(!pump->isSpeedSteady())
            {
                pump->transition();
                pump->execute();
                delay(1);
            }

            cout << speed << endl;
        }

        gardenerTmr->reload(1000);
        while (!gardenerTmr->isExpired())
        {
            delay(1);
        }

        for (speed = 0; speed <= 100; speed += 10)
        {
            pump->requestChangeSpeed(-speed);
            while(!pump->isSpeedSteady())
            {
                pump->transition();
                pump->execute();
                delay(1);
            }

            cout << speed << endl;
        }

        gardenerTmr->reload(100);
        while (!gardenerTmr->isExpired())
        {
            delay(1);
        }

        for (speed = 100; speed >= 0; speed -= 10)
        {
            pump->requestChangeSpeed(-speed);
            while(!pump->isSpeedSteady())
            {
                pump->transition();
                pump->execute();
                delay(1);
            }

            cout << speed << endl;
        }

        gardenerTmr->reload(1000);
        while (!gardenerTmr->isExpired())
        {
            delay(1);
        }
    }
}

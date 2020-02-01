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

    IConfig *cfg = new Config(10, 1);
    ITimer *gardenerTmr = new Timer();
    ITimer *fwdDwellTmr = new Timer();
    ITimer *revDwellTmr = new Timer();
    IPump *fwdPump = new Pump(PWM0_pin, *cfg, *fwdDwellTmr);
    IPump *revPump = new Pump(PWM1_pin, *cfg, *revDwellTmr);

    while (1)
    {
        int speed;

        for (speed = 0; speed <= 100; speed += 10)
        {
            fwdPump->requestChangeSpeed(speed);
            while(!fwdPump->isSpeedChanged())
            {
                fwdPump->transition();
                fwdPump->execute();
                delay(100);
            }

            cout << speed << endl;
        }

        gardenerTmr->reload(1);
        while (!gardenerTmr->isExpired())
        {
            delay(100);
        }

        for (speed = 100; speed >= 0; speed -= 10)
        {
            fwdPump->requestChangeSpeed(speed);
            while(!fwdPump->isSpeedChanged())
            {
                fwdPump->transition();
                fwdPump->execute();
                delay(100);
            }

            cout << speed << endl;
        }

        gardenerTmr->reload(10);
        while (!gardenerTmr->isExpired())
        {
            delay(100);
        }

        for (speed = 0; speed <= 100; speed += 10)
        {
            revPump->requestChangeSpeed(speed);
            while(!revPump->isSpeedChanged())
            {
                revPump->transition();
                revPump->execute();
                delay(100);
            }

            cout << speed << endl;
        }

        gardenerTmr->reload(1);
        while (!gardenerTmr->isExpired())
        {
            delay(100);
        }

        for (speed = 100; speed >= 0; speed -= 10)
        {
            revPump->requestChangeSpeed(speed);
            while(!revPump->isSpeedChanged())
            {
                revPump->transition();
                revPump->execute();
                delay(100);
            }

            cout << speed << endl;
        }

        gardenerTmr->reload(10);
        while (!gardenerTmr->isExpired())
        {
            delay(100);
        }
    }
}

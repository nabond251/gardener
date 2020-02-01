/**
 * Defines gardener pump controller.
 */

#include "pump.h"

#include <algorithm>
#include <wiringPi.h>

using namespace gardener;
using namespace std;

const int Pump::deltaSpeed = 1;
const int Pump::dwellTime = 1;
const int Pump::dutyPerSpeed = 10485;
const int Pump::dutyRes = 10;

Pump::Pump(
    const int pwmPin,
    IConfig &config,
    ITimer &dwellTimer)
    : pwmPin(pwmPin)
    , config(config)
    , dwellTimer(dwellTimer)
    , currentSpeed(0)
    , requestedSpeed(-1)
    , currentState(IDLE)
{
    pinMode(this->pwmPin, PWM_OUTPUT); /* set PWM pin as output */
}

void Pump::requestChangeSpeed(const int newSpeed)
{
    this->requestedSpeed = newSpeed;
}

bool Pump::isSpeedChanged(void)
{
    return this->requestedSpeed == this->currentSpeed;
}

void Pump::transition(void)
{
    switch (this->currentState)
    {
        case IDLE:
        default:
            if (this->requestedSpeed >= 0 &&
                this->requestedSpeed != this->currentSpeed)
            {
                this->currentState = CHANGE;
            }

            break;

        case CHANGE:
            if (this->requestedSpeed == this->currentSpeed)
            {
                this->currentState = IDLE;
            }
            else
            {
                this->currentState = DWELL;
            }

            break;

        case DWELL:
            if (this->dwellTimer.isExpired())
            {
                this->currentState = CHANGE;
            }

            break;
    }
}

void Pump::execute(void)
{
    switch (this->currentState)
    {
        case IDLE:
        case DWELL:
        default:
            break;

        case CHANGE:
            if (this->requestedSpeed > this->currentSpeed)
            {
                // Ramp up
                this->setCurrentSpeed(min(
                    this->requestedSpeed,
                    this->currentSpeed + deltaSpeed));
            }
            else
            {
                // Ramp down
                this->setCurrentSpeed(max(
                    this->requestedSpeed,
                    this->currentSpeed - deltaSpeed));
            }

            this->dwellTimer.reload(dwellTime);

            break;
    }
}

void Pump::setCurrentSpeed(const int newSpeed)
{
    int duty = newSpeed * dutyPerSpeed >> dutyRes;
    pwmWrite(this->pwmPin, duty); /* provide PWM value for duty cycle */
    this->currentSpeed = newSpeed;
}

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
const int Pump::dutyScaleBits = 2;
const int Pump::dutyDeadband = 623;

Pump::Pump(
    const int fwdPin,
    const int revPin,
    IConfig &config,
    ITimer &dwellTimer)
    : fwdPin(fwdPin)
    , revPin(revPin)
    , config(config)
    , dwellTimer(dwellTimer)
    , currentSpeed(0)
    , requestedSpeed(0)
    , currentState(STEADY)
{
    /* set PWM pins as output */
    pinMode(this->fwdPin, PWM_OUTPUT);
    pinMode(this->revPin, PWM_OUTPUT);
}

void Pump::requestChangeSpeed(const int newSpeed)
{
    this->requestedSpeed = newSpeed;
}

bool Pump::isSpeedSteady(void)
{
    return this->requestedSpeed == this->currentSpeed;
}

void Pump::transition(void)
{
    switch (this->currentState)
    {
        case STEADY:
        default:
            if (!this->isSpeedSteady())
            {
                this->currentState = CHANGE;
            }

            break;

        case CHANGE:
            if (this->isSpeedSteady())
            {
                this->currentState = STEADY;
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
        case STEADY:
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
    int fwdDuty = 0;
    int revDuty = 0;

    if (newSpeed > 0)
    {
        fwdDuty = (newSpeed << dutyScaleBits) + dutyDeadband;
    }
    else if (newSpeed < 0)
    {
        revDuty = ((-newSpeed) << dutyScaleBits) + dutyDeadband;
    }

    /* provide PWM value for duty cycle */
    pwmWrite(this->fwdPin, fwdDuty);
    pwmWrite(this->revPin, revDuty);

    this->currentSpeed = newSpeed;
}

/**
 * Defines gardener controller.
 */

#include "gardener.h"

using namespace gardener;
using namespace std;

const int Gardener::waitSpeed = 0;
const int Gardener::waterSpeed = 100;

Gardener::Gardener(
    IConfig &config,
    IPump &pump,
    ITimer &timer)
    : config(config)
    , pump(pump)
    , timer(timer)
    , currentState(IDLE)
{
}

void Gardener::transition(void)
{
    switch (this->currentState)
    {
        case IDLE:
        default:
            this->currentState = START_WAIT;
            break;

        case START_WAIT:
            this->currentState = WAIT;
            break;

        case WAIT:
            if (this->timer.isExpired())
            {
                this->currentState = START_RAMP_UP;
            }

            break;

        case START_RAMP_UP:
            this->currentState = RAMP_UP;
            break;

        case RAMP_UP:
            if (this->pump.isSpeedSteady())
            {
                this->currentState = START_WATER;
            }

            break;

        case START_WATER:
            this->currentState = WATER;
            break;

        case WATER:
            if (this->timer.isExpired())
            {
                this->currentState = START_RAMP_DOWN;
            }

            break;

        case START_RAMP_DOWN:
            this->currentState = RAMP_DOWN;
            break;

        case RAMP_DOWN:
            if (this->pump.isSpeedSteady())
            {
                this->currentState = START_WAIT;
            }

            break;
    }
}

void Gardener::execute(void)
{
    switch (this->currentState)
    {
        case START_WAIT:
            this->timer.reload(this->config.getWaitTime());
            break;

        case START_RAMP_UP:
            this->pump.requestChangeSpeed(100);
            break;

        case START_WATER:
            this->timer.reload(this->config.getWaterTime());
            break;

        case START_RAMP_DOWN:
            this->pump.requestChangeSpeed(0);
            break;

        case IDLE:
        case WAIT:
        case RAMP_UP:
        case WATER:
        case RAMP_DOWN:
        default:
            break;
    }
}

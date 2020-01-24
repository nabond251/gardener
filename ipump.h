#ifndef I_PUMP_H
#define I_PUMP_H

#include "istatemachine.h"

namespace gardener
{
    class IPump : public IStateMachine
    {
        public:
            /*
             * Request the pump to transition to the given speed.
             *
             * newSpeed (in) - value from 0-1000 indicating percentage of
             *                 total operating speed with resolution of 0.1%
             *                 per count.
             *
             * Does not effect an immediate transition; only requests that
             * the transition begin.  Use isSpeedChanged to check that speed
             * has been attained.
             */
            virtual void requestChangeSpeed(const int newSpeed) = 0;

            /*
             * Checks if the speed requested in requestChangeSpeed has been
             * attained.
             *
             * Returns true if pump is operating at speed requested by latest
             * call to requestChangeSpeed; or
             * false if requestChangeSpeed has not been called or pump is
             * changing to requested speed.
             */
            virtual bool isSpeedChanged(void) = 0;
    };
}

#endif /* I_PUMP_H */

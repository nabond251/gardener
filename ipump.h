/**
 * @brief Declares interface for gardener pump controller.
 */

#ifndef I_PUMP_H
#define I_PUMP_H

#include "istatemachine.h"

namespace gardener
{
    /**
     * @brief Gardener pump controller interface.
     */
    class IPump : public IStateMachine
    {
        public:
            /**
             * @brief   Requests the pump to transition to the given speed.
             *
             * @param   [in] newSpeed   Value from 0-1000 indicating
             *                          percentage of total operating speed
             *                          with resolution of 0.1% per count.
             *
             * @note    Does not effect an immediate transition; only requests
             *          that the transition begin.  Use @ref isSpeedChanged to
             *          check that the speed has been attained.
             */
            virtual void requestChangeSpeed(const int newSpeed) = 0;

            /**
             * @brief   Checks if the speed requested has been attained.
             *
             * @returns true if pump is operating at speed requested by latest
             *          call to @ref requestChangeSpeed, or if @ref
             *          requestChangeSpeed has not been called; or false if
             *          @ref requestChangeSpeed has been called and pump is
             *          changing to requested speed.
             */
            virtual bool isSpeedSteady(void) = 0;
    };
}

#endif /* I_PUMP_H */

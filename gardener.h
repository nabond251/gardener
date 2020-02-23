/**
 * @brief Declares gardener controller.
 */

#ifndef GARDENER_H
#define GARDENER_H

#include "iconfig.h"
#include "igardener.h"
#include "ipump.h"
#include "itimer.h"

namespace gardener
{
    /**
     * @brief Gardener controller.
     */
    class Gardener : public IGardener
    {
        public:
            /**
             * @brief   Initializes a new instance of the @ref Gardener class.
             *
             * @param   [in,out] config     Gardener configuration manager.
             * @param   [in,out] pump       Gardener watering pump.
             * @param   [in,out] timer      Timer for resting/watering.
             */
            Gardener(
                IConfig &config,
                IPump &pump,
                ITimer &timer);

            virtual void transition(void);
            virtual void execute(void);

        private:
            enum state
            {
                IDLE,               /**< Start state */
                START_WAIT,         /**< Reload wait timer */
                WAIT,               /**< Waiting to water */
                START_RAMP_UP,      /**< Request watering pump speed */
                RAMP_UP,            /**< Changing to watering pump speed */
                START_WATER,        /**< Reload watering timer */
                WATER,              /**< Watering */
                START_RAMP_DOWN,    /**< Request waiting pump speed */
                RAMP_DOWN,          /**< Changing to waiting pump speed */
            };

            static const int waitSpeed;
            static const int waterSpeed;

            IConfig &config;
            IPump &pump;
            ITimer &timer;

            state currentState;
    };
}

#endif /* GARDENER_H */

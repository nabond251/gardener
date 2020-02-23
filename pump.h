/**
 * @brief Declares gardener pump controller.
 */

#ifndef PUMP_H
#define PUMP_H

#include "iconfig.h"
#include "ipump.h"
#include "itimer.h"

namespace gardener
{
    /**
     * @brief Gardener pump controller.
     */
    class Pump : public IPump
    {
        public:
            /**
             * @brief   Initializes a new instance of the @ref Pump class.
             *
             * @param   [in] fwdPin         WiringPi PWM pin to control pump
                                            in forward direction.
             * @param   [in] revPin         WiringPi PWM pin to control pump
                                            in reverse direction.
             * @param   [in,out] config     Owning gardener's configuration.
             * @param   [in,out] dwellTimer Timer for dwelling during ramp-up.
             */
            Pump(
                const int fwdPin,
                const int revPin,
                IConfig &config,
                ITimer &dwellTimer);

            virtual void requestChangeSpeed(const int newSpeed);
            virtual bool isSpeedSteady(void);

            virtual void transition(void);
            virtual void execute(void);

        private:
            enum state
            {
                STEADY, /**< At requested speed */
                CHANGE, /**< Changing to requested speed */
                DWELL,  /**< Dwelling at changed speed */
            };

            static const int deltaSpeed;
            static const int dwellTime;
            static const int dutyScaleBits;
            static const int dutyDeadband;

            int fwdPin;
            int revPin;
            IConfig &config;
            ITimer &dwellTimer;

            int currentSpeed;
            int requestedSpeed;
            state currentState;

            void setCurrentSpeed(const int newSpeed);
    };
}

#endif /* PUMP_H */

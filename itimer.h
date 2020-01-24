#ifndef I_TIMER_H
#define I_TIMER_H

#include "istatemachine.h"

namespace gardener
{
    class ITimer : public IStateMachine
    {
        public:
            /*
             * Reloads the timer.
             *
             * newTime (in) - new timer value to reload in seconds.
             *
             * Call isExpired to check if newTime has elapsed.
             */
            virtual void reload(const int newTime) = 0;

            /*
             * Checks if the timer has expired.
             *
             * Returns true if time reloaded in reload has elapsed; or
             * false if timer has not been loaded or time has not elapsed.
             */
            virtual bool isExpired(void) = 0;
    };
}

#endif /* I_TIMER_H */

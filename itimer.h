/**
 * @brief Declares interface for gardening sequencing timer.
 */

#ifndef I_TIMER_H
#define I_TIMER_H

#include "istatemachine.h"

namespace gardener
{
    /**
     * @brief Gardener sequencing timer interface.
     */
    class ITimer
    {
        public:
            /**
             * @brief   Reloads the timer.
             *
             * @param   [in] newTime    New timer value to reload in seconds.
             *
             * @note    Call @ref isExpired to check if @p newTime has
             *          elapsed.
             */
            virtual void reload(const int newTime) = 0;

            /**
             * @brief   Checks if the timer has expired.
             *
             * @returns true if time reloaded in @ref reload has elapsed;
             *          or false if timer has not been loaded or time has not
             *          elapsed.
             */
            virtual bool isExpired(void) = 0;
    };
}

#endif /* I_TIMER_H */

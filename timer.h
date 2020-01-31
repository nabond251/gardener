/**
 * @brief Declares gardening sequencing timer.
 */

#ifndef TIMER_H
#define TIMER_H

#include <ctime>

#include "itimer.h"

namespace gardener
{
    /**
     * @brief Gardener sequencing timer.
     */
    class Timer : public ITimer
    {
        public:
            /**
             * Initializes a new instance of the @ref Timer class.
             */
            Timer(void);

            virtual void reload(const int newTime);
            virtual bool isExpired(void);

        private:
            time_t endTime;
    };
}

#endif /* I_TIMER_H */

/**
 * @brief Declares gardening sequencing timer.
 */

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

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
            std::chrono::steady_clock::time_point endTime;
    };
}

#endif /* I_TIMER_H */

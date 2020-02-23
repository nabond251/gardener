/**
 * Defines gardener sequencing timer.
 */

#include "timer.h"

#include <limits>

using namespace gardener;
using namespace std;

Timer::Timer(void)
    : endTime(numeric_limits<time_t>::max())
{
}

void Timer::reload(const int newTime)
{
    const int msPerSec = 1000;
    const int clocksCorrection = 4;
    const int clocksPerMs = CLOCKS_PER_SEC / clocksCorrection / msPerSec;

    int newClocks = newTime * clocksPerMs;
    this->endTime = clock() + newClocks;
}

bool Timer::isExpired(void)
{
    time_t currentClock = clock();
    return currentClock >= this->endTime;
}

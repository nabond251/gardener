/**
 * Defines gardener sequencing timer.
 */

#include "timer.h"

using namespace gardener;
using namespace std;

Timer::Timer(void)
    : endTime(chrono::steady_clock::duration::max())
{
}

void Timer::reload(const int newTime)
{
    this->endTime = chrono::steady_clock::now() + chrono::milliseconds(newTime);
}

bool Timer::isExpired(void)
{
    chrono::steady_clock::time_point currentClock = chrono::steady_clock::now();
    return currentClock >= this->endTime;
}

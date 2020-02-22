/**
 * Defines gardener sequencing timer.
 */

#include "timer.h"

#include <limits>

#define MS_PER_SEC 1000

using namespace gardener;
using namespace std;

Timer::Timer(void)
    : endTime(numeric_limits<time_t>::max())
{
}

void Timer::reload(const int newTime)
{
    int newClocks = (newTime * CLOCKS_PER_SEC) / MS_PER_SEC;
    this->endTime = clock() + newClocks;
}

bool Timer::isExpired(void)
{
    time_t currentClock = clock();
    return currentClock < this->endTime;
}

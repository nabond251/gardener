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
    this->endTime = time(NULL) + newTime;
}

bool Timer::isExpired(void)
{
    time_t currentTime = time(NULL);
    return difftime(currentTime, this->endTime) > 0.0;
}

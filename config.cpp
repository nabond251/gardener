/**
 * Defines gardener configuration manager.
 */

#include "config.h"

using namespace gardener;
using namespace std;

Config::Config(
    const int waitTime,
    const int waterTime)
    : waitTime(waitTime)
    , waterTime(waterTime)
{
}

int Config::getWaitTime(void)
{
    return this->waitTime;
}

int Config::getWaterTime(void)
{
    return this->waterTime;
}


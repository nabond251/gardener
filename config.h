/**
 * @brief Declares gardener configuration manager.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "iconfig.h"

namespace gardener
{
    /**
     * @brief Gardener configuration manager.
     */
    class Config : public IConfig
    {
        public:
            /**
             * @brief   Initializes a new instance of the @ref Config class.
             *
             * @param   [in] waitTime   Time to wait before watering.
             * @param   [in] waterTime  Time to water before waiting.
             */
            Config(
                const int waitTime,
                const int waterTime);

            virtual int getWaitTime(void);
            virtual int getWaterTime(void);

        private:
            int waitTime;
            int waterTime;
    };
}

#endif /* CONFIG_H */

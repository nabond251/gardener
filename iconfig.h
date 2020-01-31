/**
 * @brief Declares interface for gardener configuration manager.
 */

#ifndef I_CONFIG_H
#define I_CONFIG_H

namespace gardener
{
    /**
     * @brief Gardener configuration manager.
     */
    class IConfig
    {
        public:
            /**
             * @brief   Gets the configured wait time.
             *
             * @returns the time to wait before watering in seconds.
             */
            virtual int getWaitTime(void) = 0;

            /**
             * @brief   Gets the configured water time.
             *
             * @returns the time to water before waiting in seconds.
             */
            virtual int getWaterTime(void) = 0;
    };
}

#endif /* I_CONFIG_H */

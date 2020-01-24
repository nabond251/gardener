#ifndef I_CONFIG_H
#define I_CONFIG_H

namespace gardener
{
    class IConfig
    {
        public:
            /*
             * Gets the configured wait time.
             *
             * Returns the time to wait before watering in seconds.
             */
            virtual int getWaitTime(void) = 0;

            /*
             * Gets the configured water time.
             *
             * Returns the time to water before waiting in seconds.
             */
            virtual int getWaterTime(void) = 0;
    };
}

#endif /* I_CONFIG_H */


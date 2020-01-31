/**
 * @brief Declares interface for generic state machine component.
 */

#ifndef I_STATE_MACHINE_H
#define I_STATE_MACHINE_H

namespace gardener
{
    /**
     * @brief Generic state machine component.
     */
    class IStateMachine
    {
        public:
            /**
             * @brief   Prepare state for execution.
             *
             * @note    Should always be called before execute.
             * @note    Should never call execute.
             */
            virtual void transition(void) = 0;

            /**
             * @brief   Execute per current state.
             *
             * @note    Should always be called after transition.
             * @note    Should never call transition.
             */
            virtual void execute(void) = 0;
    };
}

#endif /* I_STATE_MACHINE_H */

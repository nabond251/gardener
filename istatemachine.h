#ifndef I_STATE_MACHINE_H
#define I_STATE_MACHINE_H

namespace gardener
{
    class IStateMachine
    {
        public:
            /*
             * Prepare state for execution.
             * Should always be called before execute.
             * Should never call execute.
             */
            virtual void transition(void) = 0;

            /*
             * Execute per current state.
             * Should always be called after transition.
             * Should never call transition.
             */
            virtual void execute(void) = 0;
    };
}

#endif /* I_STATE_MACHINE_H */

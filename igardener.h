/**
 * Declares top-level interface for gardener.
 */

#ifndef I_GARDENER_H
#define I_GARDENER_H

#include "istatemachine.h"

/**
 * Top-level gardener namespace.
 */
namespace gardener
{
    /**
     * Top-level gardener component.
     */
    class IGardener : public IStateMachine
    {
    };
}

#endif /* I_GARDENER_H */

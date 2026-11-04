// STAND-IN: RuffKing cStateMachine has one CurrentState pointer and no virtuals.
// CD2 cEquipment's constructor (0x82604AF8) initializes it at +0x7A0,
// immediately after cNetDynamicBody. Remaining state-machine methods are not recovered.
#ifndef FUN_RUNTIME_CSTATEMACHINE_H
#define FUN_RUNTIME_CSTATEMACHINE_H
#include "cd2/layout.h"
namespace Fun_Runtime
{
    class State;
    class cStateMachine
    {
    private:
        State *CurrentState;
        CD2_LAYOUT_CHECKS(cStateMachine,
            CD2_SIZE(cStateMachine, 4)
            CD2_OFFSET(cStateMachine, CurrentState, 0))
    };
}
#endif

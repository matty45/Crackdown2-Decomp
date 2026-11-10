// STAND-IN: RuffKing cStateMachine has one CurrentState pointer and no virtuals.
// CD2 cEquipment's constructor (0x82604AF8) initializes it at +0x7A0,
// immediately after cNetDynamicBody. cPivotBasedProp's constructor (0x8273AFF8) zeroes it at +0xE30 before the
// vptr stores (inline default constructor). GoTo_State is CD2 0x8264B3E0 (29 callers); the IsIn* state queries
// (0x82736F58, ...) inline IsIn_State as one compare of CurrentState.
#ifndef FUN_RUNTIME_CSTATEMACHINE_H
#define FUN_RUNTIME_CSTATEMACHINE_H
#include "cd2/layout.h"
namespace Fun_Runtime
{
    class State;
    class cStateMachine
    {
    public:
        cStateMachine() : CurrentState(0) {}
        void ProcessStateMachine();
        bool GoTo_State(Fun_Runtime::State *NextState);
        bool IsIn_State(Fun_Runtime::State *pState) const { return CurrentState == pState; }
        Fun_Runtime::State *RetCurrentState() { return CurrentState; }
    private:
        State *CurrentState;
        CD2_LAYOUT_CHECKS(cStateMachine,
            CD2_SIZE(cStateMachine, 4)
            CD2_OFFSET(cStateMachine, CurrentState, 0))
    };
}
#endif

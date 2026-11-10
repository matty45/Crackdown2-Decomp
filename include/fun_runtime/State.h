// Fun_Runtime::State (Crackdown 2): STAND-IN from RuffKing's declaration (dumped with cEquipment.h): a polymorphic
// state object with a wide name pointer at +4, 8 bytes. Evidence in CD2: the static-local state singletons of
// cPivotBasedProp/cHingedProp (0x8273AFA8, 0x82737300, ...) store the vptr at +0 and L"" (0x8211ED48) at +4, with no
// destructor registration; state tables (0x8213DFE0, 0x8213EF60) start with BeginState, EndState and an empty Process
// (0x82580578, blr).
#ifndef FUN_RUNTIME_STATE_H
#define FUN_RUNTIME_STATE_H

#include "cd2/layout.h"

namespace Fun_Runtime
{
    class cStateMachine;

    class State
    {
    public:
        State() : m_sName(L"") {}
        virtual void BeginState(Fun_Runtime::cStateMachine *);
        virtual void EndState(Fun_Runtime::cStateMachine *);
        virtual void Process(Fun_Runtime::cStateMachine *) {}
        const wchar_t *RetName() const;
        void SetName(const wchar_t *);

    private:
        const wchar_t *m_sName;

        CD2_LAYOUT_CHECKS(State,
            CD2_SIZE(State, 8)
            CD2_OFFSET(State, m_sName, 4))
    };
}

#endif // FUN_RUNTIME_STATE_H

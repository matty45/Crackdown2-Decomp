// STAND-IN: RuffKing NPCArmedBehaviour derives from NPCBehaviour. CD2's
// StaticCreateClass (0x824A7E80) gives size 0xF0; constructor 0x824A8070
// confirms the reference-named vectors and state fields after the 0xC0 base.
#ifndef AI_NPCARMEDBEHAVIOUR_H
#define AI_NPCARMEDBEHAVIOUR_H
#include "AI/NPCBehaviour.h"
namespace AI
{
    class NPCArmedBehaviour : public NPCBehaviour
    {
    public:
        enum eState
        {
            eMAIN_Null = 0, eMAIN_Idle, eMAIN_Investigate, eMAIN_Patrol,
            eMAIN_Attack, eMAIN_Cover, eMAIN_Retreat, eMAIN_ReactResupply,
            eMAIN_Ambient, eMAIN_Drive, eNumMainStates
        };
        // CD2 constructor 0x824A8070 installs 132-slot table 0x821089B0.
        // State callback names follow RuffKing; remaining vf names are unresolved.
        virtual void vf96(); // primary slot 96
        virtual void OnReplicatedEnter(unsigned char); // primary slot 97
        virtual void ChangeMainState(eState); // primary slot 98
        virtual void ChangeSubState(unsigned int); // primary slot 99
        virtual void EnterSubState(unsigned int); // primary slot 100
        virtual void ExitSubState(); // primary slot 101
        // CD2 holds _purecall in slots 102..106, 109 and 110.
        virtual void OnIdle() = 0; // primary slot 102
        virtual void OnInvestigating() = 0; // primary slot 103
        virtual void OnPatrolling() = 0; // primary slot 104
        virtual void OnAttacking() = 0; // primary slot 105
        virtual void OnCover() = 0; // primary slot 106
        virtual void OnRetreating(); // primary slot 107
        virtual void OnReactResupply(); // primary slot 108
        virtual void OnAmbient() = 0; // primary slot 109
        virtual void OnDrive() = 0; // primary slot 110
        virtual void EnterSubStateIdle(); // primary slot 111
        virtual void EnterSubStateInvestigating(); // primary slot 112
        virtual void EnterSubStatePatrolling(); // primary slot 113
        virtual void EnterSubStateAttacking(); // primary slot 114
        virtual void EnterSubStateCover(); // primary slot 115
        virtual void EnterSubStateRetreating(); // primary slot 116
        virtual void EnterSubStateReactResupply(); // primary slot 117
        virtual void EnterSubStateAmbient(); // primary slot 118
        virtual void EnterSubStateDrive(); // primary slot 119
        virtual void ExitSubStateIdle(); // primary slot 120
        virtual void ExitSubStateInvestigating(); // primary slot 121
        virtual void ExitSubStatePatrolling(); // primary slot 122
        virtual void ExitSubStateAttacking(); // primary slot 123
        virtual void ExitSubStateCover(); // primary slot 124
        virtual void ExitSubStateRetreating(); // primary slot 125
        virtual void ExitSubStateReactResupply(); // primary slot 126
        virtual void ExitSubStateAmbient(); // primary slot 127
        virtual void ExitSubStateDrive(); // primary slot 128
        virtual void vf129(); // primary slot 129
        virtual void vf130(); // primary slot 130
        virtual void vf131(); // primary slot 131

        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x8381E770: set by the initializer 0x82F91630 from StaticCreateClass; RetClass and IsA read it.
        static const Fun_Runtime::cClass *ms_pNPCArmedBehaviourClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
    protected:
        Fun_Runtime::Vec3 m_vInvestigationPoint;
        Fun_Runtime::Vec3 m_vGuardPoint;
        eState m_nMainState;
        unsigned int m_nSubState;
    private:
        bool m_bIsAmbient;
        int m_nAmbientAnimID;
    public:
        // Out of line: CD2 0x824A8070 (it first calls NPCBehaviour's 0x824A89C8).
        NPCArmedBehaviour();
        // Inline and empty: the deleting destructor 0x824C17F0 (shared by CellGuard, CellMinigun, CellRocket and
        // Peacekeeper, identical code folded) restores this class's vtables (0x821089B0, which its constructor installs)
        // and calls ~cNonGameBase directly; NPCBehaviour's own destructor stores none (~cPedestrianBase, 0x824A8EB8).
        virtual ~NPCArmedBehaviour() {}
    private:
        CD2_LAYOUT_CHECKS(NPCArmedBehaviour,
            CD2_SIZE(NPCArmedBehaviour, 0xF0)
            CD2_OFFSET(NPCArmedBehaviour, m_vInvestigationPoint, 0xC0)
            CD2_OFFSET(NPCArmedBehaviour, m_vGuardPoint, 0xD0)
            CD2_OFFSET(NPCArmedBehaviour, m_nMainState, 0xE0)
            CD2_OFFSET(NPCArmedBehaviour, m_nSubState, 0xE4)
            CD2_OFFSET(NPCArmedBehaviour, m_bIsAmbient, 0xE8)
            CD2_OFFSET(NPCArmedBehaviour, m_nAmbientAnimID, 0xEC))

    public:
        // CD2 table 0x821089B0 differs from NPCBehaviour at these inherited slots.
        virtual void OnEnterReplicatedState(unsigned char); // slot 72: 0x824A7E70
        virtual void Slot79(); // slot 79: 0x824A82C8
        virtual void SetReactResupplyPoint(const Fun_Runtime::Vec3 &, const Fun_Runtime::Vec3 &); // slot 85: 0x824A8110
        virtual unsigned char GetStateReplicationInfo() const; // slot 89: 0x824A7E60

    public:
        // CD2 table 0x821089B0 differs from NPCBehaviour at these inherited slots.

    public:
        // CD2 table 0x821089B0: overrides relative to NPCBehaviour.
        virtual void OnEnter(); // slot 68: 0x824A81A8
        virtual void OnExit(); // slot 69: 0x824A8278
        virtual void Slot71(); // slot 71: 0x824A8330, main-state dispatcher; original name unresolved
    };
}
#endif

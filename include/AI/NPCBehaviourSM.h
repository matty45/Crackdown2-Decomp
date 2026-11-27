// AI::NPCBehaviourSM (Crackdown 2): the state-machine NPC behaviour. Burn's NPCBehaviourStateMachine.h: an NPCBehaviour
// with the current state and its index after the base's fields. CD2's constructor 0x824ABA30 calls NPCBehaviour's
// (0x824A89C8), installs the tables 0x821091A8 (primary, 101 slots), 0x8210B4D8, 0x8210BEB0, 0x8210933C and 0x8212CED0,
// and zeroes m_pCurrentState (0xC0) and m_nState (0xC4); NPCBehaviour's 16-byte alignment makes the class 0xD0 (its
// derived classes' first own fields are at 0xD0). Its primary table differs from NPCBehaviour's 0x82108C08 in slots
// 71, 73, 81 and 89 (the overrides below) and adds Burn's five virtuals as slots 96..100 (GetState is _purecall);
// its registered-class table 0x8210933C holds its own RetClass and IsA (0x824AB9C0 / 0x824AB9D0).
// CD2 registers the class under NPCBehaviour (inheritance registrar 0x82F92140), as Burn does.
#ifndef AI_NPCBEHAVIOURSM_H
#define AI_NPCBEHAVIOURSM_H

#include "AI/NPCBehaviour.h"
#include "AI/IBehaviourState.h"
#include "cd2/layout.h"

namespace AI
{
    class NPCBehaviourSM : public NPCBehaviour
    {
    public:
        // CD2 0x8221DD30 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pNPCBehaviourSMClass;
        NPCBehaviourSM();

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;

        virtual void Update(float fDeltaTime);
        // Burn's inline override; CD2's copy (0x824CB4F8) was kept from cAgressiveResponseChaseBehaviour's object.
        virtual void OnAttacked(CHARACTER::cCharacter *pAttacker, const Fun_Runtime::Vec3 &vPosition, cAIEvent *pEvent)
        {
            if (m_pCurrentState)
                m_pCurrentState->OnAttacked(*this, pAttacker, vPosition, pEvent);
        }
        virtual void OnAnimationEvent(unsigned char nType, int nBaseState, short nEventID);
        virtual unsigned char GetStateReplicationInfo() const;

        // 96..100: Burn's NPCBehaviourSM virtuals in its order. The defaults of 96 and 97 are empty (0x82580578).
        virtual void PreUpdateAllStates(float fDeltaTime);
        virtual void PostUpdateAllStates(float fDeltaTime);
        virtual void OnReachedDestination(bool bSuccess);
    protected:
        virtual void ChangeState(unsigned char stateID);
        virtual IBehaviourState *GetState(unsigned char stateID) = 0;

        IBehaviourState *m_pCurrentState;       // 0xC0
        unsigned char m_nState;                 // 0xC4

    public:
        CD2_LAYOUT_CHECKS(NPCBehaviourSM,
            CD2_SIZE(NPCBehaviourSM, 0xD0)
            CD2_OFFSET(NPCBehaviourSM, m_pCurrentState, 0xC0)
            CD2_OFFSET(NPCBehaviourSM, m_nState, 0xC4))
    };
}

#endif // AI_NPCBEHAVIOURSM_H

// AI::tBehaviourState<T> (Crackdown 2): Burn's NPCBehaviourStateMachine.h template, a state built from six member
// functions of the behaviour and a flags word (0x40 bytes: the eight-byte member pointers from 0x8, m_nFlags at 0x38).
// Its virtuals are inline in Burn. CD2's instantiations fold to one table (0x82109854) whose bodies call the member
// pointer when it is set, with the behaviour adjusted by the pointer's second word: Enter/Update/Exit 0x824B25E0..
// 0x824B2620, HandleAnimEvent 0x824CF5F8, OnAttacked 0x824CF628, OnReachedDestination 0x824CC9A8, HasFlagsSet 0x824BF9A0.
// cChaseBehaviour::GetState (0x824CF188) builds seven of them, 0x40 bytes apart, in a function-local static array.
#ifndef AI_TBEHAVIOURSTATE_H
#define AI_TBEHAVIOURSTATE_H

#include "AI/IBehaviourState.h"

namespace AI
{
    template <class T>
    class tBehaviourState : public IBehaviourState
    {
    public:
        typedef void (T::*tStateEnterFn)();
        typedef void (T::*tStateUpdateFn)(float);
        typedef void (T::*tStateExitFn)();
        typedef void (T::*tStateAnimEventFn)(unsigned char, int, short);
        typedef void (T::*tStateAttackedFn)(CHARACTER::cCharacter *, const Fun_Runtime::Vec3 &, cAIEvent *);
        typedef void (T::*tStateDestReachedFn)(bool);

        tBehaviourState(tStateEnterFn pfnEnter, tStateUpdateFn pfnUpdate, tStateExitFn pfnExit,
                        tStateAnimEventFn pfnAnim, tStateAttackedFn pfnAttacked, tStateDestReachedFn pfnDestReached,
                        unsigned int nFlags)
            : m_pfnEnter(pfnEnter), m_pfnUpdate(pfnUpdate), m_pfnExit(pfnExit), m_pfnAnimEvent(pfnAnim),
              m_pfnAttacked(pfnAttacked), m_pfnDestReached(pfnDestReached), m_nFlags(nFlags)
        {
        }

        virtual void Enter(NPCBehaviour &caller)
        {
            if (m_pfnEnter)
                (static_cast<T &>(caller).*m_pfnEnter)();
        }
        virtual void Update(NPCBehaviour &caller, float dt)
        {
            if (m_pfnUpdate)
                (static_cast<T &>(caller).*m_pfnUpdate)(dt);
        }
        virtual void Exit(NPCBehaviour &caller)
        {
            if (m_pfnExit)
                (static_cast<T &>(caller).*m_pfnExit)();
        }
        virtual void HandleAnimEvent(NPCBehaviour &caller, unsigned char nType, int nBaseState, short nEventID)
        {
            if (m_pfnAnimEvent)
                (static_cast<T &>(caller).*m_pfnAnimEvent)(nType, nBaseState, nEventID);
        }
        virtual void OnAttacked(NPCBehaviour &caller, CHARACTER::cCharacter *pAttacker, const Fun_Runtime::Vec3 &vPosition,
                                cAIEvent *pEvent)
        {
            if (m_pfnAttacked)
                (static_cast<T &>(caller).*m_pfnAttacked)(pAttacker, vPosition, pEvent);
        }
        virtual void OnReachedDestination(NPCBehaviour &caller, bool bSuccess)
        {
            if (m_pfnDestReached)
                (static_cast<T &>(caller).*m_pfnDestReached)(bSuccess);
        }
        virtual bool HasFlagsSet(unsigned int nTestFlags) const
        {
            return (m_nFlags & nTestFlags) != 0;
        }

    private:
        tStateEnterFn m_pfnEnter;               // 0x8
        tStateUpdateFn m_pfnUpdate;             // 0x10
        tStateExitFn m_pfnExit;                 // 0x18
        tStateAnimEventFn m_pfnAnimEvent;       // 0x20
        tStateAttackedFn m_pfnAttacked;         // 0x28
        tStateDestReachedFn m_pfnDestReached;   // 0x30
        unsigned int m_nFlags;                  // 0x38
    };
}

#endif // AI_TBEHAVIOURSTATE_H

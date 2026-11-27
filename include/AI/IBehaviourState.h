// AI::IBehaviourState (Crackdown 2): the state interface of NPCBehaviourSM. Burn's NPCBehaviourStateMachine.h declares
// it with these seven pure virtuals in this order; CD2's NPCBehaviourSM calls the current state's slots with the same
// arguments: Update (0x824ABAA8) slot 1 with the behaviour and the time step, ChangeState (0x824A8C00) slot 2 (Exit)
// on the old state and slot 0 (Enter) on the new one, OnAnimationEvent (0x824ABB30) slot 3 with three arguments after
// the behaviour, OnAttacked (0x824CB4F8) slot 4 with three, OnReachedDestination (0x824ABB68) slot 5 with one.
#ifndef AI_IBEHAVIOURSTATE_H
#define AI_IBEHAVIOURSTATE_H

namespace CHARACTER { class cCharacter; }
namespace Fun_Runtime { class Vec3; }

namespace AI
{
    class NPCBehaviour;
    class cAIEvent;

    class IBehaviourState
    {
    public:
        virtual void Enter(NPCBehaviour &caller) = 0;
        virtual void Update(NPCBehaviour &caller, float dt) = 0;
        virtual void Exit(NPCBehaviour &caller) = 0;
        virtual void HandleAnimEvent(NPCBehaviour &caller, unsigned char nType, int nBaseState, short nEventID) = 0;
        virtual void OnAttacked(NPCBehaviour &caller, CHARACTER::cCharacter *pAttacker, const Fun_Runtime::Vec3 &vPosition,
                                cAIEvent *pEvent) = 0;
        virtual void OnReachedDestination(NPCBehaviour &caller, bool bSuccess) = 0;
        virtual bool HasFlagsSet(unsigned int nTestFlags) const = 0;
    };
}

#endif // AI_IBEHAVIOURSTATE_H

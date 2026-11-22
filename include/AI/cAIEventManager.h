// AI::cAIEventManager (Crackdown 2): STAND-IN for the AI event singleton. RuffKing's class (AI/Event/cAIEventManager.h)
// keeps its instance in ms_pEventManager, and RuffKing's inline cAIEventHandler::Unsubscribe forwards the subscription
// to the instance's Unsubscribe. CD2's behaviours do not derive from cAIEventHandler (NPCBehaviour's m_pHost follows
// cNonGameBase at 0x7C); they load the instance from 0x83800988 and call Unsubscribe (0x8243F860) with their
// subscription themselves, as CellTurret::OnExit (0x824C5648) does.
#ifndef AI_CAIEVENTMANAGER_H
#define AI_CAIEVENTMANAGER_H

namespace AI
{
    class cAIEventSubscription;

    class cAIEventManager
    {
    public:
        cAIEventSubscription *Unsubscribe(cAIEventSubscription *pSubscription);

        static cAIEventManager *ms_pEventManager;
    };
}

#endif // AI_CAIEVENTMANAGER_H

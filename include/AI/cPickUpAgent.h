// AI::cPickUpAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cPickUpAgent> (0x823F8B80) allocates 0x14 bytes, builds a
// cAgent and installs table 0x820FDDCC (RetAgentName 0x82419C80 returns "PickUpAgent"; slot 14, RetAgentClassID, is
// 0x82419C38). Its own byte at 0x10 is named after RuffKing's m_bTriggered of cThrowAgent and cSecondaryFireAgent,
// which follow the same pattern: the inlined constructor clears it, OnEnter (slot 6, 0x82419CB8) clears it and sets the
// brain's m_bCarrying, Think (5, 0x82419CD0) reads and sets it and EventTrigger (8, 0x82419F98) sets it. RuffKing's
// cPickUpAgent derives from cMoveToObjectAgent instead.
#ifndef AI_CPICKUPAGENT_H
#define AI_CPICKUPAGENT_H

#include "AI/cAgent.h"

namespace AI
{
    class cPickUpAgent : public cAgent
    {
    public:
        cPickUpAgent(cCharacterBrain *pBrain) : cAgent(pBrain), m_bTriggered(false) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual void Think();
        virtual void OnEnter();
        virtual void EventTrigger(CHARACTER::eControllerEventType eEventType,
            CHARACTER::eControllerEventSubType eEventSubType,
            CHARACTER::eControllerEvents eEvent);
        virtual unsigned short RetAgentClassID();

    private:
        bool m_bTriggered;                                      // 0x10

        CD2_LAYOUT_CHECKS(cPickUpAgent,
            CD2_SIZE(cPickUpAgent, 0x14)
            CD2_OFFSET(cPickUpAgent, m_bTriggered, 0x10))
    };
}

#endif // AI_CPICKUPAGENT_H

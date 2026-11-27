// AI::cMoveAndReloadAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cMoveAndReloadAgent> (0x823F69A0) allocates 0xC0
// bytes, builds a cMoveAndFaceAgent (0x822333C0), installs table 0x820FD878 (RetAgentName 0x82410DA8 returns
// "MoveAndReloadAgent"; slot 14, RetAgentClassID, is 0x82410D60) and clears its own byte at 0xB0, named after RuffKing's
// m_bTriggered of cReloadAgent, which follows the same pattern: Think (slot 5, 0x82410E40) reads and sets it, OnEnter
// (6, 0x82410E08) clears it and EventTrigger (8, 0x82411040) sets it. Slot 0 is cMoveAgent's deleting destructor.
#ifndef AI_CMOVEANDRELOADAGENT_H
#define AI_CMOVEANDRELOADAGENT_H

#include "AI/cMoveAndFaceAgent.h"

namespace AI
{
    class cMoveAndReloadAgent : public cMoveAndFaceAgent
    {
    public:
        cMoveAndReloadAgent(cCharacterBrain *pBrain) : cMoveAndFaceAgent(pBrain), m_bTriggered(false) {}
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
        bool m_bTriggered;                                      // 0xB0

        CD2_LAYOUT_CHECKS(cMoveAndReloadAgent,
            CD2_SIZE(cMoveAndReloadAgent, 0xC0)
            CD2_OFFSET(cMoveAndReloadAgent, m_bTriggered, 0xB0))
    };
}

#endif // AI_CMOVEANDRELOADAGENT_H

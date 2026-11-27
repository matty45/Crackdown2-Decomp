// AI::cChaseAndReloadAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cChaseAndReloadAgent> (0x823FA6F0) allocates
// 0xF0 bytes, builds a cChaseAgent, installs table 0x820FD080 (RetAgentName 0x82408000 returns "ChaseAndReloadAgent";
// slot 14, RetAgentClassID, is 0x82407FB8) and clears its own byte at 0xE0, named after RuffKing's m_bTriggered of
// cReloadAgent, which follows the same pattern: Think (slot 5, 0x82408178) reads and sets it, OnEnter (6, 0x82408140)
// clears it and EventTrigger (8, 0x82408378) sets it. Its deleting destructor is cChaseAgent's (0x824080B0).
#ifndef AI_CCHASEANDRELOADAGENT_H
#define AI_CCHASEANDRELOADAGENT_H

#include "AI/cChaseAgent.h"

namespace AI
{
    class cChaseAndReloadAgent : public cChaseAgent
    {
    public:
        cChaseAndReloadAgent(cCharacterBrain *pBrain) : cChaseAgent(pBrain), m_bTriggered(false) {}
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
        bool m_bTriggered;                                      // 0xE0

        CD2_LAYOUT_CHECKS(cChaseAndReloadAgent,
            CD2_SIZE(cChaseAndReloadAgent, 0xF0)
            CD2_OFFSET(cChaseAndReloadAgent, m_bTriggered, 0xE0))
    };
}

#endif // AI_CCHASEANDRELOADAGENT_H

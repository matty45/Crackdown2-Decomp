// AI::cChaseAgent (Crackdown 2): STAND-IN. CD2's constructor 0x82407B30 (out of line) installs table 0x820FCF78 after
// its cMoveAgent base (RetAgentName 0x82407A98 returns "ChaseAgent"; slot 14, RetAgentClassID, is 0x82407A50). Its
// fields are not modelled (not an allocation layout).
#ifndef AI_CCHASEAGENT_H
#define AI_CCHASEAGENT_H

#include "AI/cMoveAgent.h"

namespace AI
{
    class cChaseAgent : public cMoveAgent
    {
    public:
        cChaseAgent(cCharacterBrain *pBrain);
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();
    };
}

#endif // AI_CCHASEAGENT_H

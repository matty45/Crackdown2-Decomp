// AI::cMoveAgent (Crackdown 2): STAND-IN. CD2's constructor 0x8240E728 (out of line) installs table 0x820FD708 after
// its cAgent base (RetAgentName 0x82227F60 returns "MoveAgent"; slot 14, RetAgentClassID, is 0x821FED70). Its fields
// are not modelled (not an allocation layout).
#ifndef AI_CMOVEAGENT_H
#define AI_CMOVEAGENT_H

#include "AI/cAgent.h"

namespace AI
{
    class cMoveAgent : public cAgent
    {
    public:
        cMoveAgent(cCharacterBrain *pBrain);
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

#endif // AI_CMOVEAGENT_H

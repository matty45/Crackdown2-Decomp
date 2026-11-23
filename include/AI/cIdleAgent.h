// AI::cIdleAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cIdleAgent> (0x823F5790) allocates 0x10 bytes, builds a
// cAgent and installs table 0x82003880 (RetAgentName 0x8240E0B8 returns "IdleAgent"; slot 14, RetAgentClassID, is
// 0x8240E070). Its own fields are not modelled.
#ifndef AI_CIDLEAGENT_H
#define AI_CIDLEAGENT_H

#include "AI/cAgent.h"

namespace AI
{
    class cIdleAgent : public cAgent
    {
    public:
        cIdleAgent(cCharacterBrain *pBrain) : cAgent(pBrain) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 0x8240E070, also expanded into CreateAgent).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();

        CD2_LAYOUT_CHECKS(cIdleAgent,
            CD2_SIZE(cIdleAgent, 0x10))
    };
}

#endif // AI_CIDLEAGENT_H

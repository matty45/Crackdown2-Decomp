// AI::cChaseAndReloadAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cChaseAndReloadAgent> (0x823FA6F0) allocates
// 0xF0 bytes, builds a cChaseAgent and installs table 0x820FD080 (RetAgentName 0x82408000 returns
// "ChaseAndReloadAgent"; slot 14, RetAgentClassID, is 0x82407FB8). Its fields are not modelled (not an allocation
// layout).
#ifndef AI_CCHASEANDRELOADAGENT_H
#define AI_CCHASEANDRELOADAGENT_H

#include "AI/cChaseAgent.h"

namespace AI
{
    class cChaseAndReloadAgent : public cChaseAgent
    {
    public:
        cChaseAndReloadAgent(cCharacterBrain *pBrain) : cChaseAgent(pBrain) {}
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

#endif // AI_CCHASEANDRELOADAGENT_H

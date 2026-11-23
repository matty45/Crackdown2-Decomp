// AI::cInterceptAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cInterceptAgent> (0x823FA820) allocates 0xB0 bytes,
// builds a cMoveAndFaceAgent and installs table 0x820FD5B0 (RetAgentName 0x8240E110 returns "InterceptAgent"; slot
// 14, RetAgentClassID, is 0x8240E0C8). Its fields are not modelled (not an allocation layout).
#ifndef AI_CINTERCEPTAGENT_H
#define AI_CINTERCEPTAGENT_H

#include "AI/cMoveAndFaceAgent.h"

namespace AI
{
    class cInterceptAgent : public cMoveAndFaceAgent
    {
    public:
        cInterceptAgent(cCharacterBrain *pBrain) : cMoveAndFaceAgent(pBrain) {}
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

#endif // AI_CINTERCEPTAGENT_H

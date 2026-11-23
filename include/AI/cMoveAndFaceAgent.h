// AI::cMoveAndFaceAgent (Crackdown 2): STAND-IN. CD2's constructor 0x822333C0 (out of line) installs table 0x820FD798
// after its cMoveAgent base (RetAgentName 0x8236E820 returns "MoveAndFaceAgent"; slot 14, RetAgentClassID, is
// 0x824107C0). Its fields are not modelled (not an allocation layout).
#ifndef AI_CMOVEANDFACEAGENT_H
#define AI_CMOVEANDFACEAGENT_H

#include "AI/cMoveAgent.h"

namespace AI
{
    class cMoveAndFaceAgent : public cMoveAgent
    {
    public:
        cMoveAndFaceAgent(cCharacterBrain *pBrain);
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

#endif // AI_CMOVEANDFACEAGENT_H

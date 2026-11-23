// AI::cThrowAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cThrowAgent> (0x823F7D70) allocates 0x50 bytes, builds a
// cFaceAgent and installs table 0x820FE144 (RetAgentName 0x8241D7F8 returns "ThrowAgent"; slot 14, RetAgentClassID,
// is 0x8241D7B0). Its own fields are not modelled.
#ifndef AI_CTHROWAGENT_H
#define AI_CTHROWAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cThrowAgent : public cFaceAgent
    {
    public:
        cThrowAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();

    private:
        unsigned char m_unmodelled40[0x50 - 0x40];

        CD2_LAYOUT_CHECKS(cThrowAgent,
            CD2_SIZE(cThrowAgent, 0x50))
    };
}

#endif // AI_CTHROWAGENT_H

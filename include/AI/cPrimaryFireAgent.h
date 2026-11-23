// AI::cPrimaryFireAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cPrimaryFireAgent> (0x823F7A70) allocates 0x50
// bytes, builds a cFaceAgent and installs table 0x820FDE68 (RetAgentName 0x8241A608 returns "PrimaryFireAgent"; slot
// 14, RetAgentClassID, is 0x8241A5C0). Its own fields are not modelled.
#ifndef AI_CPRIMARYFIREAGENT_H
#define AI_CPRIMARYFIREAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cPrimaryFireAgent : public cFaceAgent
    {
    public:
        cPrimaryFireAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain) {}
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

        CD2_LAYOUT_CHECKS(cPrimaryFireAgent,
            CD2_SIZE(cPrimaryFireAgent, 0x50))
    };
}

#endif // AI_CPRIMARYFIREAGENT_H

// AI::cSecondaryFireAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cSecondaryFireAgent> (0x823F7BF0) allocates 0x50
// bytes, builds a cFaceAgent and installs table 0x820FE068 (RetAgentName 0x8241D2F8 returns "SecondaryFireAgent";
// slot 14, RetAgentClassID, is 0x8241D2B0). Its own fields are not modelled.
#ifndef AI_CSECONDARYFIREAGENT_H
#define AI_CSECONDARYFIREAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cSecondaryFireAgent : public cFaceAgent
    {
    public:
        cSecondaryFireAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain) {}
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

        CD2_LAYOUT_CHECKS(cSecondaryFireAgent,
            CD2_SIZE(cSecondaryFireAgent, 0x50))
    };
}

#endif // AI_CSECONDARYFIREAGENT_H

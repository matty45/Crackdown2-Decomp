// AI::cPickUpItemAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cPickUpItemAgent> (0x823F8A00) allocates 0x50
// bytes, builds a cFaceAgent and installs table 0x820FDE18 (RetAgentName 0x8241A268 returns "PickUpItemAgent"; slot
// 14, RetAgentClassID, is 0x8241A220). Its own fields are not modelled.
#ifndef AI_CPICKUPITEMAGENT_H
#define AI_CPICKUPITEMAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cPickUpItemAgent : public cFaceAgent
    {
    public:
        cPickUpItemAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain) {}
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

        CD2_LAYOUT_CHECKS(cPickUpItemAgent,
            CD2_SIZE(cPickUpItemAgent, 0x50))
    };
}

#endif // AI_CPICKUPITEMAGENT_H

// AI::cPickUpAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cPickUpAgent> (0x823F8B80) allocates 0x14 bytes, builds
// a cAgent and installs table 0x820FDDCC (RetAgentName 0x82419C80 returns "PickUpAgent"; slot 14, RetAgentClassID, is
// 0x82419C38). Its own fields are not modelled.
#ifndef AI_CPICKUPAGENT_H
#define AI_CPICKUPAGENT_H

#include "AI/cAgent.h"

namespace AI
{
    class cPickUpAgent : public cAgent
    {
    public:
        cPickUpAgent(cCharacterBrain *pBrain) : cAgent(pBrain) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();

    private:
        unsigned char m_unmodelled10[0x14 - 0x10];

        CD2_LAYOUT_CHECKS(cPickUpAgent,
            CD2_SIZE(cPickUpAgent, 0x14))
    };
}

#endif // AI_CPICKUPAGENT_H

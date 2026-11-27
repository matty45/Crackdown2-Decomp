// AI::cUncrouchAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cUncrouchAgent> (0x823F8FC0) allocates 0x40 bytes,
// builds a cFaceAgent and installs table 0x820FE1FC (RetAgentName 0x8241E770 returns "UncrouchAgent"; slot 14,
// RetAgentClassID, is 0x8241E728). Its own fields are not modelled.
#ifndef AI_CUNCROUCHAGENT_H
#define AI_CUNCROUCHAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cUncrouchAgent : public cFaceAgent
    {
    public:
        cUncrouchAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();
        // Slot 5: CD2 0x8241E780.
        virtual void Think();

        CD2_LAYOUT_CHECKS(cUncrouchAgent,
            CD2_SIZE(cUncrouchAgent, 0x40))
    };
}

#endif // AI_CUNCROUCHAGENT_H

// AI::cReloadAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cReloadAgent> (0x823F58C0) allocates 0x50 bytes, builds
// a cFaceAgent and installs table 0x820FDF9C (RetAgentName 0x8241C6A8 returns "ReloadAgent"; slot 14,
// RetAgentClassID, is 0x8241C660). Its own fields are not modelled.
#ifndef AI_CRELOADAGENT_H
#define AI_CRELOADAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cReloadAgent : public cFaceAgent
    {
    public:
        cReloadAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain) {}
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

        CD2_LAYOUT_CHECKS(cReloadAgent,
            CD2_SIZE(cReloadAgent, 0x50))
    };
}

#endif // AI_CRELOADAGENT_H

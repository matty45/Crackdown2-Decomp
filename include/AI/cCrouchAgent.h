// AI::cCrouchAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cCrouchAgent> (0x823F8E40) allocates 0x40 bytes, builds
// a cFaceAgent and installs table 0x820FD1E4 (RetAgentName 0x8240A9B0 returns "CrouchAgent"; slot 14,
// RetAgentClassID, is 0x8240A968). Its own fields are not modelled.
#ifndef AI_CCROUCHAGENT_H
#define AI_CCROUCHAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cCrouchAgent : public cFaceAgent
    {
    public:
        cCrouchAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();
        // Slot 5: CD2 0x8240A9C0.
        virtual void Think();

        CD2_LAYOUT_CHECKS(cCrouchAgent,
            CD2_SIZE(cCrouchAgent, 0x40))
    };
}

#endif // AI_CCROUCHAGENT_H

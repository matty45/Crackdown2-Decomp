// AI::cUpperBodyAnimateAndFaceAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cUpperBodyAnimateAndFaceAgent>
// (0x823F8288) allocates 0x40 bytes, builds a cFaceAgent and installs table 0x820FE258 (RetAgentName 0x8241E828
// returns "UpperBodyAnimateAndFaceAgent"; slot 14, RetAgentClassID, is 0x8241E7E0). Its own fields are not modelled.
#ifndef AI_CUPPERBODYANIMATEANDFACEAGENT_H
#define AI_CUPPERBODYANIMATEANDFACEAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cUpperBodyAnimateAndFaceAgent : public cFaceAgent
    {
    public:
        cUpperBodyAnimateAndFaceAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();

        CD2_LAYOUT_CHECKS(cUpperBodyAnimateAndFaceAgent,
            CD2_SIZE(cUpperBodyAnimateAndFaceAgent, 0x40))
    };
}

#endif // AI_CUPPERBODYANIMATEANDFACEAGENT_H

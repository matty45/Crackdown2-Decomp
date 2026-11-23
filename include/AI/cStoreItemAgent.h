// AI::cStoreItemAgent (Crackdown 2): STAND-IN; not in the reference builds. CD2's CreateAgent<cStoreItemAgent>
// (0x823F8880) allocates 0x50 bytes, builds a cFaceAgent, then installs table 0x820FE0D8 (RetAgentName 0x8241D5B8
// returns "StoreItemAgent") and clears the byte at 0x40. Its own fields are not modelled.
#ifndef AI_CSTOREITEMAGENT_H
#define AI_CSTOREITEMAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cStoreItemAgent : public cFaceAgent
    {
    public:
        cStoreItemAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain) {}
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

        CD2_LAYOUT_CHECKS(cStoreItemAgent,
            CD2_SIZE(cStoreItemAgent, 0x50))
    };
}

#endif // AI_CSTOREITEMAGENT_H

// AI::cDropAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cDropAgent> (0x823F8CC0) allocates 0x50 bytes, builds a
// cFaceAgent and installs table 0x820FD330 (RetAgentName 0x8240BD58 returns "DropAgent"; slot 14, RetAgentClassID, is
// 0x8240BD10). Its own fields are not modelled.
#ifndef AI_CDROPAGENT_H
#define AI_CDROPAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cDropAgent : public cFaceAgent
    {
    public:
        cDropAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain) {}
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

        CD2_LAYOUT_CHECKS(cDropAgent,
            CD2_SIZE(cDropAgent, 0x50))
    };
}

#endif // AI_CDROPAGENT_H

// AI::cDodgeAgent (Crackdown 2): STAND-IN; not in the reference builds. CD2's CreateAgent<cDodgeAgent> (0x823F9D70)
// allocates 0xD0 bytes, builds a cMoveAndPrimaryFireAgent (0x82410990), installs table 0x820FD2A8 (RetAgentName
// 0x8240B1B0 returns "DodgeAgent"; slot 14, RetAgentClassID, is 0x8240B168) and clears its byte at 0xC0 (name ours:
// OnEnter, slot 6 at 0x8240B298, clears it, slot 18 (0x8240BAC8) sets it and Think, slot 5 at 0x8240BC20, reads it).
// Slot 0 is cMoveAgent's deleting destructor.
#ifndef AI_CDODGEAGENT_H
#define AI_CDODGEAGENT_H

#include "AI/cMoveAndPrimaryFireAgent.h"

namespace AI
{
    class cDodgeAgent : public cMoveAndPrimaryFireAgent
    {
    public:
        cDodgeAgent(cCharacterBrain *pBrain) : cMoveAndPrimaryFireAgent(pBrain), m_bDodgeTriggered(false) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual void Think();
        virtual void OnEnter();
        virtual unsigned short RetAgentClassID();

    protected:
        virtual void vf18();

    private:
        bool m_bDodgeTriggered;                                 // 0xC0

        CD2_LAYOUT_CHECKS(cDodgeAgent,
            CD2_SIZE(cDodgeAgent, 0xD0)
            CD2_OFFSET(cDodgeAgent, m_bDodgeTriggered, 0xC0))
    };
}

#endif // AI_CDODGEAGENT_H

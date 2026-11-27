// AI::cPrimaryFireAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cPrimaryFireAgent> (0x823F7A70) allocates 0x50
// bytes, builds a cFaceAgent and installs table 0x820FDE68 (RetAgentName 0x8241A608 returns "PrimaryFireAgent"; slot
// 14, RetAgentClassID, is 0x8241A5C0). Its own field at 0x40 is named after RuffKing's m_bTriggered of the sibling
// cThrowAgent and cSecondaryFireAgent (0x30 there), which follow the same pattern: the inlined constructor clears it,
// OnEnter clears it, Think reads it and EventAnimation sets it.
#ifndef AI_CPRIMARYFIREAGENT_H
#define AI_CPRIMARYFIREAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cPrimaryFireAgent : public cFaceAgent
    {
    public:
        cPrimaryFireAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain), m_bTriggered(false) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();
        // Slot 5: CD2 0x8241A628.
        virtual void Think();
        // Slot 6: CD2 0x8241D890.
        virtual void OnEnter();
        // Slot 9: CD2 0x8241A7D8.
        virtual void EventAnimation(const CHARACTER::etActionTypesEnum &eType, int nBaseState, short nEventID);

    private:
        bool m_bTriggered;                          // 0x40

        CD2_LAYOUT_CHECKS(cPrimaryFireAgent,
            CD2_SIZE(cPrimaryFireAgent, 0x50)
            CD2_OFFSET(cPrimaryFireAgent, m_bTriggered, 0x40))
    };
}

#endif // AI_CPRIMARYFIREAGENT_H

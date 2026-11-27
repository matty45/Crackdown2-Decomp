// AI::cPickUpItemAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cPickUpItemAgent> (0x823F8A00) allocates 0x50 bytes,
// builds a cFaceAgent and installs table 0x820FDE18 (RetAgentName 0x8241A268 returns "PickUpItemAgent"; slot 14,
// RetAgentClassID, is 0x8241A220). Its own field at 0x40 is named after RuffKing's m_bTriggered of the sibling
// cThrowAgent and cSecondaryFireAgent (0x30 there), which follow the same pattern: the inlined constructor clears it,
// OnEnter clears it, Think reads it and EventTrigger sets it.
#ifndef AI_CPICKUPITEMAGENT_H
#define AI_CPICKUPITEMAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cPickUpItemAgent : public cFaceAgent
    {
    public:
        cPickUpItemAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain), m_bTriggered(false) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();
        // Slot 5: CD2 0x8241A298.
        virtual void Think();
        // Slot 6: CD2 0x8241D890.
        virtual void OnEnter();
        // Slot 8: CD2 0x8241A490.
        virtual void EventTrigger(CHARACTER::eControllerEventType eEventType,
            CHARACTER::eControllerEventSubType eEventSubType,
            CHARACTER::eControllerEvents eEvent);

    private:
        bool m_bTriggered;                          // 0x40

        CD2_LAYOUT_CHECKS(cPickUpItemAgent,
            CD2_SIZE(cPickUpItemAgent, 0x50)
            CD2_OFFSET(cPickUpItemAgent, m_bTriggered, 0x40))
    };
}

#endif // AI_CPICKUPITEMAGENT_H

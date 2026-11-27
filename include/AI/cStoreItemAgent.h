// AI::cStoreItemAgent (Crackdown 2): STAND-IN; not in the reference builds. CD2's CreateAgent<cStoreItemAgent>
// (0x823F8880) allocates 0x50 bytes, builds a cFaceAgent, then installs table 0x820FE0D8 (RetAgentName 0x8241D5B8
// returns "StoreItemAgent") and clears the byte at 0x40. Its own field at 0x40 is named after RuffKing's m_bTriggered
// of the sibling cThrowAgent and cSecondaryFireAgent (0x30 there), which follow the same pattern: the inlined
// constructor clears it, OnEnter clears it, Think reads it and EventTrigger sets it.
#ifndef AI_CSTOREITEMAGENT_H
#define AI_CSTOREITEMAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cStoreItemAgent : public cFaceAgent
    {
    public:
        cStoreItemAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain), m_bTriggered(false) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();
        // Slot 5: CD2 0x8241D5D8.
        virtual void Think();
        // Slot 6: CD2 0x8241D890.
        virtual void OnEnter();
        // Slot 8: CD2 0x8241D690.
        virtual void EventTrigger(CHARACTER::eControllerEventType eEventType,
            CHARACTER::eControllerEventSubType eEventSubType,
            CHARACTER::eControllerEvents eEvent);

    private:
        bool m_bTriggered;                          // 0x40

        CD2_LAYOUT_CHECKS(cStoreItemAgent,
            CD2_SIZE(cStoreItemAgent, 0x50)
            CD2_OFFSET(cStoreItemAgent, m_bTriggered, 0x40))
    };
}

#endif // AI_CSTOREITEMAGENT_H

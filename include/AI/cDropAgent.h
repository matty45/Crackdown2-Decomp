// AI::cDropAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cDropAgent> (0x823F8CC0) allocates 0x50 bytes, builds a
// cFaceAgent and installs table 0x820FD330 (RetAgentName 0x8240BD58 returns "DropAgent"; slot 14, RetAgentClassID, is
// 0x8240BD10). Its own field at 0x40 is named after RuffKing's m_bTriggered of the sibling cThrowAgent and
// cSecondaryFireAgent (0x30 there), which follow the same pattern: the inlined constructor clears it, OnEnter clears
// it, Think reads it and EventTrigger sets it.
#ifndef AI_CDROPAGENT_H
#define AI_CDROPAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cDropAgent : public cFaceAgent
    {
    public:
        cDropAgent(cCharacterBrain *pBrain) : cFaceAgent(pBrain), m_bTriggered(false) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();
        // Slot 5: CD2 0x8240BD88.
        virtual void Think();
        // Slot 6: CD2 0x8241D890.
        virtual void OnEnter();
        // Slot 7: CD2 0x8240BD78.
        virtual void OnExit();
        // Slot 8: CD2 0x8240BDF0.
        virtual void EventTrigger(CHARACTER::eControllerEventType eEventType,
            CHARACTER::eControllerEventSubType eEventSubType,
            CHARACTER::eControllerEvents eEvent);

    private:
        bool m_bTriggered;                          // 0x40

        CD2_LAYOUT_CHECKS(cDropAgent,
            CD2_SIZE(cDropAgent, 0x50)
            CD2_OFFSET(cDropAgent, m_bTriggered, 0x40))
    };
}

#endif // AI_CDROPAGENT_H

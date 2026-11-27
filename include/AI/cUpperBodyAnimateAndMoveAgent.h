// AI::cUpperBodyAnimateAndMoveAgent (Crackdown 2): STAND-IN; not in the reference builds. CD2's
// CreateAgent<cUpperBodyAnimateAndMoveAgent> (0x823F8408) allocates 0xA0 bytes, builds a cMoveAgent (0x8240E728) and
// installs table 0x820FE2B8 (RetAgentName 0x8241E998 returns "UpperBodyAnimateAndMoveAgent"; slot 14, RetAgentClassID,
// is 0x8241E950): it adds no fields. It overrides OnEnter, OnExit and EventTrigger (slots 6..8: 0x8241E9A8, 0x8241EA90
// and 0x8241EAF0, the last shared with cUpperBodyAnimateAndFaceAgent); slot 0 is cMoveAgent's deleting destructor.
#ifndef AI_CUPPERBODYANIMATEANDMOVEAGENT_H
#define AI_CUPPERBODYANIMATEANDMOVEAGENT_H

#include "AI/cMoveAgent.h"

namespace AI
{
    class cUpperBodyAnimateAndMoveAgent : public cMoveAgent
    {
    public:
        cUpperBodyAnimateAndMoveAgent(cCharacterBrain *pBrain) : cMoveAgent(pBrain) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual void OnEnter();
        virtual void OnExit();
        virtual void EventTrigger(CHARACTER::eControllerEventType eEventType,
            CHARACTER::eControllerEventSubType eEventSubType,
            CHARACTER::eControllerEvents eEvent);
        virtual unsigned short RetAgentClassID();

        CD2_LAYOUT_CHECKS(cUpperBodyAnimateAndMoveAgent,
            CD2_SIZE(cUpperBodyAnimateAndMoveAgent, 0xA0))
    };
}

#endif // AI_CUPPERBODYANIMATEANDMOVEAGENT_H

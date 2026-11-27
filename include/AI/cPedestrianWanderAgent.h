// AI::cPedestrianWanderAgent (Crackdown 2): STAND-IN. CD2's constructor 0x82417830 (out of line) builds a cMoveAgent
// (0x8240E728) and installs table 0x820FDD18 (RetAgentName 0x824177F0 returns "PedestrianWanderAgent"; slot 14,
// RetAgentClassID, is 0x824177A8); CreateAgent<cPedestrianWanderAgent> (0x823F7EF0) allocates 0x140 bytes. Its own
// members (from 0xA0: safe pointers and further tables the constructor installs) are not modelled. Its table has its
// own deleting destructor (0x8240AAB8) and overrides ReInit, Think, OnEnter, OnExit, EventTrigger (slots 4..8),
// OnArrived (17) and SetPathFinderLOD (20), and adds slots from 21 on.
#ifndef AI_CPEDESTRIANWANDERAGENT_H
#define AI_CPEDESTRIANWANDERAGENT_H

#include "AI/cMoveAgent.h"

namespace AI
{
    class cPedestrianWanderAgent : public cMoveAgent
    {
    public:
        cPedestrianWanderAgent(cCharacterBrain *pBrain);
        virtual ~cPedestrianWanderAgent();
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();

    private:
        unsigned char m_unmodelledA0[0x140 - 0xA0];

        CD2_LAYOUT_CHECKS(cPedestrianWanderAgent,
            CD2_SIZE(cPedestrianWanderAgent, 0x140))
    };
}

#endif // AI_CPEDESTRIANWANDERAGENT_H

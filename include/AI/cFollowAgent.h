// AI::cFollowAgent (Crackdown 2): STAND-IN; not in the reference builds. CD2's CreateAgent<cFollowAgent> (0x823F6E48)
// allocates 0xC0 bytes, builds a cMoveAgent (0x8240E728), installs table 0x820FD4C8 (RetAgentName 0x8240DA10 returns
// "FollowAgent"; slot 14, RetAgentClassID, is 0x8240D9C8) and stores CONST_FLOAT_0 of its object's g_GlobalConstants
// copy (0x830B0BA0) in the two distances, two constants at 0xA8/0xAC and clears the byte at 0xB0: that copy places the
// constructor in the agent's own object, so it is out of line here. The "Follow" script method (0x823F23B0) sets the
// two distances; their names are ours. It overrides Think (slot 5, 0x8240DC90) and OnEnter (6, 0x8240DA20).
#ifndef AI_CFOLLOWAGENT_H
#define AI_CFOLLOWAGENT_H

#include "AI/cMoveAgent.h"

namespace AI
{
    class cFollowAgent : public cMoveAgent
    {
    public:
        cFollowAgent(cCharacterBrain *pBrain);
        // RuffKing's pattern: the type's ID, allocated on first use (CD2 expands it into CreateAgent).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual void Think();
        virtual void OnEnter();
        virtual unsigned short RetAgentClassID();
        void SetDistances(float fMinDistance, float fMaxDistance)
        {
            m_fMinDistance = fMinDistance;
            m_fMaxDistance = fMaxDistance;
        }

    private:
        float m_fMinDistance;                                   // 0xA0
        float m_fMaxDistance;                                   // 0xA4
        unsigned char m_unmodelledA8[0xC0 - 0xA8];

        CD2_LAYOUT_CHECKS(cFollowAgent,
            CD2_SIZE(cFollowAgent, 0xC0)
            CD2_OFFSET(cFollowAgent, m_fMinDistance, 0xA0)
            CD2_OFFSET(cFollowAgent, m_fMaxDistance, 0xA4))
    };
}

#endif // AI_CFOLLOWAGENT_H

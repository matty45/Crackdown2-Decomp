// AI::cChaseAndPrimaryFireAgent (Crackdown 2): STAND-IN. RuffKing's cChaseAndPrimaryFireAgent : cMoveAndPrimaryFireAgent
// (AI/Agents/cChaseAndPrimaryFireAgent.h) with m_fTargetTooFarDistance 0x10 bytes later (0xC0). CD2's
// CreateAgent<cChaseAndPrimaryFireAgent> (0x823FA5B8) allocates 0xD0 bytes, builds a cMoveAndPrimaryFireAgent
// (0x82410990), installs table 0x820FD010 (RetAgentName 0x82407D48 returns "ChaseAndPrimaryFireAgent"; slot 14,
// RetAgentClassID, is 0x82407D00) and stores 0.0f in m_fTargetTooFarDistance. It overrides RetAgentStatus (slot 2,
// 0x82407D58), Think (5, 0x82407F80) and OnEnter (6, 0x82407F78); slot 0 is cMoveAgent's deleting destructor.
#ifndef AI_CCHASEANDPRIMARYFIREAGENT_H
#define AI_CCHASEANDPRIMARYFIREAGENT_H

#include "AI/cMoveAndPrimaryFireAgent.h"

namespace AI
{
    class cChaseAndPrimaryFireAgent : public cMoveAndPrimaryFireAgent
    {
    public:
        cChaseAndPrimaryFireAgent(cCharacterBrain *pBrain)
            : cMoveAndPrimaryFireAgent(pBrain), m_fTargetTooFarDistance(0.0f)
        {
        }
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned int RetAgentStatus() const;
        virtual void Think();
        virtual void OnEnter();
        virtual unsigned short RetAgentClassID();
        // RuffKing's setter (out of line there); the "ChaseAndPrimaryFire" script method expands it.
        void SetTargetTooFarDistance(const float fDistance) { m_fTargetTooFarDistance = fDistance; }

    protected:
        float m_fTargetTooFarDistance;                          // 0xC0

        CD2_LAYOUT_CHECKS(cChaseAndPrimaryFireAgent,
            CD2_SIZE(cChaseAndPrimaryFireAgent, 0xD0)
            CD2_OFFSET(cChaseAndPrimaryFireAgent, m_fTargetTooFarDistance, 0xC0))
    };
}

#endif // AI_CCHASEANDPRIMARYFIREAGENT_H

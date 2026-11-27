// AI::cSafeDistancePrimaryFireAgent (Crackdown 2): STAND-IN. RuffKing's cSafeDistancePrimaryFire : cMoveAndPrimaryFireAgent
// (AI/Agents/cSafeDistancePrimaryFire.h; CD2's RetAgentName 0x8241CA58 returns "SafeDistancePrimaryFireAgent"). CD2's
// CreateAgent<cSafeDistancePrimaryFireAgent> (0x823F7920) allocates 0x100 bytes, builds a cMoveAndPrimaryFireAgent
// (0x82410990), installs table 0x820FDFF8 (slot 14, RetAgentClassID, is 0x8241CA10), clears a halfword at 0xC0, points
// RuffKing's m_vHistory (a cVectorip of four vertices, 0xD0) at its own storage and stores CONST_FLOAT_0 of its
// object's g_GlobalConstants copy (0x830B2140) in m_fDistance (0xF0): that copy places the constructor in the agent's
// own object, so it is out of line here. RuffKing's m_fUnSafeDistance follows (0xF4). The halfword and the history are
// not modelled.
#ifndef AI_CSAFEDISTANCEPRIMARYFIREAGENT_H
#define AI_CSAFEDISTANCEPRIMARYFIREAGENT_H

#include "AI/cMoveAndPrimaryFireAgent.h"

namespace AI
{
    class cSafeDistancePrimaryFireAgent : public cMoveAndPrimaryFireAgent
    {
    public:
        cSafeDistancePrimaryFireAgent(cCharacterBrain *pBrain);
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();
        // RuffKing's setter (out of line there); the "SafeDistancePrimaryFire" script method (0x823F2AC0) expands it.
        void SetDistance(float fDistance)
        {
            m_fDistance = fDistance;
            m_fUnSafeDistance = fDistance - 1.0f;
        }

    private:
        unsigned char m_unmodelledC0[0xF0 - 0xC0];
        float m_fDistance;                                      // 0xF0
        float m_fUnSafeDistance;                                // 0xF4
        unsigned char m_unmodelledF8[0x100 - 0xF8];

        CD2_LAYOUT_CHECKS(cSafeDistancePrimaryFireAgent,
            CD2_SIZE(cSafeDistancePrimaryFireAgent, 0x100)
            CD2_OFFSET(cSafeDistancePrimaryFireAgent, m_fDistance, 0xF0)
            CD2_OFFSET(cSafeDistancePrimaryFireAgent, m_fUnSafeDistance, 0xF4))
    };
}

#endif // AI_CSAFEDISTANCEPRIMARYFIREAGENT_H

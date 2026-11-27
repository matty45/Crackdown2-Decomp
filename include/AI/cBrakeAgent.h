// AI::cBrakeAgent (Crackdown 2): STAND-IN; not in the reference builds. CD2's CreateAgent<cBrakeAgent> (0x823FA050)
// allocates 0x18 bytes, builds a cAgent, installs table 0x820FE4FC (RetAgentName 0x82420EB0 returns "BrakeAgent";
// slot 14, RetAgentClassID, is 0x82420E68), clears the bytes at 0x10/0x11 and stores CONST_FLOAT_0 of its object's
// g_GlobalConstants copy (0x830B2C4C) at 0x14: that copy places the constructor in the agent's own object, so it is
// out of line here. Names ours: Think (slot 5, 0x82420EE0) does nothing once m_bFinished is set and compares the
// vehicle's speed with m_fStopSpeed; the "Brake" script method (0x823F42F8) sets m_fStopSpeed and the flag at 0x10.
// It overrides OnEnter (6, 0x82420ED0).
#ifndef AI_CBRAKEAGENT_H
#define AI_CBRAKEAGENT_H

#include "AI/cAgent.h"

namespace AI
{
    class cBrakeAgent : public cAgent
    {
    public:
        cBrakeAgent(cCharacterBrain *pBrain);
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
        void SetBrake(bool bBrakeFlag, float fStopSpeed)
        {
            m_fStopSpeed = fStopSpeed;
            m_bBrakeFlag = bBrakeFlag;
        }

    private:
        bool m_bBrakeFlag;                                      // 0x10
        bool m_bFinished;                                       // 0x11
        float m_fStopSpeed;                                     // 0x14

        CD2_LAYOUT_CHECKS(cBrakeAgent,
            CD2_SIZE(cBrakeAgent, 0x18)
            CD2_OFFSET(cBrakeAgent, m_bBrakeFlag, 0x10)
            CD2_OFFSET(cBrakeAgent, m_bFinished, 0x11)
            CD2_OFFSET(cBrakeAgent, m_fStopSpeed, 0x14))
    };
}

#endif // AI_CBRAKEAGENT_H

// AI::cCloseAttackAgent (Crackdown 2): STAND-IN; not in the reference builds. CD2's constructor 0x82408DD8 (out of
// line) builds a cMoveAndFaceAgent (0x822333C0), installs table 0x820FD170 (RetAgentName 0x82408D18 returns
// "CloseAttackAgent"; slot 14, RetAgentClassID, is 0x82408CD0) and its members (animation parameters from 0xB4, whose
// IDs, times and flags the "SetCloseAttack...Anim" script methods set, and safe pointers); CreateAgent<cCloseAttackAgent>
// (0x823F9838) allocates 0x1C0 bytes. Only the time the "CloseAttack" script method (0x823F3C68) sets is modelled
// (name ours; Think, slot 5 at 0x82409220, counts it down). Its table has its own deleting destructor (0x82409000) and
// overrides ReInit, Think, OnEnter, OnExit, EventTrigger, EventAnimation (slots 4..9) and OnArrived (17).
#ifndef AI_CCLOSEATTACKAGENT_H
#define AI_CCLOSEATTACKAGENT_H

#include "AI/cMoveAndFaceAgent.h"

namespace AI
{
    class cCloseAttackAgent : public cMoveAndFaceAgent
    {
    public:
        cCloseAttackAgent(cCharacterBrain *pBrain);
        virtual ~cCloseAttackAgent();
        // RuffKing's pattern: the type's ID, allocated on first use (CD2 expands it into CreateAgent).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();
        void SetCloseAttackTime(float fTime) { m_fCloseAttackTime = fTime; }

    private:
        unsigned char m_unmodelledB0[0x194 - 0xB0];
        float m_fCloseAttackTime;                               // 0x194
        unsigned char m_unmodelled198[0x1C0 - 0x198];

        CD2_LAYOUT_CHECKS(cCloseAttackAgent,
            CD2_SIZE(cCloseAttackAgent, 0x1C0)
            CD2_OFFSET(cCloseAttackAgent, m_fCloseAttackTime, 0x194))
    };
}

#endif // AI_CCLOSEATTACKAGENT_H

// AI::cMoveAndFaceAgent (Crackdown 2): STAND-IN. RuffKing's cMoveAndFaceAgent : cMoveAgent with its fields 0x10 bytes
// later (after CD2's 0xA0-byte cMoveAgent). CD2's constructor 0x822333C0 (out of line) installs table 0x820FD798
// (RetAgentName 0x8236E820 returns "MoveAndFaceAgent"; slot 14, RetAgentClassID, is 0x824107C0), stores CONST_FLOAT_0
// in m_fTolerance (0xA0) and m_fDifference (0xA4) and sets m_bTargetFacingEnabled (0xA8); CreateAgent<cMoveAndFaceAgent>
// (0x823F6880) allocates 0xB0 bytes. Its table overrides cMoveAgent's Think (slot 5, 0x82410808); slot 0 is cMoveAgent's
// deleting destructor (0x82410DB8): the class declares no destructor.
#ifndef AI_CMOVEANDFACEAGENT_H
#define AI_CMOVEANDFACEAGENT_H

#include "AI/cMoveAgent.h"

namespace AI
{
    class cMoveAndFaceAgent : public cMoveAgent
    {
    public:
        cMoveAndFaceAgent(cCharacterBrain *pBrain);
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual void Think();                                   // 5: 0x82410808
        virtual unsigned short RetAgentClassID();

    protected:
        float m_fTolerance;                                     // 0xA0
        float m_fDifference;                                    // 0xA4
        bool m_bTargetFacingEnabled;                            // 0xA8

        CD2_LAYOUT_CHECKS(cMoveAndFaceAgent,
            CD2_SIZE(cMoveAndFaceAgent, 0xB0)
            CD2_OFFSET(cMoveAndFaceAgent, m_fTolerance, 0xA0)
            CD2_OFFSET(cMoveAndFaceAgent, m_fDifference, 0xA4)
            CD2_OFFSET(cMoveAndFaceAgent, m_bTargetFacingEnabled, 0xA8))
    };
}

#endif // AI_CMOVEANDFACEAGENT_H

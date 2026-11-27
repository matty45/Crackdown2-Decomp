// AI::cCircleAgent (Crackdown 2): STAND-IN. RuffKing's cCircleAgent : cMoveAndFaceAgent (AI/Agents/cCircleAgent.h)
// with its fields from 0xB0, after CD2's 0xB0-byte cMoveAndFaceAgent, and one more flag. CD2's CreateAgent<cCircleAgent>
// (0x823F9AD0) allocates 0xC0 bytes, builds a cMoveAndFaceAgent (0x822333C0), installs table 0x820FD108 (RetAgentName
// 0x82408490 returns "CircleAgent"; slot 14, RetAgentClassID, is 0x82408448), stores CONST_FLOAT_0 of its object's
// g_GlobalConstants copy (0x830B0150) in the three floats (that copy places the constructor in the agent's own object,
// so it is out of line here) and sets the flags at 0xBC..0xBF to 0, 1, 0, 0. Think (slot 5, 0x82408A10) changes
// direction when m_fTime reaches m_fMaxTime unless m_bDirectionLock (0xBF) is set; OnEnter (6, 0x824084A0) picks
// m_nDirection and m_fMaxTime and, when the byte at 0xBD is set, adjusts the host's movement as cBackAwayAgent's does
// (the byte's name is ours, as there). It overrides OnExit (7, 0x82408B98) too.
#ifndef AI_CCIRCLEAGENT_H
#define AI_CCIRCLEAGENT_H

#include "AI/cMoveAndFaceAgent.h"

namespace AI
{
    class cCircleAgent : public cMoveAndFaceAgent
    {
    public:
        cCircleAgent(cCharacterBrain *pBrain);
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual void Think();
        virtual void OnEnter();
        virtual void OnExit();
        virtual unsigned short RetAgentClassID();
        // RuffKing's setters (out of line there); the "Circle" script method (0x823F4158) expands them.
        void SetDistance(float fDistance) { m_fDistance = fDistance; }
        void SetAdjustMovement(bool bAdjust) { m_bAdjustMovement = bAdjust; }
        void SetDirectionLocked(const bool bLocked) { m_bDirectionLock = bLocked; }

    private:
        float m_fTime;                                          // 0xB0
        float m_fMaxTime;                                       // 0xB4
        float m_fDistance;                                      // 0xB8
        char m_nDirection;                                      // 0xBC
        bool m_bAdjustMovement;                                 // 0xBD
        bool m_bIncreasingRange;                                // 0xBE
        bool m_bDirectionLock;                                  // 0xBF

        CD2_LAYOUT_CHECKS(cCircleAgent,
            CD2_SIZE(cCircleAgent, 0xC0)
            CD2_OFFSET(cCircleAgent, m_fTime, 0xB0)
            CD2_OFFSET(cCircleAgent, m_fDistance, 0xB8)
            CD2_OFFSET(cCircleAgent, m_nDirection, 0xBC)
            CD2_OFFSET(cCircleAgent, m_bAdjustMovement, 0xBD)
            CD2_OFFSET(cCircleAgent, m_bDirectionLock, 0xBF))
    };
}

#endif // AI_CCIRCLEAGENT_H

// AI::cBackAwayAgent (Crackdown 2): STAND-IN. RuffKing's cBackAwayAgent (AI/Agents/cBackAwayAgent.h) derives from
// cMoveAndPrimaryFireAgent and cTask; CD2's has no second table: CreateAgent<cBackAwayAgent> (0x823F9C30) allocates
// 0xD0 bytes, builds a cMoveAndPrimaryFireAgent (0x82410990), installs table 0x82004B08 (RetAgentName 0x824072C0
// returns "BackAwayAgent"; slot 14, RetAgentClassID, is 0x82407278), sets the byte at 0xC0 and stores 0.0f in
// RuffKing's m_fSafeDistance and m_fTooClose (0xC4, 0xC8; the "BackAway" script method sets them in that order). The
// byte's name is ours: OnEnter (slot 6, 0x824075C0) and OnExit (7, 0x82407810) adjust the host's movement only when
// it is set. The table overrides RetAgentStatus (2, 0x82407518), Think (5, 0x82407728) and ReloadCode (21,
// 0x82407888); slot 0 is cMoveAgent's deleting destructor.
#ifndef AI_CBACKAWAYAGENT_H
#define AI_CBACKAWAYAGENT_H

#include "AI/cMoveAndPrimaryFireAgent.h"

namespace AI
{
    class cBackAwayAgent : public cMoveAndPrimaryFireAgent
    {
    public:
        // __forceinline: CD2 expands it into CreateAgent<cBackAwayAgent>, which /Ob1 declines for a plain inline.
        __forceinline cBackAwayAgent(cCharacterBrain *pBrain)
            : cMoveAndPrimaryFireAgent(pBrain), m_bAdjustMovement(true), m_fSafeDistance(0.0f), m_fTooClose(0.0f)
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
        virtual void OnExit();
        virtual unsigned short RetAgentClassID();
        void SetAdjustMovement(bool bAdjust) { m_bAdjustMovement = bAdjust; }
        // RuffKing's setters (out of line there); the "BackAway" script method expands them.
        void SetSafeDistance(const float fDistance) { m_fSafeDistance = fDistance; }
        void SetTargetTooCloseDistance(const float fDistance) { m_fTooClose = fDistance; }

    protected:
        virtual void ReloadCode();

    private:
        bool m_bAdjustMovement;                                 // 0xC0
        float m_fSafeDistance;                                  // 0xC4
        float m_fTooClose;                                      // 0xC8

        CD2_LAYOUT_CHECKS(cBackAwayAgent,
            CD2_SIZE(cBackAwayAgent, 0xD0)
            CD2_OFFSET(cBackAwayAgent, m_bAdjustMovement, 0xC0)
            CD2_OFFSET(cBackAwayAgent, m_fSafeDistance, 0xC4)
            CD2_OFFSET(cBackAwayAgent, m_fTooClose, 0xC8))
    };
}

#endif // AI_CBACKAWAYAGENT_H

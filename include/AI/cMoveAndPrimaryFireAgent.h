// AI::cMoveAndPrimaryFireAgent (Crackdown 2): STAND-IN. RuffKing's cMoveAndPrimaryFireAgent : cMoveAndFaceAgent
// (AI/Agents/cMoveAndPrimaryFireAgent.h) with its fields 0x10 bytes later, after CD2's 0xB0-byte cMoveAndFaceAgent.
// CD2's constructor 0x82410990 (out of line) installs table 0x820FD808 (RetAgentName 0x82410980 returns
// "MoveAndPrimaryFireAgent"; slot 14, RetAgentClassID, is 0x82410938), stores CONST_FLOAT_0 in the two times (0xB0,
// 0xB4) and CONST_INT_0 in m_nBurstFireNumRounds (0xB8), clears m_bFaceTargetWhenNotFiring (0xBC) and sets
// m_bFiringEnabled and m_bUsePrototypeBurstPause (0xBD, 0xBE); CreateAgent<cMoveAndPrimaryFireAgent> (0x823F6D40)
// allocates 0xC0 bytes. Its table overrides Think (slot 5, 0x82250BA0) and OnEnter (6, 0x82410A00) and adds
// RuffKing's ReloadCode (21, 0x82410B78); slot 0 is cMoveAgent's deleting destructor.
#ifndef AI_CMOVEANDPRIMARYFIREAGENT_H
#define AI_CMOVEANDPRIMARYFIREAGENT_H

#include "AI/cMoveAndFaceAgent.h"

namespace AI
{
    class cMoveAndPrimaryFireAgent : public cMoveAndFaceAgent
    {
    public:
        cMoveAndPrimaryFireAgent(cCharacterBrain *pBrain);
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual void Think();
        virtual void OnEnter();
        virtual unsigned short RetAgentClassID();
        // RuffKing's setters (out of line there, with its spelling); CD2's script methods expand them.
        void SetSurpressingFireTime(float fTime) { m_fSuppressingFireTime = fTime; }
        void SetFaceTargetWhenNotFiring(bool bFace) { m_bFaceTargetWhenNotFiring = bFace; }
        void SetFiringEnabled(bool bEnabled) { m_bFiringEnabled = bEnabled; }
        // Keeps the prototype's pause unless the time is above 0.01 (as cFaceAndPrimaryFireAgent's).
        void SetFirePauseTime(float fTime)
        {
            if (fTime > 0.01f)
            {
                m_fBurstFirePauseTime = fTime;
                m_bUsePrototypeBurstPause = false;
            }
        }

    protected:
        virtual void ReloadCode();

        float m_fSuppressingFireTime;                           // 0xB0
        float m_fBurstFirePauseTime;                            // 0xB4
        unsigned int m_nBurstFireNumRounds;                     // 0xB8
        bool m_bFaceTargetWhenNotFiring;                        // 0xBC
        bool m_bFiringEnabled;                                  // 0xBD
        bool m_bUsePrototypeBurstPause;                         // 0xBE

        CD2_LAYOUT_CHECKS(cMoveAndPrimaryFireAgent,
            CD2_SIZE(cMoveAndPrimaryFireAgent, 0xC0)
            CD2_OFFSET(cMoveAndPrimaryFireAgent, m_fSuppressingFireTime, 0xB0)
            CD2_OFFSET(cMoveAndPrimaryFireAgent, m_nBurstFireNumRounds, 0xB8)
            CD2_OFFSET(cMoveAndPrimaryFireAgent, m_bFaceTargetWhenNotFiring, 0xBC)
            CD2_OFFSET(cMoveAndPrimaryFireAgent, m_bUsePrototypeBurstPause, 0xBE))
    };
}

#endif // AI_CMOVEANDPRIMARYFIREAGENT_H

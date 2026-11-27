// AI::cFaceAndPrimaryFireAgent (Crackdown 2): STAND-IN. RuffKing's cFaceAndPrimaryFireAgent : cFaceAgent
// (AI/Agents/cFaceAndPrimaryFireAgent.h) with its fields 0x10 bytes later, after CD2's 0x40-byte cFaceAgent. CD2's
// constructor 0x8240CA48 (out of line) installs table 0x82004230 (RetAgentName 0x8240CA28 returns
// "FaceAndPrimaryFireAgent"; slot 14, RetAgentClassID, is 0x8240C9E0), stores CONST_FLOAT_0 in the five floats
// (0x40..0x50) and CONST_INT_0 in m_nBurstFireNumRounds (0x54) and sets m_bUsePrototypeBurstPause (0x58);
// CreateAgent<cFaceAndPrimaryFireAgent> (0x823F74F0) allocates 0x60 bytes. Its table overrides RetAgentStatus (slot 2,
// 0x82268A00), Think (5, 0x8240D038), OnEnter (6, 0x8240CE98) and EventTrigger (8, 0x8240D070) and adds RuffKing's
// EndOfBurstNotify (15) and Reloading (16), both empty (0x82580578), and ReloadCode (17, 0x8240D138).
#ifndef AI_CFACEANDPRIMARYFIREAGENT_H
#define AI_CFACEANDPRIMARYFIREAGENT_H

#include "AI/cFaceAgent.h"

namespace AI
{
    class cFaceAndPrimaryFireAgent : public cFaceAgent
    {
    public:
        cFaceAndPrimaryFireAgent(cCharacterBrain *pBrain);
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
        virtual void EventTrigger(CHARACTER::eControllerEventType eEventType,
            CHARACTER::eControllerEventSubType eEventSubType,
            CHARACTER::eControllerEvents eEvent);
        virtual unsigned short RetAgentClassID();
        // RuffKing's setters (out of line there, with its spelling); the "FaceAndPrimaryFire" script method (0x823F2920)
        // expands them, SetFirePauseTime keeping the prototype's pause unless the time is above 0.01.
        void SetSurpressingFireTime(float fTime) { m_fSuppressingFireTime = fTime; }
        void SetFirePauseTime(float fTime)
        {
            if (fTime > 0.01f)
            {
                m_fBurstFirePauseTime = fTime;
                m_bUsePrototypeBurstPause = false;
            }
        }
        void SetEnemyDistances(const float &fMinimumDistance, const float &fMaximumDistance)
        {
            m_fMinimumEnemyDistance = fMinimumDistance;
            m_fMaximumEnemyDistance = fMaximumDistance;
        }

    protected:
        virtual void EndOfBurstNotify();
        virtual void Reloading(const bool bReloading);
        virtual void ReloadCode();

        float m_fMinimumEnemyDistance;                          // 0x40
        float m_fMaximumEnemyDistance;                          // 0x44
        float m_fSuppressingFireTime;                           // 0x48
        float m_fBurstFirePauseTime;                            // 0x4C
        float m_fDelayTime;                                     // 0x50
        unsigned int m_nBurstFireNumRounds;                     // 0x54
        bool m_bUsePrototypeBurstPause;                         // 0x58

        CD2_LAYOUT_CHECKS(cFaceAndPrimaryFireAgent,
            CD2_SIZE(cFaceAndPrimaryFireAgent, 0x60)
            CD2_OFFSET(cFaceAndPrimaryFireAgent, m_fMinimumEnemyDistance, 0x40)
            CD2_OFFSET(cFaceAndPrimaryFireAgent, m_fSuppressingFireTime, 0x48)
            CD2_OFFSET(cFaceAndPrimaryFireAgent, m_nBurstFireNumRounds, 0x54)
            CD2_OFFSET(cFaceAndPrimaryFireAgent, m_bUsePrototypeBurstPause, 0x58))
    };
}

#endif // AI_CFACEANDPRIMARYFIREAGENT_H

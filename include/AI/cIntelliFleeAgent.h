// AI::cIntelliFleeAgent (Crackdown 2): STAND-IN; not in the reference builds. CD2's constructor 0x82429280 (out of
// line) builds a cMoveAgent (0x8240E728), installs table 0x820FE930 (RetAgentName 0x82429238 returns
// "IntelliFleeAgent"; slot 14, RetAgentClassID, is 0x824291F0) and clears cMoveAgent's m_bSuccess;
// CreateAgent<cIntelliFleeAgent> (0x823F7110) allocates 0x120 bytes. The fields named here are the ones CD2's
// "IntelliFlee" script methods on cCharacterEntityIF set; the names are ours. The constructor sets the seven animation
// IDs (0xF4..0x10C) to -1 and the times to CONST_FLOAT_0 of its object's g_GlobalConstants copy. Not modelled: a word
// at 0xA0, an embedded object with table 0x820FEA08 at 0xA4 (its +8/+0xC hold copies of the first two "IntelliFlee"
// distances), the words at 0xBC/0xDC, the float at 0xEC, the flags at 0xF0..0xF3 and the halfword at 0x110. Its table
// overrides the deleting destructor (0x82429380), Think, OnEnter, OnExit and EventTrigger (slots 5..8) and OnArrived
// (17, 0x82429998).
#ifndef AI_CINTELLIFLEEAGENT_H
#define AI_CINTELLIFLEEAGENT_H

#include "AI/cMoveAgent.h"

namespace AI
{
    class cIntelliFleeAgent : public cMoveAgent
    {
    public:
        cIntelliFleeAgent(cCharacterBrain *pBrain);
        virtual ~cIntelliFleeAgent();
        // RuffKing's pattern: the type's ID, allocated on first use (CD2 expands it into CreateAgent).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual void Think();
        virtual void OnEnter();
        virtual void OnExit();
        virtual void EventTrigger(CHARACTER::eControllerEventType eEventType,
            CHARACTER::eControllerEventSubType eEventSubType,
            CHARACTER::eControllerEvents eEvent);
        virtual unsigned short RetAgentClassID();

        // The "IntelliFlee" script methods (0x823F2550 .. 0x823F2670) expand these; the two use-flags are words, and CD2
        // normalizes the flag to 0 or 1 (subic/subfe) before storing it.
        void ResetTimeout()
        {
            if (m_nState == 2)
                m_fTimeoutRemaining = m_fTimeout;
        }
        void SetUpperBodyAnim(bool bUse, int nAnimID)
        {
            m_bUseUpperBodyAnim = bUse ? 1 : 0;
            m_nUpperBodyAnimID = nAnimID;
        }
        void SetLookBehindAnim(bool bUse, int nLookAnimID, int nTurnAnimID, float fMinTime, float fMaxTime)
        {
            m_bUseLookBehindAnim = bUse ? 1 : 0;
            m_nLookBehindAnimID = nLookAnimID;
            m_nLookBehindTurnAnimID = nTurnAnimID;
            m_fLookBehindMinTime = fMinTime;
            m_fLookBehindMaxTime = fMaxTime;
        }
        void SetCowerAnims(int nStartAnimID, int nLoopAnimID, int nEndAnimID)
        {
            m_nCowerStartAnimID = nStartAnimID;
            m_nCowerEndAnimID = nEndAnimID;
            m_nCowerLoopAnimID = nLoopAnimID;
        }
        void SetPanicAnim(int nAnimID) { m_nPanicAnimID = nAnimID; }

    protected:
        virtual void OnArrived(bool bSuccess);

    private:
        unsigned char m_unmodelledA0[0xCC - 0xA0];
        float m_fTimeout;                                       // 0xCC
        float m_fTimeoutRemaining;                              // 0xD0
        int m_bUseUpperBodyAnim;                                // 0xD4
        int m_bUseLookBehindAnim;                               // 0xD8
        unsigned char m_unmodelledDC[0xE0 - 0xDC];
        int m_nState;                                           // 0xE0
        float m_fLookBehindMinTime;                             // 0xE4
        float m_fLookBehindMaxTime;                             // 0xE8
        unsigned char m_unmodelledEC[0xF4 - 0xEC];
        int m_nCowerStartAnimID;                                // 0xF4
        int m_nCowerLoopAnimID;                                 // 0xF8
        int m_nCowerEndAnimID;                                  // 0xFC
        int m_nPanicAnimID;                                     // 0x100
        int m_nUpperBodyAnimID;                                 // 0x104
        int m_nLookBehindTurnAnimID;                            // 0x108
        int m_nLookBehindAnimID;                                // 0x10C
        unsigned char m_unmodelled110[0x120 - 0x110];

        CD2_LAYOUT_CHECKS(cIntelliFleeAgent,
            CD2_SIZE(cIntelliFleeAgent, 0x120)
            CD2_OFFSET(cIntelliFleeAgent, m_fTimeout, 0xCC)
            CD2_OFFSET(cIntelliFleeAgent, m_bUseUpperBodyAnim, 0xD4)
            CD2_OFFSET(cIntelliFleeAgent, m_nState, 0xE0)
            CD2_OFFSET(cIntelliFleeAgent, m_fLookBehindMinTime, 0xE4)
            CD2_OFFSET(cIntelliFleeAgent, m_nCowerStartAnimID, 0xF4)
            CD2_OFFSET(cIntelliFleeAgent, m_nPanicAnimID, 0x100)
            CD2_OFFSET(cIntelliFleeAgent, m_nLookBehindAnimID, 0x10C))
    };
}

#endif // AI_CINTELLIFLEEAGENT_H

// AI::cWanderFleeAgent (Crackdown 2): STAND-IN; not in the reference builds. CD2's CreateAgent<cWanderFleeAgent>
// (0x823F7230, which calls its RetAgent<cWanderFleeAgent> 0x823EB6B8 out of line) allocates 0x190 bytes, builds a
// cPedestrianWanderAgent (0x82417830) and installs table 0x820FE490 (RetAgentName 0x8241EC08 returns
// "WanderFleeAgent"; slot 14, RetAgentClassID, is 0x8241EBC0), then the safe pointer at 0x140, the zero avoid position
// (0x150), the flags and words up to 0x180 and CONST_FLOAT_0 of its object's g_GlobalConstants copy (0x830B28E0) in
// the three floats from 0x184: that copy places the constructor in the agent's own object, so it is out of line here.
// The fields named here are the ones CD2's "WanderFlee" script methods on cCharacterEntityIF set; the names are ours.
// Not modelled: 0x160..0x167, 0x16C and the float at 0x18C.
#ifndef AI_CWANDERFLEEAGENT_H
#define AI_CWANDERFLEEAGENT_H

#include "AI/cPedestrianWanderAgent.h"
#include "fun_runtime/safedeletablepointer.h"

class cGameBase;

namespace AI
{
    class cWanderFleeAgent : public cPedestrianWanderAgent
    {
    public:
        cWanderFleeAgent(cCharacterBrain *pBrain);
        // RuffKing's pattern: the type's ID, allocated on first use (CD2 expands it into CreateAgent).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();

        // CD2 0x8241F0E0 (out of line): the "SetWanderFleeAvoidObject" script method calls it.
        void SetAvoidObject(cGameBase *pObject);
        // The other "WanderFlee" script methods (0x823F2768 .. 0x823F2860) expand these; the two use-flags are words,
        // and CD2 normalizes the flag to 0 or 1 before storing it.
        void SetAvoidPosition(const Fun_Runtime::OldVec3 &vPosition)
        {
            m_vAvoidPosition = vPosition;
            m_nAvoidType = 2;
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

    private:
        Fun_Runtime::cSafeDeletablePointer<cGameBase> m_pAvoidObject; // 0x140
        Fun_Runtime::Vec3 m_vAvoidPosition;                     // 0x150
        unsigned char m_unmodelled160[0x168 - 0x160];
        int m_nAvoidType;                                       // 0x168
        unsigned char m_unmodelled16C[0x170 - 0x16C];
        int m_nUpperBodyAnimID;                                 // 0x170
        int m_nLookBehindTurnAnimID;                            // 0x174
        int m_nLookBehindAnimID;                                // 0x178
        int m_bUseUpperBodyAnim;                                // 0x17C
        int m_bUseLookBehindAnim;                               // 0x180
        float m_fLookBehindMinTime;                             // 0x184
        float m_fLookBehindMaxTime;                             // 0x188
        unsigned char m_unmodelled18C[0x190 - 0x18C];

        CD2_LAYOUT_CHECKS(cWanderFleeAgent,
            CD2_SIZE(cWanderFleeAgent, 0x190)
            CD2_OFFSET(cWanderFleeAgent, m_pAvoidObject, 0x140)
            CD2_OFFSET(cWanderFleeAgent, m_vAvoidPosition, 0x150)
            CD2_OFFSET(cWanderFleeAgent, m_nAvoidType, 0x168)
            CD2_OFFSET(cWanderFleeAgent, m_nUpperBodyAnimID, 0x170)
            CD2_OFFSET(cWanderFleeAgent, m_bUseUpperBodyAnim, 0x17C)
            CD2_OFFSET(cWanderFleeAgent, m_fLookBehindMaxTime, 0x188))
    };
}

#endif // AI_CWANDERFLEEAGENT_H

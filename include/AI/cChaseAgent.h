// AI::cChaseAgent (Crackdown 2): STAND-IN. RuffKing's cChaseAgent : cMoveAgent (AI/Agents/cChaseAgent.h) with its
// fields 0x10 bytes later, after CD2's 0xA0-byte cMoveAgent. CD2's constructor 0x82407B30 (out of line) installs table
// 0x820FCF78 (RetAgentName 0x82407A98 returns "ChaseAgent"; slot 14, RetAgentClassID, is 0x82407A50), clears
// m_bUseDefendedPosition (0xA0), builds the safe pointer m_pDefendedObject (0xA4: table 0x82155680, payload 0xB0),
// m_vecDefendedPosition (0xC0) and m_fRadius (0xD0, CONST_FLOAT_0 of its object's g_GlobalConstants copy);
// CreateAgent<cChaseAgent> (0x823FA498) allocates 0xE0 bytes. The class declares no destructor: its deleting
// destructor (0x824080B0) unlinks the safe pointer, restores cSafeDeletablePointerBase's table and calls cMoveAgent's
// destructor. Its table overrides Think (slot 5, 0x82407BC8, which reads and sets m_bUseDefendedPosition) and OnEnter
// (6, 0x82407BC0).
#ifndef AI_CCHASEAGENT_H
#define AI_CCHASEAGENT_H

#include "AI/cMoveAgent.h"
#include "fun_runtime/safedeletablepointer.h"

class cGameBase;

namespace AI
{
    class cChaseAgent : public cMoveAgent
    {
    public:
        cChaseAgent(cCharacterBrain *pBrain);
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual void Think();                                   // 5: 0x82407BC8
        virtual void OnEnter();                                 // 6: 0x82407BC0
        virtual unsigned short RetAgentClassID();
        // RuffKing's (inline, an out-of-line copy at its 0x8231CA90); CD2's copy is 0x823EC8A0. The object goes in
        // through a temporary safe pointer.
        void SetDefendedPosition(bool bUseDefendedPosition, cGameBase *pDefendedObject,
            const Fun_Runtime::Vec3 &vecDefendedPosition, float fRadius)
        {
            m_bUseDefendedPosition = bUseDefendedPosition;
            m_pDefendedObject = pDefendedObject;
            m_vecDefendedPosition = vecDefendedPosition;
            m_fRadius = fRadius;
        }

    protected:
        bool m_bUseDefendedPosition;                            // 0xA0
        Fun_Runtime::cSafeDeletablePointer<cGameBase> m_pDefendedObject; // 0xA4
        Fun_Runtime::Vec3 m_vecDefendedPosition;                // 0xC0
        float m_fRadius;                                        // 0xD0

        CD2_LAYOUT_CHECKS(cChaseAgent,
            CD2_SIZE(cChaseAgent, 0xE0)
            CD2_OFFSET(cChaseAgent, m_bUseDefendedPosition, 0xA0)
            CD2_OFFSET(cChaseAgent, m_pDefendedObject, 0xA4)
            CD2_OFFSET(cChaseAgent, m_vecDefendedPosition, 0xC0)
            CD2_OFFSET(cChaseAgent, m_fRadius, 0xD0))
    };
}

#endif // AI_CCHASEAGENT_H

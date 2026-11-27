// AI::cProtectAgent (Crackdown 2): STAND-IN; not in the reference builds. CD2's CreateAgent<cProtectAgent> (0x823F9958)
// allocates 0xF0 bytes, builds a cMoveAndPrimaryFireAgent (0x82410990), installs table 0x820FDED8 (RetAgentName
// 0x8241A948 returns "ProtectAgent"; slot 14, RetAgentClassID, is 0x8241A900), stores CONST_FLOAT_0 of its object's
// g_GlobalConstants copy (0x830B1EA0) at 0xC0 (that copy places the constructor in the agent's own object, so it is
// out of line here), builds the protected position at 0xD0 from ZeroVec and the safe pointer at 0xE0. The names are
// ours: the "ProtectObject" script method (0x823F40F8) sets the radius and the object. Its table has its own deleting
// destructor (0x8241A958) and overrides Think (slot 5, 0x8241ABD0) and OnEnter (6, 0x8241A9E8).
#ifndef AI_CPROTECTAGENT_H
#define AI_CPROTECTAGENT_H

#include "AI/cMoveAndPrimaryFireAgent.h"
#include "fun_runtime/safedeletablepointer.h"

class cGameBase;

namespace AI
{
    class cProtectAgent : public cMoveAndPrimaryFireAgent
    {
    public:
        cProtectAgent(cCharacterBrain *pBrain);
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
        void SetProtectRadius(float fRadius) { m_fProtectRadius = fRadius; }
        void SetProtectPosition(const Fun_Runtime::Vec3 &vPosition) { m_vProtectPosition = vPosition; }
        // CD2's copy is 0x823EC978: the object goes in through a temporary safe pointer.
        void SetProtectObject(cGameBase *pObject) { m_pProtectObject = pObject; }

    private:
        float m_fProtectRadius;                                 // 0xC0
        Fun_Runtime::Vec3 m_vProtectPosition;                   // 0xD0
        Fun_Runtime::cSafeDeletablePointer<cGameBase> m_pProtectObject; // 0xE0

        CD2_LAYOUT_CHECKS(cProtectAgent,
            CD2_SIZE(cProtectAgent, 0xF0)
            CD2_OFFSET(cProtectAgent, m_fProtectRadius, 0xC0)
            CD2_OFFSET(cProtectAgent, m_vProtectPosition, 0xD0)
            CD2_OFFSET(cProtectAgent, m_pProtectObject, 0xE0))
    };
}

#endif // AI_CPROTECTAGENT_H

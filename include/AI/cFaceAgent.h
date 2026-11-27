// AI::cFaceAgent (Crackdown 2): STAND-IN. RuffKing's cFaceAgent : cAgent (AI/Agents/cFaceAgent.h) with its fields 8
// bytes later, after CD2's 0x10-byte cAgent: CD2's CreateAgent<cFaceAgent> (0x823FA1A0) allocates 0x40 bytes and
// stores the tolerance and difference (0x10, 0x14), a zero face point (0x20), m_bFacePoint = false (0x30) and
// m_bTargetFacingEnabled = true (0x31), then installs table 0x82003704 (RetAgentName 0x8240C938 returns "FaceAgent").
// Slot 2 (0x8240C948) is RuffKing's RetAgentStatus.
#ifndef AI_CFACEAGENT_H
#define AI_CFACEAGENT_H

#include "AI/cAgent.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/class.h"

namespace AI
{
    class cFaceAgent : public cAgent
    {
    public:
        cFaceAgent(cCharacterBrain *pBrain)
            : cAgent(pBrain), m_fTolerance(Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0),
              m_fDifference(Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0), m_bFacePoint(false), m_bTargetFacingEnabled(true)
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
        virtual unsigned short RetAgentClassID();
        // Slot 5: CD2 0x82286BA8 (also cUpperBodyAnimateAndFaceAgent's; cDropAgent's Think calls it first).
        virtual void Think();
        // RuffKing's setters; CD2's "Face" script method (0x823F4358) expands them as RuffKing's ActivateAgent does.
        void SetTolerance(float fTolerance) { m_fTolerance = fTolerance; }
        void SetTargetFacingEnabled(bool bEnabled) { m_bTargetFacingEnabled = bEnabled; }
        void SetFaceTarget() { m_bFacePoint = false; }
        // cCharacterEntityIF's Face(fTolerance, vPointToFace) (0x823F43B8) expands it, as RuffKing's ActivateAgent with a
        // point does.
        void SetFacePoint(const Fun_Runtime::Vec3 &vPoint)
        {
            m_bFacePoint = true;
            m_vecFaceThisPoint = vPoint;
        }

    protected:
        float m_fTolerance;                         // 0x10
        float m_fDifference;                        // 0x14
        Fun_Runtime::Vec3 m_vecFaceThisPoint;       // 0x20
        bool m_bFacePoint;                          // 0x30
        bool m_bTargetFacingEnabled;                // 0x31

        CD2_LAYOUT_CHECKS(cFaceAgent,
            CD2_SIZE(cFaceAgent, 0x40)
            CD2_OFFSET(cFaceAgent, m_fTolerance, 0x10)
            CD2_OFFSET(cFaceAgent, m_vecFaceThisPoint, 0x20)
            CD2_OFFSET(cFaceAgent, m_bFacePoint, 0x30)
            CD2_OFFSET(cFaceAgent, m_bTargetFacingEnabled, 0x31))
    };
}

#endif // AI_CFACEAGENT_H

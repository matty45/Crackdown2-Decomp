// AI::cMoveAgent (Crackdown 2): STAND-IN. RuffKing's cMoveAgent : cAgent (AI/Agents/cMoveAgent.h) with its fields 8
// bytes later, after CD2's 0x10-byte cAgent. CD2's constructor 0x8240E728 (out of line) installs table 0x820FD708
// (RetAgentName 0x82227F60 returns "MoveAgent"; slot 14, RetAgentClassID, is 0x821FED70) and initializes the fields
// below in RuffKing's order: the path finder at 0x10, three vectors (0x20, 0x30, 0x40), the guard distance, stuck
// timers and reached distance (0x50..0x5C), the flags at 0x60..0x64, three graph pointers (0x68..0x70), m_bNeedGraph
// (0x74), the destination vector (0x78, its three pointers cleared), the last destination vertex (0x88), the streaming
// functor it allocates (0x8C), m_ePreviousLOD (0x90) and m_uiHierarchicalPathfindTries (0x94). CreateAgent<cMoveAgent>
// (0x823F5550) allocates 0xA0 bytes. The deleting destructor (0x82410DB8) calls the out-of-line destructor 0x82361770.
// Table 0x820FD708 has 21 slots: cAgent's 15, then RuffKing's IsOutsideGuardRadius (15, reads m_vecGuardPoint),
// SetDestination (16, a vector reference and two flags), OnArrived (17), one slot RuffKing lacks (18), UsePointLock
// (19, 0x827E56A8 returns 0) and SetPathFinderLOD (20). The overrides of cAgent's unnamed slots 12 and 13 keep their
// numeric placeholders.
#ifndef AI_CMOVEAGENT_H
#define AI_CMOVEAGENT_H

#include "AI/cAgent.h"
#include "CHARACTER/lodlevel.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/oldvec3.h"
#include "fun_runtime/vector.h"
#include "cd2/layout.h"

namespace Kaim
{
    class CSpatialGraph;
    class CFindNearestData;
    class CVertex;
}

namespace AI
{
    class CAdvancedPathfinder;
    class cLogicalGraph;
    class TStreamingCallbackFunctor;

    class cMoveAgent : public cAgent
    {
    public:
        cMoveAgent(cCharacterBrain *pBrain);
        virtual ~cMoveAgent();
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned int RetAgentStatus() const;            // 2: 0x8240EA50
        virtual void Think();                                   // 5: 0x8231C098
        virtual void OnEnter();                                 // 6: 0x8240EB80
        virtual void OnExit();                                  // 7: 0x82365198
        virtual void vf12();                                    // 12: 0x8242A3A0
        virtual void vf13();                                    // 13: 0x8240F010
        virtual unsigned short RetAgentClassID();
        virtual bool IsOutsideGuardRadius() const;              // 15: 0x8240E968
        virtual void SetDestination(const Fun_Runtime::Vec3 &vecDestination, bool bForced,
            bool bRememberOldDestination);                      // 16: 0x8240EF60
        // RuffKing's setters (out of line there); CD2's script methods ("MoveTo" 0x823F2018, ...) expand them.
        void SetAcceptableReachedDestinationDistance(float fDistance) { m_fReachedDestinationDistance = fDistance; }
        void SetUsePrecision(bool bUsePrecision) { m_bUsePrecision = bUsePrecision; }
        void SetStuckTimeout(float fStuckTimeout) { m_fStuckTimeout = fStuckTimeout; }
        void SetGuardPointAndDistance(const Fun_Runtime::Vec3 &vPoint, const float &fDistance)
        {
            m_vecGuardPoint = vPoint;
            m_fGuardDistance = fDistance;
        }

    protected:
        virtual void OnArrived(bool bSuccess);                  // 17: 0x8240EE10
        virtual void vf18();                                    // 18: 0x8240EEA8
        virtual bool UsePointLock();                            // 19: 0x827E56A8
        virtual void SetPathFinderLOD();                        // 20: 0x82228178

        CAdvancedPathfinder *m_pPathFinder;                     // 0x10
        Fun_Runtime::Vec3 m_vecDestination;                     // 0x20
        Fun_Runtime::Vec3 m_vecOldPosition;                     // 0x30
        Fun_Runtime::Vec3 m_vecGuardPoint;                      // 0x40
        float m_fGuardDistance;                                 // 0x50
        float m_fStuckTime;                                     // 0x54
        float m_fStuckTimeout;                                  // 0x58
        float m_fReachedDestinationDistance;                    // 0x5C
        bool m_bUsePrecision;                                   // 0x60
        bool m_bReachedPrecisionGoal;                           // 0x61
        bool m_bArrived;                                        // 0x62
        bool m_bSuccess;                                        // 0x63
        bool m_bUseHierarchicalPathFinding;                     // 0x64
        cLogicalGraph *m_pLogicalGraph;                         // 0x68
        Kaim::CSpatialGraph *m_pGlobalGraph;                    // 0x6C
        Kaim::CFindNearestData *m_pGlobalFND;                   // 0x70
        bool m_bNeedGraph;                                      // 0x74

    private:
        Fun_Runtime::cVector<Fun_Runtime::OldVec3> m_vDestinations; // 0x78
        Kaim::CVertex *m_pLastDestinationVertex;                // 0x88
        TStreamingCallbackFunctor *m_pStreamingGraphReadyFunctor; // 0x8C
        CHARACTER::eLODLevel m_ePreviousLOD;                    // 0x90
        unsigned int m_uiHierarchicalPathfindTries;             // 0x94

        CD2_LAYOUT_CHECKS(cMoveAgent,
            CD2_SIZE(cMoveAgent, 0xA0)
            CD2_OFFSET(cMoveAgent, m_pPathFinder, 0x10)
            CD2_OFFSET(cMoveAgent, m_vecDestination, 0x20)
            CD2_OFFSET(cMoveAgent, m_vecGuardPoint, 0x40)
            CD2_OFFSET(cMoveAgent, m_fGuardDistance, 0x50)
            CD2_OFFSET(cMoveAgent, m_fReachedDestinationDistance, 0x5C)
            CD2_OFFSET(cMoveAgent, m_bUsePrecision, 0x60)
            CD2_OFFSET(cMoveAgent, m_bUseHierarchicalPathFinding, 0x64)
            CD2_OFFSET(cMoveAgent, m_pLogicalGraph, 0x68)
            CD2_OFFSET(cMoveAgent, m_bNeedGraph, 0x74)
            CD2_OFFSET(cMoveAgent, m_vDestinations, 0x78)
            CD2_OFFSET(cMoveAgent, m_pLastDestinationVertex, 0x88)
            CD2_OFFSET(cMoveAgent, m_pStreamingGraphReadyFunctor, 0x8C)
            CD2_OFFSET(cMoveAgent, m_ePreviousLOD, 0x90)
            CD2_OFFSET(cMoveAgent, m_uiHierarchicalPathfindTries, 0x94))
    };
}

#endif // AI_CMOVEAGENT_H

// AI::cSimpleDrivingAvoidanceAgent (Crackdown 2): STAND-IN. RuffKing's cSimpleDrivingAvoidanceAgent : cAgent
// (AI/Agents/VehicleAgents/cSimpleDrivingAvoidanceAgentBase.h) with its fields 8 bytes later, after CD2's 0x10-byte
// cAgent. CD2's constructor 0x821D1880 (out of line) installs table 0x820FE800 (RetAgentName 0x824275D0 returns
// "cSimpleDrivingAvoidanceAgent"; slot 14, RetAgentClassID, is 0x82427588) and initializes the fields at RuffKing's
// offsets plus 8 (the update intervals at 0x18..0x20 and 0x30/0x34, the flags at 0x3C..0x3F, the sim mode 2 at 0x40,
// the counters at 0x44..0x50); CreateAgent<cSimpleDrivingAvoidanceAgent> (0x823F5670) allocates 0x5C bytes. Its
// table: OnEnter and OnExit (slots 6, 7), then RuffKing's DoAvoidance, VehicleEnterPhysicalState,
// VehicleLeavePhysicalState, SetEarlyAvoidanceEnable and RetPtrVehicle (15..19).
#ifndef AI_CSIMPLEDRIVINGAVOIDANCEAGENT_H
#define AI_CSIMPLEDRIVINGAVOIDANCEAGENT_H

#include "AI/cAgent.h"

namespace Vehicle { class cVehicle; }

namespace AI
{
    class cSimpleDrivingAvoidance;
    class cSimpleVehicleSensing;

    class cSimpleDrivingAvoidanceAgent : public cAgent
    {
    public:
        cSimpleDrivingAvoidanceAgent(cCharacterBrain *pBrain);
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual void OnEnter();
        virtual void OnExit();
        virtual unsigned short RetAgentClassID();
        // RuffKing's flags are AI::cSimpleDrivingAvoidance::eAvoidanceFlags, not modelled here.
        virtual void DoAvoidance(Vehicle::cVehicle *pVehicle, unsigned int eFlags, Vehicle::cVehicle *pIgnoreVehicle);
        virtual void VehicleEnterPhysicalState();
        virtual void VehicleLeavePhysicalState();
        virtual void SetEarlyAvoidanceEnable(bool bEnableEarlyAvoidance);
        virtual Vehicle::cVehicle *RetPtrVehicle();

    protected:
        cSimpleDrivingAvoidance *m_pSimpleAvoidanceHandler;     // 0x10
        cSimpleVehicleSensing *m_pSimpleVehicleSensing;         // 0x14
        int m_nUpdateInteral;                                   // 0x18
        int m_nStoppingUpdateScalar;                            // 0x1C
        int m_nRandomUpdateOffset;                              // 0x20
        bool m_bUseEarlyAvoidance;                              // 0x24
        float m_fMinUpdateVelo;                                 // 0x28
        float m_fMaxUpdateVelo;                                 // 0x2C
        int m_nMinUpdateInterval;                               // 0x30
        int m_nMaxUpdateInterval;                               // 0x34
        int m_nNoUpdateTicks;                                   // 0x38
        bool m_bLimitSpeed;                                     // 0x3C
        bool m_bUsePathOptimalSpeed;                            // 0x3D
        bool m_bAvoidChaseTarget;                               // 0x3E
        bool m_bIsStuck;                                        // 0x3F
        int m_ReverseSimModeCache;                              // 0x40 (RuffKing's cVehicleController::etSimMode)
        int m_nNumTicksInReverse;                               // 0x44
        int m_nDetectStuckReversingTickCounter;                 // 0x48
        int m_nDetectNeedReverseTickCounter;                    // 0x4C
        int m_nDetectStuckMovingForwardTickCounter;             // 0x50
        float m_fDriveForwardSpeedLimitTrigger;                 // 0x54
        float m_fHeightOffset;                                  // 0x58

        CD2_LAYOUT_CHECKS(cSimpleDrivingAvoidanceAgent,
            CD2_SIZE(cSimpleDrivingAvoidanceAgent, 0x5C)
            CD2_OFFSET(cSimpleDrivingAvoidanceAgent, m_nUpdateInteral, 0x18)
            CD2_OFFSET(cSimpleDrivingAvoidanceAgent, m_bUseEarlyAvoidance, 0x24)
            CD2_OFFSET(cSimpleDrivingAvoidanceAgent, m_bLimitSpeed, 0x3C)
            CD2_OFFSET(cSimpleDrivingAvoidanceAgent, m_ReverseSimModeCache, 0x40)
            CD2_OFFSET(cSimpleDrivingAvoidanceAgent, m_fHeightOffset, 0x58))
    };
}

#endif // AI_CSIMPLEDRIVINGAVOIDANCEAGENT_H

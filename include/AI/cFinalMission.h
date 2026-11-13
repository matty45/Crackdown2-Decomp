#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_CFINALMISSION_H
#define AI_CFINALMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cMissionActivationCylinder.h"

namespace GameManagement { class cFinalMissionBarrier; }

namespace AI
{
    class cHeliCallZone;
    class cMissionCriticalPropSpawnPoint;

    class cFinalMission : public AI::cMission
    {
    public:
        // RuffKing's mission states; CD2's GetSaveStateForMissionState (0x8246C430) saves 1..9 as eFMS_Ready.
        enum etFinalMissionState
        {
            eFMS_Blocked = 0,
            eFMS_Ready,
            eFMS_Charging1,
            eFMS_Charging2,
            eFMS_Charging3,
            eFMS_Collapse,
            eFMS_Detonate,
            eFMS_Complete,
            eFMS_Failed,
            eFMS_Resetting,
            eFMS_Pending_Ready,
            eFMS_Pending_Failed,
            eFMS_SignallingCore1Destroyed,
            eFMS_SignallingCore2Destroyed,
            eFMS_SignallingCore3Destroyed,
            eFMS_NumStates,
        };
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcFinalMissionClass;

        cFinalMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cFinalMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Activate(); // cRegisteredClass 2: 0x8248A0C8 (folded with cPebbleDashMission's identical body)
        virtual void Deactivate(); // cRegisteredClass 3: 0x8245E238 (folded with cAUMission's identical body)
        virtual void TickUpdate(float); // cRegisteredClass 8: 0x8246D070
        virtual void OnClientMissionStateNotification(unsigned char,unsigned char); // cRegisteredClass 15: 0x8246C340
        virtual void OnChildMissionCompleted(AI::cMission *); // cRegisteredClass 22: 0x8246C238
        virtual bool ArePrerequisitesComplete() const; // cRegisteredClass 23: 0x8246E5E8
        virtual bool IsLocalPlayerNearby() const; // cRegisteredClass 24: 0x8246E5F8
        virtual void InitReplication(); // cRegisteredClass 37: 0x8246BDD0
        virtual void TermReplication(); // cRegisteredClass 38: 0x8246BEE0
    protected:
        virtual void OnLeaveMissionState(unsigned char); // cRegisteredClass 29: 0x8246CC98
        virtual void OnEnterMissionState(unsigned char); // cRegisteredClass 31: 0x8246CA40
        virtual void OnEnterGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 33: 0x8246C248
        virtual void GetSaveStateForMissionState(unsigned char &,unsigned char &); // cRegisteredClass 36: 0x8246C430
        // RuffKing's cFinalMission fields (cFinalMission.h) at CD2's offsets up to its path lists: OnChildMissionCompleted
        // (0x8246C238) counts 0x3C5, TermReplication (0x8246BEE0) reads the three core spawn points at 0x408..0x410.
        // Size 0xC50 from CD2's registrar; RuffKing's class is 0x990, so CD2's later fields sit elsewhere: the barrier
        // that IsLocalPlayerNearby (0x8246E5F8) tests the player against is at 0xA08 (RuffKing 0x7D8), the core
        // containment zones that OnEnterGlobalMissionState (0x8246C248) starts and stops at 0xC20 (RuffKing 0x954).
        cHeliCallZone *m_pActivationZone;               // 0x3C0
        unsigned char m_nNumChildMissions;              // 0x3C4
        unsigned char m_nNumChildMissionsCompleted;     // 0x3C5
        float m_fCurrentChargeTimer;                    // 0x3C8
        float m_fPrevChargeTimer;                       // 0x3CC
        float m_fUpperWarnTime[3];                      // 0x3D0
        float m_fMiddleWarnTime[3];                     // 0x3DC
        float m_fBottomWarnTime[3];                     // 0x3E8
        float m_fPrevHealth[3];                         // 0x3F4
        float m_fCameraCutTimer;                        // 0x400
        bool m_bInCameraCut;                            // 0x404
        cMissionCriticalPropSpawnPoint *m_pCore1Spawnpoint;     // 0x408
        cMissionCriticalPropSpawnPoint *m_pCore2Spawnpoint;     // 0x40C
        cMissionCriticalPropSpawnPoint *m_pCore3Spawnpoint;     // 0x410
        bool m_bLocalPlayerLockedInMission;             // 0x414
        bool m_bPlayerWasInMissionArea;                 // 0x415
        bool m_bLocalPlayerInTriggerZone;               // 0x416
        bool m_bCore1Alive;                             // 0x417
        bool m_bCore2Alive;                             // 0x418
        bool m_bCore3Alive;                             // 0x419
        unsigned int m_unmodelled41C[(0xA08 - 0x41C) / 4];
        GameManagement::cFinalMissionBarrier *m_pBarrier;       // 0xA08
        unsigned int m_unmodelledA0C[(0xC20 - 0xA0C) / 4];
        cMissionActivationCylinder *m_pCore1ContainmentZone;    // 0xC20
        cMissionActivationCylinder *m_pCore2ContainmentZone;    // 0xC24
        cMissionActivationCylinder *m_pCore3ContainmentZone;    // 0xC28
        unsigned int m_unmodelledC2C[(0xC50 - 0xC2C) / 4];
        CD2_LAYOUT_CHECKS(cFinalMission,
            CD2_OFFSET(cFinalMission, m_nNumChildMissionsCompleted, 0x3C5)
            CD2_OFFSET(cFinalMission, m_pCore1Spawnpoint, 0x408)
            CD2_OFFSET(cFinalMission, m_bCore3Alive, 0x419)
            CD2_OFFSET(cFinalMission, m_pBarrier, 0xA08)
            CD2_OFFSET(cFinalMission, m_pCore1ContainmentZone, 0xC20)
            CD2_SIZE(cFinalMission, 0xC50))
    };
}

#endif


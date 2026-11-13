#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_CBREACHHOLEMISSION_H
#define AI_CBREACHHOLEMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "fun_runtime/vectorip.h"
#include "ZoneManager/cPlayerTriggerBase.h"
namespace Activity { class cSquadSpawnPoint; }
namespace Cam { class cCameraMarker; }

namespace AI
{
    class cBreachHole;
    class cPatrolRoute;

    // RuffKing's bases. CD2's MakeNew (0x82471370) returns the attribute handler at +0x258, cMission's at +0x10 in the
    // complete object, as cTacticalObjective's does; this class's mission overrides read cMission-relative offsets
    // 0x10 below RuffKing's complete-object ones.
    class cBreachHoleMission : public RWS::CEventHandler, public AI::cMission
    {
    public:
        // RuffKing's states; CD2's GetSaveStateForMissionState (0x82472618) saves 0..3 as eBS_Closed, 4 and 5 as
        // eBS_Destroyed.
        enum eBreachState
        {
            eBS_Open = 0,
            eBS_Standby,
            eBS_FailedToOpen,
            eBS_Closed,
            eBS_Destroyed,
            eBS_ChopperClosing,
            eBS_NumStates,
            eBS_Invalid,
        };
        // RuffKing declares the CEventHandler override; CD2's table 0x821041EC holds it in slot 5.
        virtual void HandleEvents(RWS::CMsg &);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcBreachHoleMissionClass;

        cBreachHoleMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cBreachHoleMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Activate(); // cRegisteredClass 2: 0x82471800
        virtual void Deactivate(); // cRegisteredClass 3: 0x82471858
        virtual void ResetMission(); // cRegisteredClass 4: 0x824713C0
        virtual void NotifySquadSpawn(Activity::cSquadSpawnPoint *); // cRegisteredClass 7: 0x82472D68
        virtual void TickUpdate(float); // cRegisteredClass 8: 0x82342478
        virtual void Destruct(); // cRegisteredClass 18: 0x82475848
        virtual bool IsLocalPlayerNearby() const; // cRegisteredClass 24: 0x82473330
        virtual void NotifyDeliveryStart(int); // cRegisteredClass 25: 0x82472EA0
        virtual void InitReplication(); // cRegisteredClass 37: 0x82475D88
        virtual void TermReplication(); // cRegisteredClass 38: 0x82475E50
    protected:
        virtual void OnLeaveMissionState(unsigned char); // cRegisteredClass 29: 0x82472898
        virtual void OnTransitionMissionState(unsigned char); // cRegisteredClass 30: 0x82472888
        virtual void OnEnterMissionState(unsigned char); // cRegisteredClass 31: 0x82472670
        virtual void OnEnterGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 33: 0x824717A0
        virtual void GetSaveStateForMissionState(unsigned char &,unsigned char &); // cRegisteredClass 36: 0x82472618
    protected:
        // RuffKing's fields and offsets; its size (0x530) is CD2's registrar size.
        unsigned int m_SquadDeathCounts[3];             // 0x3D0 RuffKing: cMap<unsigned char, unsigned char>; not modelled
        unsigned int m_LastSentSquadDeathCounts[3];     // 0x3DC RuffKing: cMap<unsigned char, unsigned char>; not modelled
        unsigned int m_nMaxSpawn;                       // 0x3E8
        unsigned short m_nBreachHoleStates;             // 0x3EC
        unsigned short m_nTotalKillCount;               // 0x3EE
        float m_fHealth;                                // 0x3F0
        bool m_bInsideActivation;                       // 0x3F4
        float m_fLastHostUpdateReceivedTime;            // 0x3F8
        float m_fPercToHeli;                            // 0x3FC
        float m_fCloseDelay;                            // 0x400
        float m_fLastPlayerNearbyTimer;                 // 0x404
        float m_fOpenTimer;                             // 0x408
        float m_fIntroCutTimer;                         // 0x40C
        float m_fCurrentTimer;                          // 0x410
        float m_fDeathCountUpdateTimer;                 // 0x414
        unsigned char m_nLastNodeSentTo;                // 0x418
        ZoneManager::cPlayerTriggerBase *m_pActivationZone;             // 0x41C
        Fun_Runtime::cVectorip<cBreachHole *, 10> m_vBreachHoles;       // 0x420
        Fun_Runtime::cVectorip<Activity::cSquadSpawnPoint *, 10> m_vHeliSquad;      // 0x460
        Fun_Runtime::cVectorip<cMission *, 20> m_vMissions;             // 0x4A0
        bool m_bSpawningPhase;                          // 0x500
        bool m_bHeliActive;                             // 0x501
        bool m_bHasShownMapGD;                          // 0x502
        unsigned int m_nBreachOpenTime;                 // 0x504
        const cPatrolRoute *m_pTravelRoute;             // 0x508
        const cPatrolRoute *m_pTargetRoute;             // 0x50C
        float m_fCameraCutTriggerRadiusSq;              // 0x510
        float m_fCameraCutHoldTime;                     // 0x514
        unsigned int m_nCameraCutEndTime;               // 0x518
        bool m_bInCameraCut;                            // 0x51C
        int m_nHeliID;                                  // 0x520
        unsigned char m_ePrevMissionState;              // 0x524
        bool m_bShowingBreachState;                     // 0x525
        Cam::cCameraMarker *m_pIntroCameraLookAtMarker; // 0x528
        CD2_LAYOUT_CHECKS(cBreachHoleMission,
            CD2_SIZE(cBreachHoleMission, 0x530)
            CD2_OFFSET(cBreachHoleMission, m_SquadDeathCounts, 0x3D0)
            CD2_OFFSET(cBreachHoleMission, m_pActivationZone, 0x41C)
            CD2_OFFSET(cBreachHoleMission, m_vMissions, 0x4A0)
            CD2_OFFSET(cBreachHoleMission, m_nHeliID, 0x520)
            CD2_OFFSET(cBreachHoleMission, m_pIntroCameraLookAtMarker, 0x528))
    };
}

#endif


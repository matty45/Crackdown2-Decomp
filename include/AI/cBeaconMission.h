#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_CBEACONMISSION_H
#define AI_CBEACONMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "fun_runtime/vector.h"
#include "AI/cHeliCallZone.h"
#include "AI/cMissionActivationCylinder.h"

namespace Prop { class cProp; }

namespace AI
{
    class cAgencyTowerSegmentMission;

    class cBeaconMission : public AI::cMission
    {
    public:
        // RuffKing's mission states.
        enum etBeaconMissionState
        {
            eBMS_Blocked = 0,
            eBMS_Direction_Start,
            eBMS_Direction_Follow,
            eBMS_Ready,
            eBMS_WaitingForStartDelivery,
            eBMS_EnRoute,
            eBMS_Pending_Dropping,
            eBMS_Dropping,
            eBMS_RaisingWFDRT,
            eBMS_ChargingBeacon,
            eBMS_ChargingSWGT,
            eBMS_SWGTCollapse,
            eBMS_ExplosionInitialShockwave,
            eBMS_ExplosionExpandingUVSPhere,
            eBMS_ExplosionCooldown,
            eBMS_Complete,
            eBMS_AbortDelivery,
            eBMS_Pending_Failed,
            eBMS_Failed,
            eBMS_BeaconDestroyed,
            eBMS_Resetting,
            eBMS_Pending_Ready,
            eBMS_NumStates,
        };
        // CD2's load/save table overrides Save with 0x82465088.
        virtual void Save(SaveGame::cSaveStream *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcBeaconMissionClass;

        cBeaconMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cBeaconMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Activate(); // cRegisteredClass 2: 0x8248A0C8 (folded with cPebbleDashMission's identical body)
        virtual void Deactivate(); // cRegisteredClass 3: 0x82464F08
        virtual void ResetMission(); // cRegisteredClass 4: 0x82468328
        virtual void NotifySquadDead(Activity::cSquadSpawnPoint *); // cRegisteredClass 5: 0x82467EF0
        virtual void TickUpdate(float); // cRegisteredClass 8: 0x82325D48
        virtual void OnMissionCriticalPropDestroyed(AI::cMissionCriticalPropSpawnPoint *); // cRegisteredClass 11: 0x824685C0
        virtual void OnMissionCriticalPropDetached(AI::cMissionCriticalPropSpawnPoint *); // cRegisteredClass 13: 0x8226FEB0
        virtual void OnClientMissionStateNotification(unsigned char,unsigned char); // cRegisteredClass 15: 0x82464F60
        virtual bool ArePrerequisitesComplete() const; // cRegisteredClass 23: 0x8246E5E8
        virtual bool IsLocalPlayerNearby() const; // cRegisteredClass 24: 0x82467BC0
        virtual void NotifyDeliveryStart(int); // cRegisteredClass 25: 0x82467B10
        virtual void NotifyDeliveryDrop(bool); // cRegisteredClass 26: 0x82467B30
        virtual void NotifyDeliveryFinish(bool); // cRegisteredClass 27: 0x82467B90
        virtual void InitReplication(); // cRegisteredClass 37: 0x82464728
    protected:
        virtual void OnLeaveMissionState(unsigned char); // cRegisteredClass 29: 0x823BFFD8
        virtual void OnEnterMissionState(unsigned char); // cRegisteredClass 31: 0x82465FE8
        virtual void OnLeaveGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 32: 0x82464E80
        virtual void OnEnterGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 33: 0x82464CE8
        virtual void GetSaveStateForMissionState(unsigned char &,unsigned char &); // cRegisteredClass 36: 0x822607C8
        // CD2: cBeaconMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void TermReplication(); // cRegisteredClass 38: 0x82242398
        // cLoadSaveObject table 0x821040B4 (at +0x260): slot 0. RuffKing declares the override.
        virtual void Load(SaveGame::cLoadStream *pStream);
        // RuffKing's names; CD2 0x82467D80 and 0x823BD500 (Load calls both).
        void SetBeaconZones(int numDaysPassed);
        void LinkToTrafficZones();
    protected:
        // RuffKing's first cBeaconMission fields (cBeaconMission.h) at CD2's offsets: NotifySquadDead (0x82467EF0) counts
        // 0x3CA. Size 0x2300 from CD2's registrar; RuffKing's class is smaller, so the rest is not modelled.
        unsigned int m_unmodelled3C0;
        unsigned short m_nNumAUMissions;
        unsigned short m_nNumAUMissionsCompleted;
        unsigned short m_nNumInitialSquads;
        unsigned short m_nNumInitialSquadsDead;
        // RuffKing's next fields, at its offsets: NotifyDeliveryStart (0x82467B10) stores m_nHeliID at 0x3D4.
        unsigned int m_nBeaconToDeliver;                                // 0x3CC
        Prop::cProp *m_pDeliveryBeacon;                                 // 0x3D0
        unsigned int m_nHeliID;                                         // 0x3D4
        unsigned int m_nBreachHoleStates;                               // 0x3D8
        cAgencyTowerSegmentMission *m_pTowerMission;                    // 0x3DC
        cMissionCriticalPropSpawnPoint *m_pBeaconTargetSpawnPoint;      // 0x3E0
        cMissionCriticalPropSpawnPoint *m_pSWGTTargetSpawnPoint;        // 0x3E4
        unsigned int m_unmodelled3E8[(0x1B30 - 0x3E8) / 4];
        // RuffKing's names; CD2's OnLeaveGlobalMissionState (0x82464E80) hides the call zone at 0x1B30 and stops the
        // containment zones of the vector at 0x224C.
        cHeliCallZone *m_pActivationZone;                               // 0x1B30
        // RuffKing's next fields (0x1AE4.. there); CD2's Load (0x82464FB0) reads the five words and tests the two flags.
        float m_fLastMissionPhase;                                      // 0x1B34
        float m_fMissionCompletePhase;                                  // 0x1B38
        int m_nNumDaysPassed;                                           // 0x1B3C
        int m_nPhase2SpecialCaseSpawnSkip;                              // 0x1B40
        int m_nPhase3SpecialCaseExtraDay;                               // 0x1B44
        bool m_validLoadedData;                                         // 0x1B48
        bool m_zonesInitialised;                                        // 0x1B49
        unsigned char m_unmodelled1B4A[0x224C - 0x1B4A];
        Fun_Runtime::cVector<cMissionActivationCylinder *> m_vContainmentZones;    // 0x224C
        unsigned int m_unmodelled225C[(0x2300 - 0x225C) / 4];
        CD2_LAYOUT_CHECKS(cBeaconMission,
            CD2_OFFSET(cBeaconMission, m_nNumInitialSquadsDead, 0x3CA)
            CD2_OFFSET(cBeaconMission, m_nHeliID, 0x3D4)
            CD2_OFFSET(cBeaconMission, m_pSWGTTargetSpawnPoint, 0x3E4)
            CD2_OFFSET(cBeaconMission, m_pActivationZone, 0x1B30)
            CD2_OFFSET(cBeaconMission, m_nNumDaysPassed, 0x1B3C)
            CD2_OFFSET(cBeaconMission, m_zonesInitialised, 0x1B49)
            CD2_OFFSET(cBeaconMission, m_vContainmentZones, 0x224C)
            CD2_SIZE(cBeaconMission, 0x2300))
    };
}

#endif


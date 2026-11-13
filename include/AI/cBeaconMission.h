#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_CBEACONMISSION_H
#define AI_CBEACONMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cBeaconMission : public AI::cMission
    {
    public:
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
    protected:
        // RuffKing's first cBeaconMission fields (cBeaconMission.h) at CD2's offsets: NotifySquadDead (0x82467EF0) counts
        // 0x3CA. Size 0x2300 from CD2's registrar; RuffKing's class is smaller, so the rest is not modelled.
        unsigned int m_unmodelled3C0;
        unsigned short m_nNumAUMissions;
        unsigned short m_nNumAUMissionsCompleted;
        unsigned short m_nNumInitialSquads;
        unsigned short m_nNumInitialSquadsDead;
        unsigned int m_unmodelled3CC[(0x2300 - 0x3CC) / 4];
        CD2_LAYOUT_CHECKS(cBeaconMission,
            CD2_OFFSET(cBeaconMission, m_nNumInitialSquadsDead, 0x3CA)
            CD2_SIZE(cBeaconMission, 0x2300))
    };
}

#endif


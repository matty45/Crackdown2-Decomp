#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_CCELLSTRONGHOLDMISSION_H
#define AI_CCELLSTRONGHOLDMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "fun_runtime/vectorip.h"
#include "ZoneManager/cPlayerTriggerBase.h"
namespace GameManagement { class cCampaignPlayerSpawnGroup; }
namespace VEHICLE_CONTROL { class cVehicleCollectionZone; }

namespace AI
{
    class cCellStrongholdMission : public AI::cMission
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcCellStrongholdMissionClass;

        cCellStrongholdMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // RuffKing's states.
        enum eCSMState
        {
            eCSMS_Inactive = 0,
            eCSMS_Within,
            eCSMS_Complete,
            eCSMS_NumStates,
            eCSMS_Invalid,
        };
        // CD2: cCellStrongholdMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Activate(); // cRegisteredClass 2: 0x82475090
        virtual void Deactivate(); // cRegisteredClass 3: 0x8245E238 (folded with cAUMission's identical body)
        virtual void ResetMission(); // cRegisteredClass 4: 0x82475420
        virtual void TickUpdate(float); // cRegisteredClass 8: 0x824750A0
        virtual bool IsLocalPlayerNearby() const; // cRegisteredClass 24: 0x82475508
        virtual void InitReplication(); // cRegisteredClass 37: 0x82326A78
        virtual void TermReplication(); // cRegisteredClass 38: 0x823BA938
    protected:
        virtual void OnEnterMissionState(unsigned char); // cRegisteredClass 31: 0x82475390
        virtual void OnLeaveGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 32: 0x82475360
        virtual void OnEnterGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 33: 0x82475298
        virtual void GetSaveStateForMissionState(unsigned char &,unsigned char &); // cRegisteredClass 36: 0x8233F690
    protected:
        // RuffKing's fields; its size (0x410) is CD2's registrar size. IsLocalPlayerNearby (0x82475508) and
        // OnLeaveGlobalMissionState (0x82475360) read the containment zone at 0x3D0.
        float m_fCurrResetTime;                                         // 0x3C0
        float m_fResetTimer;                                            // 0x3C4
        GameManagement::cCampaignPlayerSpawnGroup *m_pSpawnGroup;       // 0x3C8
        VEHICLE_CONTROL::cVehicleCollectionZone *m_pCollectionZone;     // 0x3CC
        ZoneManager::cPlayerTriggerBase *m_pContainmentZone;            // 0x3D0
        Fun_Runtime::cVectorip<cMission *, 5> m_vMissions;              // 0x3E0
        CD2_LAYOUT_CHECKS(cCellStrongholdMission,
            CD2_SIZE(cCellStrongholdMission, 0x410)
            CD2_OFFSET(cCellStrongholdMission, m_pContainmentZone, 0x3D0)
            CD2_OFFSET(cCellStrongholdMission, m_vMissions, 0x3E0))
    };
}

#endif


#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_CBREACHHOLEMISSION_H
#define AI_CBREACHHOLEMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cBreachHoleMission : public AI::cMission
    {
    public:
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
        // Size 0x530 from CD2's registrar (MakeNew allocates it); the fields after cMission are not modelled.
        unsigned int m_unmodelled3C0[(0x530 - 0x3C0) / 4];
        CD2_LAYOUT_CHECKS(cBreachHoleMission, CD2_SIZE(cBreachHoleMission, 0x530))
    };
}

#endif


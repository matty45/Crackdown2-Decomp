#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_CAUMISSION_H
#define AI_CAUMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cAUMission : public AI::cMission
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAUMissionClass;

        cAUMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cAUMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Activate(); // cRegisteredClass 2: 0x8245E200
        virtual void ResetMission(); // cRegisteredClass 4: 0x8245F428
        virtual void OnMissionCriticalPropTakeDamage(AI::cMissionCriticalPropSpawnPoint *,Damage::cDamage &); // cRegisteredClass 10: 0x8245E240
        virtual void OnMissionCriticalPropDestroyed(AI::cMissionCriticalPropSpawnPoint *); // cRegisteredClass 11: 0x8245E310
        virtual void OnMissionCriticalPropUsed(AI::cMissionCriticalPropSpawnPoint *,unsigned char); // cRegisteredClass 12: 0x8245E368
        virtual void OnMissionCriticalPropDetached(AI::cMissionCriticalPropSpawnPoint *); // cRegisteredClass 13: 0x8245E4B0
        virtual void OnMissionCriticalPropApproachedByLocalPlayer(AI::cMissionCriticalPropSpawnPoint *); // cRegisteredClass 14: 0x8245E530
        virtual void OnClientMissionStateNotification(unsigned char,unsigned char); // cRegisteredClass 15: 0x822ACAB0
        virtual void InitReplication(); // cRegisteredClass 37: 0x8245E000
        virtual void TermReplication(); // cRegisteredClass 38: 0x8245E100
    protected:
        virtual void TriggerCompletionVOA(); // cRegisteredClass 28: 0x8245DDE0
        virtual void OnTransitionMissionState(unsigned char); // cRegisteredClass 30: 0x8245E888
        virtual void OnEnterMissionState(unsigned char); // cRegisteredClass 31: 0x8245E9B8
        virtual void OnEnterGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 33: 0x8245EBC0
        virtual void OnEnterComplete(); // cRegisteredClass 34: 0x822AC510
        virtual void GetSaveStateForMissionState(unsigned char &,unsigned char &); // cRegisteredClass 36: 0x8245F380
    };
}

#endif


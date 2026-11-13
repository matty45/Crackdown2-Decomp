#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_CCELLSTRONGHOLDMISSION_H
#define AI_CCELLSTRONGHOLDMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

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
        // CD2: cCellStrongholdMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Activate(); // cRegisteredClass 2: 0x82475090
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
        // Size 0x410 from CD2's registrar (MakeNew allocates it); the fields after cMission are not modelled.
        unsigned int m_unmodelled3C0[(0x410 - 0x3C0) / 4];
        CD2_LAYOUT_CHECKS(cCellStrongholdMission, CD2_SIZE(cCellStrongholdMission, 0x410))
    };
}

#endif


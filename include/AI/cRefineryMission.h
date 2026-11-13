#ifndef AI_CREFINERYMISSION_H
#define AI_CREFINERYMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cMission.h"

namespace AI
{
    class cRefineryMission : public cMission
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcRefineryMissionClass;

        cRefineryMission();
        // Out of line (CD2 0x82456C20): the deleting wrapper calls it.
        virtual ~cRefineryMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cRefineryMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Deactivate(); // cRegisteredClass 3: 0x82456DA8
        virtual void TickUpdate(float); // cRegisteredClass 8: 0x82456F70
        virtual void OnMissionCriticalPropUsed(AI::cMissionCriticalPropSpawnPoint *,unsigned char); // cRegisteredClass 12: 0x822AC238
        virtual bool IsLocalPlayerNearby() const; // cRegisteredClass 24: 0x82457230
        virtual void InitReplication(); // cRegisteredClass 37: 0x82456CA8
        virtual void TermReplication(); // cRegisteredClass 38: 0x82456D28
    protected:
        virtual void OnLeaveGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 32: 0x82457060
        // CD2: cRefineryMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    protected:
        virtual void OnEnterMissionState(unsigned char); // cRegisteredClass 31: 0x82456E28
        virtual void OnEnterGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 33: 0x824570E0
    protected:
        // Size 0x400 from CD2's registrar (MakeNew allocates it); the fields after cMission are not modelled.
        unsigned int m_unmodelled3C0[(0x400 - 0x3C0) / 4];
        CD2_LAYOUT_CHECKS(cRefineryMission, CD2_SIZE(cRefineryMission, 0x400))
    };
}

#endif


#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_CAGENCYTOWERSEGMENTMISSION_H
#define AI_CAGENCYTOWERSEGMENTMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cAgencyTowerSegmentMission : public AI::cMission
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAgencyTowerSegmentMissionClass;

        cAgencyTowerSegmentMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cAgencyTowerSegmentMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Activate(); // cRegisteredClass 2: 0x8245CD58
        virtual void ResetMission(); // cRegisteredClass 4: 0x8245C798
        virtual void TickUpdate(float); // cRegisteredClass 8: 0x8245D058
        virtual void TermReplication(); // cRegisteredClass 38: 0x8245CCF8
    protected:
        virtual void OnEnterMissionState(unsigned char); // cRegisteredClass 31: 0x8245CE08
        virtual void OnEnterGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 33: 0x82580578
        virtual void OnEnterComplete(); // cRegisteredClass 34: 0x8245CF68
    };
}

#endif


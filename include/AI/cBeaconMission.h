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
    };
}

#endif


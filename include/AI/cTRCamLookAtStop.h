#ifndef AI_CTRCAMLOOKATSTOP_H
#define AI_CTRCAMLOOKATSTOP_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cTrainingRouteEvent.h"

namespace AI
{
    // RuffKing's base. CD2's table (0x82104B28) holds this class's RetClass, IsA and RetClassName in slots 11 to 13, where
    // cBasePatrolRouteEvent declares them.
    class cTRCamLookAtStop : public cTrainingRouteEvent
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTRCamLookAtStopClass;

        cTRCamLookAtStop();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif


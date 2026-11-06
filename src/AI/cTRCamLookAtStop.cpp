// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "AI/cTRCamLookAtStop.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cTRCamLookAtStop::ms_pcTRCamLookAtStopClass = 0;

    cTRCamLookAtStop::cTRCamLookAtStop() {}

    const Fun_Runtime::cClass &cTRCamLookAtStop::RetClass() const
    {
        return *ms_pcTRCamLookAtStopClass;
    }

    const char *cTRCamLookAtStop::RetClassName() const
    {
        return "cTRCamLookAtStop";
    }

    bool cTRCamLookAtStop::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTRCamLookAtStopClass->IsA(c);
    }

    RWS::CAttributeHandler *cTRCamLookAtStop::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTRCamLookAtStop();
    }
}

static RWS::CClassFactory::CRegistrar cTRCamLookAtStopRegistrar(
    "cTRCamLookAtStop", AI::cTRCamLookAtStop::MakeNew, 0x90, false);

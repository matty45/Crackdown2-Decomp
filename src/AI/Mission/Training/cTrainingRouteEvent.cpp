// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cTrainingRouteEvent.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cTrainingRouteEvent::ms_pcTrainingRouteEventClass = 0;

    cTrainingRouteEvent::cTrainingRouteEvent() {}

    const Fun_Runtime::cClass &cTrainingRouteEvent::RetClass() const
    {
        return *ms_pcTrainingRouteEventClass;
    }

    const char *cTrainingRouteEvent::RetClassName() const
    {
        return "cTrainingRouteEvent";
    }

    bool cTrainingRouteEvent::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTrainingRouteEventClass->IsA(c);
    }

    RWS::CAttributeHandler *cTrainingRouteEvent::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTrainingRouteEvent();
    }

    static RWS::CClassFactory::CRegistrar cTrainingRouteEventRegistrar(
        "cTrainingRouteEvent", cTrainingRouteEvent::MakeNew, 0x90, false);
}

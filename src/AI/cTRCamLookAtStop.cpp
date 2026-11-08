// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "AI/cTRCamLookAtStop.h"
#include "rws/classfactory.h"
#include "AI/BehaviourClassID.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"

namespace AI
{
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

    Fun_Runtime::cClass &cTRCamLookAtStop::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTRCamLookAtStopClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cTRCamLookAtStop", 0x90);
        return *cTRCamLookAtStopClass;
    }

    const Fun_Runtime::cClass *cTRCamLookAtStop::ms_pcTRCamLookAtStopClass = &cTRCamLookAtStop::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cTRCamLookAtStopcTrainingRouteEventInheritRegistrar(
        cTRCamLookAtStop::StaticCreateClass(), cTrainingRouteEvent::StaticCreateClass());
}

static RWS::CClassFactory::CRegistrar cTRCamLookAtStopRegistrar(
    "cTRCamLookAtStop", AI::cTRCamLookAtStop::MakeNew, 0x90, false);

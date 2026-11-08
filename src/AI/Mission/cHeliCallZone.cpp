// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cHeliCallZone.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cHeliCallZone::ms_pcHeliCallZoneClass = &cHeliCallZone::StaticCreateClass();

    cHeliCallZone::cHeliCallZone() {}

    const Fun_Runtime::cClass &cHeliCallZone::RetClass() const
    {
        return *ms_pcHeliCallZoneClass;
    }

    const char *cHeliCallZone::RetClassName() const
    {
        return "cHeliCallZone";
    }

    bool cHeliCallZone::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcHeliCallZoneClass->IsA(c);
    }

    RWS::CAttributeHandler *cHeliCallZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHeliCallZone();
    }
}

static RWS::CClassFactory::CRegistrar cHeliCallZoneRegistrar(
    "cHeliCallZone", AI::cHeliCallZone::MakeNew, 0x1F0, false);
